#pragma once

#include "ui.h"
#include "lvgl.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "lv_conf.h"
#include "ui.h"

extern TFT_eSPI tftDisplay;
void clearAllCheckMarks(void);
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void tft_init(void);