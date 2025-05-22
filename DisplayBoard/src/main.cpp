#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "lv_conf.h"
#include "ui.h"
#include "tft_helper.h"

TFT_eSPI tftDisplay = TFT_eSPI();

#include <XPT2046_Touchscreen.h>


//PRODUCTION PIN DEFINITIONS
// #define XPT2046_IRQ 36   // T_IRQ
// #define XPT2046_MOSI 32  // T_DIN
// #define XPT2046_MISO 39  // T_OUT
// #define XPT2046_CLK 25   // T_CLK
// #define XPT2046_CS 33    // T_CS

//PERFBOARD PIN DEFINITIONS
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 23  // T_DIN
#define XPT2046_MISO 21  // T_OUT
#define XPT2046_CLK 18   // T_CLK
#define XPT2046_CS 33    // T_CS



void setup(){
  Serial.begin(115200);

  tft_init();

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_PowerSelectionStatusScreen);
  lv_refr_now(NULL);  
  clearAllCheckMarks();
}

void loop(){


  lv_task_handler(); // Handle LVGL tasks
  lv_refr_now(NULL);  
  lv_timer_handler(); // Handle LVGL timers
  delay(5);          // Small delay to allow for task processing
}