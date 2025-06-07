#include "main.h"

ScreenID current_screen = SCREEN_CONTACTOR;
unsigned long lastScreenChangeTime = 0;
const unsigned long screenChangeInterval = 7000; // 7 seconds

ESP32SPISlave slave;
TFT_eSPI tftDisplay = TFT_eSPI();

volatile bool atHomeScreen = true;

//139
constexpr size_t BUFFER_SIZE = 32;
constexpr size_t QUEUE_SIZE = 10;

uint8_t tx_buf[BUFFER_SIZE] = {0};  // Send dummy data
uint8_t rx_buf[BUFFER_SIZE] = {0};  // Will hold received bytes


void setup(){
  Serial.begin(115200);

  tft_init();

  slave.setDataMode(SPI_MODE0); // Set SPI mode to 0
  slave.setQueueSize(QUEUE_SIZE); // default: 1
  slave.begin(VSPI, COM_PIN_SCLK, COM_PIN_MISO, COM_PIN_MOSI, COM_PIN_CS);

  tftDisplay.endWrite();

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_Contactor_Screen);
  lv_refr_now(NULL);  
  clearAllCheckMarks();
}

void recieveData(){
   size_t received_bytes = slave.transfer(tx_buf, rx_buf, BUFFER_SIZE);

    // Print received bytes
    if (received_bytes > 0) {
        Serial.print("Received: ");
        for (size_t i = 0; i < received_bytes; ++i) {

            // Serial.print((char)rx_buf[i]);  // or use HEX if preferred
            Serial.printf("%02X ", rx_buf[i]);
            // Serial.print(rx_buf[i], HEX);
        }
        Serial.println();

        // updateBatteryInfoUI(rx_buf, received_bytes); // Update UI with received data
  }
}

void loop(){

  recieveData(); // Receive data from SPI slave

  unsigned long currentTime = millis();
    if (currentTime - lastScreenChangeTime >= screenChangeInterval) {
        lastScreenChangeTime = currentTime;
        load_next_screen();  // Cycle to next screen
    }

  lv_task_handler(); // Handle LVGL tasks
  lv_refr_now(NULL);
  lv_timer_handler(); // Handle LVGL timers
  delay(5);          // Small delay to allow for task processing
}