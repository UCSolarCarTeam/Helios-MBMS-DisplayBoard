#include "main.h"

ScreenID current_screen = SCREEN_CONTACTOR;
unsigned long lastScreenChangeTime = 0;
const unsigned long screenChangeInterval = 7000; // 7 seconds

TFT_eSPI tftDisplay = TFT_eSPI();

ScreenDataDictionary screenData;

void setup()
{
  Serial.begin(115200);

  Serial.println("Starting MBMS UI...");
  Serial.println("Hello");


  tft_init();

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_Contactor_Screen);
  lv_refr_now(NULL);
  clearAllCheckMarks();
}


void loop()
{

  unsigned long currentTime = millis();
  if (currentTime - lastScreenChangeTime >= screenChangeInterval)
  {
    lastScreenChangeTime = currentTime;
    load_next_screen(); // Cycle to next screen
  }

  lv_task_handler(); // Handle LVGL tasks
  lv_refr_now(NULL);
  lv_timer_handler(); // Handle LVGL timers
  delay(5);           // Small delay to allow for task processing
}