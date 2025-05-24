#pragma once

#include "ui.h"
#include "lvgl.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "lv_conf.h"
#include <XPT2046_Touchscreen.h>
#include "ui.h"

extern TFT_eSPI tftDisplay;
extern SPIClass touchscreenSPI;

// #define XPT2046_IRQ 36   // T_IRQ
// #define XPT2046_MOSI 13  // T_DIN
// #define XPT2046_MISO 12  // T_OUT
// #define XPT2046_CLK 14   // T_CLK
// #define XPT2046_CS 33    // T_CS

#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

const int touch_min_x = 200;
const int touch_max_x = 3600;
const int touch_min_y = 240;
const int touch_max_y = 3700;

extern volatile bool atHomeScreen;

enum BUTTON_ID {
  CONTACTOR_AND_PRECHARGER_STATUS,
  TRIP_STATUS,
  BATTERY_INFO,
  POWER_STATUS,
  MBMS_STATUS,
  BUTTON_COUNT
};

struct Button {
    int x1;     // Top-left x-coordinate
    int y1;     // Top-left y-coordinate
    int x2;     // Bottom-right x-coordinate
    int y2;     // Bottom-right y-coordinate
    BUTTON_ID id;

    // Constructor that takes top-left and bottom-right coordinates
    Button(int topX, int topY, int bottomX, int bottomY, BUTTON_ID buttonId)
        : x1(topX), y1(topY), x2(bottomX), y2(bottomY), id(buttonId) {}

        //12,211
    // Check if point is within bounds
    bool contains(int px, int py) const {
        return px >= x1 && px <= x2 &&
               py >= y2 && py <= y1;
    }

    // Get width (useful for some calculations)
    int width() const { return x2 - x1; }

    // Get height (useful for some calculations)
    int height() const { return y2 - y1; }
};

const Button buttons[] = {
    {0, 220, 330, 170, BUTTON_ID::CONTACTOR_AND_PRECHARGER_STATUS},  // x1,y1 to x2,y2
    {0, 140, 140, 92, BUTTON_ID::TRIP_STATUS},
    {175, 144, 320, 90, BUTTON_ID::BATTERY_INFO},
    {0, 70, 142, 13, BUTTON_ID::POWER_STATUS},
    {165, 67, 325, 2, BUTTON_ID::MBMS_STATUS}
};

extern XPT2046_Touchscreen touchscreen;

void clearAllCheckMarks(void);
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void tft_init(void);
void handleTouchscreen();