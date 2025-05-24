#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "lv_conf.h"
#include "ui.h"
#include "tft_helper.h"
#include "spi_helper.h"
#include <XPT2046_Touchscreen.h>

TFT_eSPI tftDisplay = TFT_eSPI();
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
SPIClass touchscreenSPI = SPIClass(VSPI);

volatile bool atHomeScreen = true;

void setup(){
  Serial.begin(115200);

  tft_init();
  //setupSPI();

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_HomeScreen);
  lv_refr_now(NULL);  
  clearAllCheckMarks();
}

void loop(){

  // uint8_t recvbuf[MAX_TRANSFER_SIZE];
  // size_t received_len = 0;
  // receiveSPIMessage(recvbuf, sizeof(recvbuf), &received_len);

  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    handleTouchscreen();
  }

  lv_task_handler(); // Handle LVGL tasks
  lv_refr_now(NULL);
  lv_timer_handler(); // Handle LVGL timers
  delay(5);          // Small delay to allow for task processing
}