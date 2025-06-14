#pragma once

#include "Arduino.h"
#include <string.h>
#include "lvgl.h"
#include "MBMS.hpp"
#include "ui.h"
#include "mcp2515.h"
#include "CAN.hpp"

//Might not be needed but defined for clarity

//P3 Extended IO
#define COM_PIN_MOSI 35
#define COM_PIN_SCLK 22
#define COM_PIN_CS 21

//TX/RX Pins on yellow board 
#define CAN_PIN_IRQ 1
#define COM_PIN_MISO 3

#define SPI_CLOCK_SPEED 1000000 // 1MHz SPI clock speed, adjust as needed

extern struct can_frame frame;
void processCAN(void);