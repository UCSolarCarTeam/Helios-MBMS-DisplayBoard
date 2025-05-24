#pragma once

#include "ui.h"
#include "lvgl.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "lv_conf.h"
#include <XPT2046_Touchscreen.h>

extern TFT_eSPI tftDisplay;
extern SPIClass touchscreenSPI;


#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 13  // T_DIN
#define XPT2046_MISO 12  // T_OUT
#define XPT2046_CLK 14   // T_CLK
#define XPT2046_CS 33    // T_CS

extern XPT2046_Touchscreen touchscreen;

void clearAllCheckMarks(void);
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void tft_init(void);