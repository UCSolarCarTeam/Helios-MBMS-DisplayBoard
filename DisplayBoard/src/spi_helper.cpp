#include <string.h>
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_MISO 19
#define PIN_MOSI 23
#define PIN_SCLK 18
#define PIN_CS 5

#define MAX_TRANSFER_SIZE 138 // Adjust based on expected data size

static const char *TAG = "SPI_SLAVE";

void app_main(void)
{
    // Configure SPI bus
    spi_bus_config_t buscfg = {
        .mosi_io_num = PIN_MOSI,
        .miso_io_num = PIN_MISO,
        .sclk_io_num = PIN_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = MAX_TRANSFER_SIZE};

    // Configure SPI slave interface
    spi_slave_interface_config_t slvcfg = {
        .spics_io_num = PIN_CS,
        .flags = 0,
        .queue_size = 3,
        .mode = 0, // SPI mode 0: CPOL=0, CPHA=0
        .post_setup_cb = nullptr,
        .post_trans_cb = nullptr};
        
    // Initialize SPI slave interface
    esp_err_t ret = spi_slave_initialize(HSPI_HOST, &buscfg, &slvcfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize SPI slave: %s", esp_err_to_name(ret));
        return;
    }

    // Buffers for receiving data
    uint8_t recvbuf[MAX_TRANSFER_SIZE] = {0};
    spi_slave_transaction_t t;

    while (true)
    {
        memset(&t, 0, sizeof(t));
        t.length = MAX_TRANSFER_SIZE * 8; // Length in bits
        t.rx_buffer = recvbuf;

        // Wait for a transaction from the master
        ret = spi_slave_transmit(HSPI_HOST, &t, portMAX_DELAY);
        if (ret == ESP_OK)
        {
            // Process received data
            ESP_LOGI(TAG, "Received %d bytes:", t.trans_len / 8);
            for (int i = 0; i < t.trans_len / 8; ++i)
            {
                printf("%02X ", recvbuf[i]);
            }
            printf("\n");
        }
        else
        {
            ESP_LOGE(TAG, "SPI transmission failed: %s", esp_err_to_name(ret));
        }
    }
}
