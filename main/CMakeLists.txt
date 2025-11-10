idf_component_register(
    SRCS "main.c"
    PRIV_REQUIRES spi_flash lwip esp_wifi esp_event nvs_flash driver
    INCLUDE_DIRS ""
)


