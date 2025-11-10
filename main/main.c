#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#define LED_GPIO        GPIO_NUM_2
#define WIFI_CONNECTED_BIT BIT0

static const char *TAG = "WIFI_HTTP_APP";

static EventGroupHandle_t wifi_event_group;
static volatile bool internet_available = false;
static TaskHandle_t led_task_handle = NULL;

// Konfiguracja Wi-Fi
static const char *ssid = "12345";
static const char *password = "fsce3889";

// --------------------------------------------
// LED Task
// --------------------------------------------
static void led_blink_task(void *pvParameters)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        if (!internet_available) {
            // brak Internetu → mrugaj
            gpio_set_level(LED_GPIO, 1);
            vTaskDelay(pdMS_TO_TICKS(500));
            gpio_set_level(LED_GPIO, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            // Internet OK → LED włączony
            gpio_set_level(LED_GPIO, 1);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

// --------------------------------------------
// Sprawdzenie dostępu do Internetu (ping-like)
// --------------------------------------------
static void internet_check_task(void *pvParameters)
{
    while (1) {
        EventBits_t bits = xEventGroupGetBits(wifi_event_group);

        if (bits & WIFI_CONNECTED_BIT) {
            struct addrinfo hints = {0};
            struct addrinfo *res = NULL;
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;

            int err = getaddrinfo("example.com", "80", &hints, &res);
            if (err == 0 && res != NULL) {
                int sock = socket(res->ai_family, res->ai_socktype, 0);
                if (sock >= 0) {
                    struct timeval timeout = { .tv_sec = 3, .tv_usec = 0 };
                    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
                    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

                    if (connect(sock, res->ai_addr, res->ai_addrlen) == 0) {
                        internet_available = true;
                        close(sock);
                        freeaddrinfo(res);
                        vTaskDelay(pdMS_TO_TICKS(10000));
                        continue;
                    }
                    close(sock);
                }
                freeaddrinfo(res);
            }
            internet_available = false;
        } else {
            internet_available = false;
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

// --------------------------------------------
// Event handler Wi-Fi
// --------------------------------------------
static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT) {
        if (event_id == WIFI_EVENT_STA_START) {
            ESP_LOGI(TAG, "Łączenie z Wi-Fi...");
            esp_wifi_connect();
        } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
            ESP_LOGW(TAG, "Rozłączono z Wi-Fi, ponawiam...");
            xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
            esp_wifi_connect();
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "Połączono! IP: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

// --------------------------------------------
// Setup Wi-Fi
// --------------------------------------------
static void wifi_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));

    wifi_config_t wifi_config = {0};
    strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
    strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password));
    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

// --------------------------------------------
// HTTP GET przez socket
// --------------------------------------------
void http_get_task(void *pvParameters)
{
    char rx_buffer[512];

    while (1) {
        if (!internet_available) {
            ESP_LOGW(TAG, "Brak Internetu, pomijam request...");
            vTaskDelay(pdMS_TO_TICKS(10000));
            continue;
        }

        ESP_LOGI(TAG, "Łączenie z serwerem example.com...");
        struct addrinfo hints = {0};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        struct addrinfo *res = NULL;

        int err = getaddrinfo("example.com", "80", &hints, &res);
        if (err != 0 || res == NULL) {
            ESP_LOGE(TAG, "DNS lookup failed");
            vTaskDelay(pdMS_TO_TICKS(10000));
            continue;
        }

        int sock = socket(res->ai_family, res->ai_socktype, 0);
        if (sock < 0) {
            ESP_LOGE(TAG, "Socket failed");
            freeaddrinfo(res);
            vTaskDelay(pdMS_TO_TICKS(10000));
            continue;
        }

        struct timeval timeout = { .tv_sec = 5, .tv_usec = 0 };
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

        if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
            ESP_LOGE(TAG, "Connect failed");
            close(sock);
            freeaddrinfo(res);
            vTaskDelay(pdMS_TO_TICKS(10000));
            continue;
        }
        freeaddrinfo(res);

        const char *req = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
        write(sock, req, strlen(req));

        int len;
        while ((len = read(sock, rx_buffer, sizeof(rx_buffer) - 1)) > 0) {
            rx_buffer[len] = 0;
            printf("%s", rx_buffer);
        }

        close(sock);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

// --------------------------------------------
// app_main
// --------------------------------------------
void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());

    wifi_event_group = xEventGroupCreate();

    // Task LED
    xTaskCreate(led_blink_task, "led_blink", 2048, NULL, 5, &led_task_handle);

    // Inicjalizacja Wi-Fi
    wifi_init();

    // Task sprawdzający Internet
    xTaskCreate(internet_check_task, "internet_check", 4096, NULL, 5, NULL);

    // Task HTTP
    xTaskCreate(http_get_task, "http_get", 8192, NULL, 5, NULL);
}

