#include "main.h"
#include "debug.h"

ScreenID current_screen = SCREEN_CONTACTOR;
unsigned long lastScreenChangeTime = 0;
const unsigned long screenChangeInterval = 7000; // 7 seconds

TFT_eSPI tftDisplay = TFT_eSPI();

HardwareSerial uart1(1);  
uint8_t rxBuffer[UART_BUFFER_SIZE];


ScreenDataDictionary screenData;

void setup()
{
  Serial.begin(115200);
  uart1.begin(UART_BAUD_RATE, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);

  Serial.println("Starting MBMS UI...");
  Serial.println("Hello");


  tft_init();

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_Contactor_Screen);
  lv_refr_now(NULL);
  clearAllCheckMarks();

  xTaskCreate(UARTReceiverTask, "UART Receiver Task", 4096, NULL, 5, NULL);
}


void loop()
{

  printScreenDataDictionary(screenData); // Print screen data for debugging
  
  unsigned long currentTime = millis();
  if (currentTime - lastScreenChangeTime >= screenChangeInterval)
  {
    lastScreenChangeTime = currentTime;
    load_next_screen(); // Cycle to next screen
  }

  lv_task_handler(); // Handle LVGL tasks
  lv_refr_now(NULL);
  lv_timer_handler(); // Handle LVGL timers
  delay(700);           // Small delay to allow for task processing
}