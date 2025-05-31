#include "main.h"

ESP32SPISlave slave;
TFT_eSPI tftDisplay = TFT_eSPI();

volatile bool atHomeScreen = true;

constexpr size_t BUFFER_SIZE = 8;
constexpr size_t QUEUE_SIZE = 20;

uint8_t tx_buf[BUFFER_SIZE] = {0};  // Send dummy data
uint8_t rx_buf[BUFFER_SIZE] = {0};  // Will hold received bytes

//Might not be needed but defined for clarity
#define COM_PIN_MISO 27

#define COM_PIN_MOSI 23
#define COM_PIN_SCLK 22
#define COM_PIN_CS 21

void setup(){
  Serial.begin(115200);

  tft_init();

  slave.setDataMode(SPI_MODE0); // Set SPI mode to 0
  slave.setQueueSize(QUEUE_SIZE); // default: 1
  slave.begin(VSPI, COM_PIN_SCLK, COM_PIN_MISO, COM_PIN_MOSI, COM_PIN_CS);
  slave.end();

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_HomeScreen);
  lv_refr_now(NULL);  
  clearAllCheckMarks();
}

void loop(){

  //  size_t received_bytes = slave.transfer(tx_buf, rx_buf, BUFFER_SIZE);

  //   // Print received bytes
  //   if (received_bytes > 0) {
  //       Serial.print("Received: ");
  //       for (size_t i = 0; i < received_bytes; ++i) {
  //           Serial.print(rx_buf[i], HEX);
  //           Serial.print(" ");
  //       }
  //       Serial.println();
  // }

  lv_task_handler(); // Handle LVGL tasks
  lv_refr_now(NULL);
  lv_timer_handler(); // Handle LVGL timers
  delay(5);          // Small delay to allow for task processing
}