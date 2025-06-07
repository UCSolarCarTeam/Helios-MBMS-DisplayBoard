#pragma once
#include <stdint.h>
#include <Arduino.h>
#include "MBMS.h"
#include "lvgl.h"
#include "ui.h"


void updateBatteryInfoUI(const uint8_t* data, size_t length);