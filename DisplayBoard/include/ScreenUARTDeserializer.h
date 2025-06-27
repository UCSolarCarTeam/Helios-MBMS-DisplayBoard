#pragma once
#include <cstdint>
#include <cstddef>
#include "MBMS.hpp"
#include "Arduino.h"


#define UART_BAUD_RATE 115200
#define UART_BUFFER_SIZE 256

extern HardwareSerial uart1; // UART1 instance
extern ScreenDataDictionary screenData;
extern uint8_t rxBuffer[];

#define UART_RX_PIN 16
#define UART_TX_PIN 17


bool deserializeScreenData(ScreenDataDictionary &out, const uint8_t *buffer, size_t len);
void UARTReceiverTask(void *pvParameters);
