// #include "spi_helper.h"

// #define PIN_MISO 19
// #define PIN_MOSI 23
// #define PIN_SCLK 18
// #define PIN_CS 5

// #define MAX_TRANSFER_SIZE 138 // Adjust based on expected data size

// // Function to initialize the SPI slave interface
// esp_err_t setupSPI()
// {
//     // Configure SPI bus
//     spi_bus_config_t buscfg = {
//         .mosi_io_num = PIN_MOSI,
//         .miso_io_num = PIN_MISO,
//         .sclk_io_num = PIN_SCLK,
//         .quadwp_io_num = -1,
//         .quadhd_io_num = -1,
//         .max_transfer_sz = MAX_TRANSFER_SIZE};

//     // Configure SPI slave interface
//     spi_slave_interface_config_t slvcfg = {
//         .spics_io_num = PIN_CS,
//         .flags = 0,
//         .queue_size = 3,
//         .mode = 0, // SPI mode 0: CPOL=0, CPHA=0
//         .post_setup_cb = nullptr,
//         .post_trans_cb = nullptr};

//     // Initialize SPI slave interface
//     esp_err_t ret = spi_slave_initialize(HSPI_HOST, &buscfg, &slvcfg, SPI_DMA_CH_AUTO);
//     if (ret != ESP_OK)
//     {
//         Serial.printf("Failed to initialize SPI slave: %s", esp_err_to_name(ret));
//     }
//     return ret;
// }

// // Function to receive SPI message
// esp_err_t receiveSPIMessage(uint8_t *recvbuf, size_t bufsize, size_t *received_len)
// {
//     if (!recvbuf || bufsize == 0)
//     {
//         Serial.printf("Invalid receive buffer");
//         return ESP_ERR_INVALID_ARG;
//     }

//     spi_slave_transaction_t t;
//     memset(&t, 0, sizeof(t));
//     t.length = bufsize * 8; // Length in bits
//     t.rx_buffer = recvbuf;

//     // Wait for a transaction from the master
//     esp_err_t ret = spi_slave_transmit(HSPI_HOST, &t, portMAX_DELAY);
//     if (ret == ESP_OK)
//     {
//         if (received_len)
//         {
//             *received_len = t.trans_len / 8;
//         }

//         // Print the received message
//         Serial.print("Received message: ");
//         for (int i = 0; i < (*received_len); i++)
//         {
//             // Serial.print((char)recvbuf[i]); // Print as characters
//             // Alternatively, to print as hex values:
//             Serial.print(recvbuf[i], HEX);
//             Serial.print(" ");
//         }
//         Serial.println(); // New line after printing
//     }
//     else
//     {
//         Serial.printf("SPI transmission failed: %s", esp_err_to_name(ret));
//     }
//     return ret;
// }
