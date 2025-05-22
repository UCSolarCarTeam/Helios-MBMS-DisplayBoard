#pragma once

#include "Arduino.h"
#include <string.h>
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_MISO 19
#define PIN_MOSI 23
#define PIN_SCLK 18
#define PIN_CS 5

#define MAX_TRANSFER_SIZE 138 // Adjust based on expected data size

esp_err_t setupSPI();
esp_err_t receiveSPIMessage(uint8_t *recvbuf, size_t bufsize, size_t *received_len);