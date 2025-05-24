#include "tft_helper.h"

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

    lv_obj_clear_state(ui_OrionCanReceivedCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_DischargeShouldTripCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeShouldTripCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_StrobeBMSLightCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_AllowChargeCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_HighVoltageEnableStateCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_AllowDischargeCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeSafetyCheck, LV_STATE_CHECKED);

    lv_obj_clear_state(ui_ExternalShutdownCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_DCDCFaultCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeFaultCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_DCDCOnCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeOnCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ThreeAmpOverCurrentCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_AuxBattDisableCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeLVEnableCheck, LV_STATE_CHECKED);
}

void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data) {
  if (touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    data->point.x = p.x;
    data->point.y = p.y;
    Serial.print("X: ");
    Serial.print(data->point.x);
    Serial.print(" Y: "); 
    Serial.print(data->point.y);
    data->state = LV_INDEV_STATE_PR;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void calibrateTouch() {
  tftDisplay.init();
  tftDisplay.setRotation(1);
  tftDisplay.fillScreen(TFT_BLACK);
  tftDisplay.setTextColor(TFT_WHITE, TFT_BLACK);
  tftDisplay.setTextSize(2);

  // Top-left corner
  tftDisplay.fillScreen(TFT_BLACK);
  tftDisplay.setCursor(20, 50);
  tftDisplay.println("Touch the");
  tftDisplay.setCursor(20, 80);
  tftDisplay.println("TOP-LEFT corner");
  tftDisplay.fillCircle(10, 10, 5, TFT_RED); // Visual indicator
  
  while (!touchscreen.touched()) {}
  TS_Point p1 = touchscreen.getPoint();
  while (touchscreen.touched()) {} // Wait for release
  delay(200);

  // Bottom-right corner
  tftDisplay.fillScreen(TFT_BLACK);
  tftDisplay.setCursor(20, 50);
  tftDisplay.println("Touch the");
  tftDisplay.setCursor(20, 80);
  tftDisplay.println("BOTTOM-RIGHT corner");
  tftDisplay.fillCircle(310, 230, 5, TFT_RED); // Visual indicator
  
  while (!touchscreen.touched()) {}
  TS_Point p2 = touchscreen.getPoint();
  while (touchscreen.touched()) {} // Wait for release
  delay(200);

  // Calculate calibration values
  int min_x = min(p1.x, p2.x);
  int max_x = max(p1.x, p2.x);
  int min_y = min(p1.y, p2.y);
  int max_y = max(p1.y, p2.y);

  // Show results on screen
  tftDisplay.fillScreen(TFT_BLACK);
  tftDisplay.setCursor(10, 30);
  tftDisplay.println("Calibration Complete");
  
  tftDisplay.setCursor(10, 70);
  tftDisplay.print("X: ");
  tftDisplay.print(min_x);
  tftDisplay.print(" - ");
  tftDisplay.println(max_x);
  
  tftDisplay.setCursor(10, 100);
  tftDisplay.print("Y: ");
  tftDisplay.print(min_y);
  tftDisplay.print(" - ");
  tftDisplay.println(max_y);

  tftDisplay.setCursor(10, 150);
  tftDisplay.println("Use these values in");
  tftDisplay.setCursor(10, 180);
  tftDisplay.println("your map() function");

  // Also print to Serial for reference
  Serial.println("Calibration values:");
  Serial.print("X range: "); Serial.print(min_x); Serial.print(" - "); Serial.println(max_x);
  Serial.print("Y range: "); Serial.print(min_y); Serial.print(" - "); Serial.println(max_y);
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


void tft_init(void){
  lv_init(); // Initialize LVGL

  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  if(touchscreen.begin(touchscreenSPI)){
    Serial.println("Touchscreen initialized successfully");
  } else {
    Serial.println("Touchscreen initialization failed");
  }
  touchscreen.setRotation(1); 

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

  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  pinMode(19,OUTPUT);
  digitalWrite(19,HIGH);

  ui_init();
  calibrateTouch();
}