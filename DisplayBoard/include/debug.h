#pragma once
#include <Arduino.h>
#include "ScreenUARTDeserializer.h"

#define DEBUG_UART 0
#define DEBUG_TOUCH 0

// Print the entire screen data dictionary to Serial
void printScreenDataDictionary(const ScreenDataDictionary& d);
