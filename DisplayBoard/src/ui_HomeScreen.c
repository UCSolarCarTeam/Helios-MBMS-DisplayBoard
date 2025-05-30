// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: MBMS_Display

#include "ui.h"

void ui_HomeScreen_screen_init(void)
{
    ui_HomeScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_HomeScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ContactorStatusBtn = lv_btn_create(ui_HomeScreen);
    lv_obj_set_width(ui_ContactorStatusBtn, 303);
    lv_obj_set_height(ui_ContactorStatusBtn, 50);
    lv_obj_set_x(ui_ContactorStatusBtn, 1);
    lv_obj_set_y(ui_ContactorStatusBtn, -77);
    lv_obj_set_align(ui_ContactorStatusBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ContactorStatusBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ContactorStatusBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ContactorStatusLabel = lv_label_create(ui_HomeScreen);
    lv_obj_set_width(ui_ContactorStatusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ContactorStatusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ContactorStatusLabel, 12);
    lv_obj_set_y(ui_ContactorStatusLabel, -78);
    lv_obj_set_align(ui_ContactorStatusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ContactorStatusLabel, "Contactor &\nPrecharger Status");
    lv_obj_set_style_text_color(ui_ContactorStatusLabel, lv_color_hex(0xFEFEFE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ContactorStatusLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ContactorStatusLabel, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TripBtn = lv_btn_create(ui_HomeScreen);
    lv_obj_set_width(ui_TripBtn, 135);
    lv_obj_set_height(ui_TripBtn, 54);
    lv_obj_set_x(ui_TripBtn, -83);
    lv_obj_set_y(ui_TripBtn, -6);
    lv_obj_set_align(ui_TripBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_TripBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_TripBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_TripBtn, lv_color_hex(0xEC4707), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TripBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TripLabel = lv_label_create(ui_HomeScreen);
    lv_obj_set_width(ui_TripLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TripLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TripLabel, -82);
    lv_obj_set_y(ui_TripLabel, -4);
    lv_obj_set_align(ui_TripLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TripLabel, "Trip Status");
    lv_obj_set_style_text_color(ui_TripLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TripLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TripLabel, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BatteryBtn = lv_btn_create(ui_HomeScreen);
    lv_obj_set_width(ui_BatteryBtn, 139);
    lv_obj_set_height(ui_BatteryBtn, 54);
    lv_obj_set_x(ui_BatteryBtn, 82);
    lv_obj_set_y(ui_BatteryBtn, -5);
    lv_obj_set_align(ui_BatteryBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BatteryBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_BatteryBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BatteryBtn, lv_color_hex(0xEFB91C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BatteryBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BatteryLabel = lv_label_create(ui_HomeScreen);
    lv_obj_set_width(ui_BatteryLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BatteryLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BatteryLabel, 83);
    lv_obj_set_y(ui_BatteryLabel, -4);
    lv_obj_set_align(ui_BatteryLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BatteryLabel, "Battery Info");
    lv_obj_set_style_text_color(ui_BatteryLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BatteryLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BatteryLabel, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBMSBtn = lv_btn_create(ui_HomeScreen);
    lv_obj_set_width(ui_MBMSBtn, 136);
    lv_obj_set_height(ui_MBMSBtn, 63);
    lv_obj_set_x(ui_MBMSBtn, 82);
    lv_obj_set_y(ui_MBMSBtn, 70);
    lv_obj_set_align(ui_MBMSBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MBMSBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MBMSBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MBMSBtn, lv_color_hex(0x0FC22E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MBMSBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MBMSLabel = lv_label_create(ui_HomeScreen);
    lv_obj_set_width(ui_MBMSLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MBMSLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MBMSLabel, 83);
    lv_obj_set_y(ui_MBMSLabel, 71);
    lv_obj_set_align(ui_MBMSLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MBMSLabel, "MBMS\nStatus");
    lv_obj_set_style_text_color(ui_MBMSLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MBMSLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MBMSLabel, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PowerSelectBtn = lv_btn_create(ui_HomeScreen);
    lv_obj_set_width(ui_PowerSelectBtn, 135);
    lv_obj_set_height(ui_PowerSelectBtn, 63);
    lv_obj_set_x(ui_PowerSelectBtn, -83);
    lv_obj_set_y(ui_PowerSelectBtn, 70);
    lv_obj_set_align(ui_PowerSelectBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_PowerSelectBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_PowerSelectBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PowerSelectBtn, lv_color_hex(0x9D1BCD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PowerSelectBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PowerSelectLabel = lv_label_create(ui_HomeScreen);
    lv_obj_set_width(ui_PowerSelectLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_PowerSelectLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_PowerSelectLabel, -82);
    lv_obj_set_y(ui_PowerSelectLabel, 71);
    lv_obj_set_align(ui_PowerSelectLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PowerSelectLabel, "Power \nStatus");
    lv_obj_set_style_text_color(ui_PowerSelectLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_PowerSelectLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_PowerSelectLabel, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ContactorStatusBtn, ui_event_ContactorStatusBtn, LV_EVENT_ALL, NULL);

}
