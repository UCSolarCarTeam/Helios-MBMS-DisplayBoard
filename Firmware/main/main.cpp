#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "lv_conf.h"
#include "ui.h"
#include "tft_helper.h"
#include "spi_helper.h"

TFT_eSPI tftDisplay = TFT_eSPI();
//USE HSPI for comms from MBMS

volatile bool atHomeScreen = true;

void setup(){

  initArduino(); // Initialize Arduino framework
  lv_init();
  Serial.begin(115200);

  // Start the tft display
  tftDisplay.init();
  // Set the TFT display rotation in landscape mode
  tftDisplay.setRotation(1);

  // Initialize display buffer and driver
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[LV_HOR_RES_MAX * 10]; // Buffer for 10 lines
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  static lv_disp_drv_t disp_drv;     // Display driver
  lv_disp_drv_init(&disp_drv);       // Basic initialization
  disp_drv.hor_res = 320;            // Set horizontal resolution
  disp_drv.ver_res = 240;            // Set vertical resolution
  disp_drv.flush_cb = my_disp_flush; // Set flush callback
  disp_drv.draw_buf = &draw_buf;     // Assign the buffer to the driver
  lv_disp_drv_register(&disp_drv);   // Register the driver

  pinMode(19,OUTPUT);
  digitalWrite(19,HIGH);

  ui_init();

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_HomeScreen);
  lv_refr_now(NULL);  
  clearAllCheckMarks();
}

extern "C" void app_main(){

  setup();

}