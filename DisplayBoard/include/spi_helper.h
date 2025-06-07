#pragma once

#include "Arduino.h"
#include <string.h>
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <ESP32SPISlave.h>
#include "lvgl.h"
#include "MBMS.h"
#include "ui.h"

//Might not be needed but defined for clarity
#define COM_PIN_MISO 27

#define COM_PIN_MOSI 35
#define COM_PIN_SCLK 22
#define COM_PIN_CS 21

// #define PIN_MISO 19
// #define PIN_MOSI 23
// #define PIN_SCLK 18
// #define PIN_CS 5

#define BATTERY_INFO_SIZE 30

#define MAX_TRANSFER_SIZE 138 // Adjust based on expected data size

extern const size_t BUFFER_SIZE;
extern const size_t QUEUE_SIZE;

extern uint8_t tx_buf[];
extern uint8_t rx_buf[];


