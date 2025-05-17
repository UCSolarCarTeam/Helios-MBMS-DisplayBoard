#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "lv_conf.h"
#include "ui.h"

TFT_eSPI tftDisplay = TFT_eSPI();

void clearAllCheckMarks(void)
{
    lv_obj_clear_state(ui_HighCellVoltageTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LowCellVoltageTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_CommonHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MotorHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ArrayHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LVHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ProtectionTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_OrionMsgTimeoutTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_HighBatteryTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ESDEnabledTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_HighTempTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MPSDisabledTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LowTempTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_CommonHeartBeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MotorHeartbeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ArrayHeartbeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeHeartbeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ContactorDisconnectedUnexpectedlyTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ContactorConnectedUnexpectedlyTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LVHeartBeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeHighCurrTrip, LV_STATE_CHECKED);

    lv_obj_clear_state(ui_ArrayCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LowVCheck, LV_STATE_CHECKED); 
    lv_obj_clear_state(ui_ChargeCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_PreChargerCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MotorCheck, LV_STATE_CHECKED);
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint16_t c;

  tftDisplay.startWrite();
  tftDisplay.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1));

  for (int y = area->y1; y <= area->y2; y++)
  {
    for (int x = area->x1; x <= area->x2; x++)
    {
      c = color_p->full; // Convert color
      tftDisplay.pushColor(c);
      color_p++;
    }
  }
  tftDisplay.endWrite();

  lv_disp_flush_ready(disp); // Tell LVGL that flushing is done
}


void setup(){
  Serial.begin(115200);

  lv_init(); // Initialize LVGL

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
  delay(4000);
  lv_scr_load(ui_TripScreen);
  lv_refr_now(NULL);  
  clearAllCheckMarks();
}

void loop(){


  lv_task_handler(); // Handle LVGL tasks
  lv_refr_now(NULL);  
  lv_timer_handler(); // Handle LVGL timers
  delay(5);          // Small delay to allow for task processing
}