#pragma once
#include <stdint.h>
#include <Arduino.h>
#include "MBMS.hpp"
#include "lvgl.h"
#include "ui.h"

typedef enum {
    SCREEN_CONTACTOR = 0,
    SCREEN_TRIP,
    SCREEN_BATTERY_INFO,
    SCREEN_MBMS_STATUS,
    SCREEN_POWER_SELECTION,
    NUM_SCREENS
} ScreenID;

extern lv_obj_t ** screen_list[NUM_SCREENS];
extern ScreenID current_screen;

void load_screen(ScreenID screen_id);
void load_next_screen(void);
ScreenID get_current_screen(void);


void updateUI(void);
void updateBatteryInfoUI();
void mbmsStatusScreenUpdate(void);
void powerSelectionStatusScreenUpdate(void);
void tripScreenUpdate(void);
void setCheckboxState(lv_obj_t* checkbox, bool checked);