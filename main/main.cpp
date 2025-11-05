#include <iostream>
#include <string>
#include <cstring>

extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "freertos/event_groups.h"
    #include "esp_wifi.h"
    #include "esp_event.h"
    #include "esp_log.h"
    #include "nvs_flash.h"
    #include "driver/gpio.h"
    #include "esp_http_client.h"
    #include "esp_netif.h"
}

static const char* TAG = "WiFiHTTP";

// ====== CONFIG ======
#define WIFI_SSID      "rolowany"
#define WIFI_PASS      "qXLm2wo6"
#define LED_GPIO       GPIO_NUM_2       // Onboard LED
#define TEST_URL       "http://example.org"  // change to any URL

// ====== Event Group ======
static EventGroupHandle_t wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0;

// ====== Global buffer to store HTML ======
static char html_buffer[8192];  // adjust size as needed
static int html_offset = 0;

// ====== Forward Declarations ======
static void wifi_init_sta();
static void blink_task(void* arg);
static void http_get_task(void* arg);

// ====== Event Handler ======
extern "C" void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                   int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } 
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "WiFi disconnected, reconnecting...");
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
    } 
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        auto* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

// ====== Wi-Fi Init ======
static void wifi_init_sta()
{
    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {};
    std::strncpy((char*)wifi_config.sta.ssid, WIFI_SSID, sizeof(wifi_config.sta.ssid));
    wifi_config.sta.ssid[sizeof(wifi_config.sta.ssid)-1] = 0;
    std::strncpy((char*)wifi_config.sta.password, WIFI_PASS, sizeof(wifi_config.sta.password));
    wifi_config.sta.password[sizeof(wifi_config.sta.password)-1] = 0;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "WiFi initialization complete.");
}

// ====== LED Blink Task ======
static void blink_task(void* arg)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (true) {
        EventBits_t bits = xEventGroupGetBits(wifi_event_group);
        if (bits & WIFI_CONNECTED_BIT) {
            gpio_set_level(LED_GPIO, 1);  // solid ON
        } else {
            gpio_set_level(LED_GPIO, 0);
            vTaskDelay(pdMS_TO_TICKS(300));
            gpio_set_level(LED_GPIO, 1);
            vTaskDelay(pdMS_TO_TICKS(300));
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// ====== HTTP Event Handler ======
esp_err_t http_event_handle(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            if (!esp_http_client_is_chunked_response(evt->client)) {
                int copy_len = evt->data_len;
                if (html_offset + copy_len >= sizeof(html_buffer)) {
                    copy_len = sizeof(html_buffer) - html_offset - 1; // leave room for null
                }
                memcpy(html_buffer + html_offset, evt->data, copy_len);
                html_offset += copy_len;
                html_buffer[html_offset] = '\0';
            }
            break;
        default:
            break;
    }
    return ESP_OK;
}

// ====== HTTP GET Task ======
static void http_get_task(void* arg)
{
    // Wait until Wi-Fi is connected
    xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

    ESP_LOGI(TAG, "Starting HTTP GET to %s", TEST_URL);

    html_offset = 0;  // reset buffer

    esp_http_client_config_t config;
    memset(&config, 0, sizeof(config));
    config.url = TEST_URL;
    config.method = HTTP_METHOD_GET;
    config.event_handler = http_event_handle;  // attach event handler
    config.cert_pem = NULL;
    config.skip_cert_common_name_check = true;
    config.use_global_ca_store = false;

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        int status = esp_http_client_get_status_code(client);
        int length = esp_http_client_get_content_length(client);
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d", status, length);
        ESP_LOGI(TAG, "HTML content:\n%s", html_buffer);
    } else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
    ESP_LOGI(TAG, "HTTP GET task finished.");

    vTaskDelete(NULL);
}

// ====== app_main ======
extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init_sta();

    xTaskCreate(blink_task, "blink_task", 2048, nullptr, 5, nullptr);
    xTaskCreate(http_get_task, "http_get_task", 8192, nullptr, 5, nullptr);
}


