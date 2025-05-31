// #include "driver/spi_slave.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_log.h"
// #include <string.h>

// #define TAG "SPI_SLAVE"

// #define SPI_SLAVE_HOST HSPI_HOST // Or VSPI_HOST
// #define DMA_CHAN 1               // DMA channel for SPI
// #define PIN_NUM_MISO 19
// #define PIN_NUM_MOSI 23
// #define PIN_NUM_SCLK 18
// #define PIN_NUM_CS 5

// #define RX_BUFFER_SIZE 128
// #define TX_BUFFER_SIZE 128

// static void spi_slave_task(void *arg)
// {
//     esp_err_t ret;
//     WORD_ALIGNED_ATTR uint8_t recvbuf[RX_BUFFER_SIZE];
//     WORD_ALIGNED_ATTR uint8_t sendbuf[TX_BUFFER_SIZE];

//     // Pre-fill TX buffer (for testing)
//     strcpy((char *)sendbuf, "ACK from ESP32");

//     spi_slave_transaction_t t;
//     memset(&t, 0, sizeof(t));
//     t.length = RX_BUFFER_SIZE * 8; // in bits
//     t.tx_buffer = sendbuf;
//     t.rx_buffer = recvbuf;

//     while (1)
//     {
//         // Wait for transaction from master
//         ret = spi_slave_transmit(SPI_SLAVE_HOST, &t, portMAX_DELAY);
//         if (ret == ESP_OK)
//         {
//             ESP_LOGI(TAG, "Received data: %.*s", RX_BUFFER_SIZE, recvbuf);
//             // Process message here
//         }
//     }
// }

// void setupSPI(void)
// {
//     esp_err_t ret;

//     // SPI slave config
//     spi_slave_interface_config_t slave_config = {
//         /* spics_io_num    */ PIN_NUM_CS,
//         /* flags           */ 0,
//         /* queue_size      */ 3,
//         /* mode            */ 0, // SPI mode 0 (optional, but depends on actual struct)
//         /* post_setup_cb   */ NULL,
//         /* post_trans_cb   */ NULL};

//     // SPI pin config
//     spi_bus_config_t bus_config = {
//         /* mosi_io_num     */ PIN_NUM_MOSI,
//         /* miso_io_num     */ PIN_NUM_MISO,
//         /* sclk_io_num     */ PIN_NUM_SCLK,
//         /* quadwp_io_num   */ -1,
//         /* quadhd_io_num   */ -1};

//     // Initialize SPI bus
//     ret = spi_slave_initialize(SPI_SLAVE_HOST, &bus_config, &slave_config, DMA_CHAN);
//     ESP_ERROR_CHECK(ret);

//     xTaskCreate(spi_slave_task, "spi_slave_task", 4096, NULL, 5, NULL);
// }
