#include "main.h"

ScreenID current_screen = SCREEN_CONTACTOR;
unsigned long lastScreenChangeTime = 0;
const unsigned long screenChangeInterval = 7000; // 7 seconds

TFT_eSPI tftDisplay = TFT_eSPI();

// Use VSPI for comms
volatile bool interrupt = false;
struct can_frame frame;
SPIClass *vspi = new SPIClass(VSPI);

MCP2515 mcp2515(COM_PIN_CS, SPI_CLOCK_SPEED, vspi);

void irqhandler()
{
  interrupt = true;
}

void setup()
{
  Serial.begin(115200);

  vspi->begin(COM_PIN_SCLK, COM_PIN_MISO, COM_PIN_MOSI, COM_PIN_CS);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();

  tft_init();

  attachInterrupt(CAN_PIN_IRQ, irqhandler, FALLING);

  Serial.println("UI initialized, switching screens");
  lv_scr_load(ui_Contactor_Screen);
  lv_refr_now(NULL);
  clearAllCheckMarks();
}

void recieveData()
{
  interrupt = false; // Reset interrupt flag

  uint8_t irq = mcp2515.getInterrupts();

  if (irq & MCP2515::CANINTF_RX0IF)
  {
    if (mcp2515.readMessage(MCP2515::RXB0, &frame) == MCP2515::ERROR_OK)
    {
      Serial.println("Received message from RXB0");
    }
  }

  if (irq & MCP2515::CANINTF_RX1IF)
  {
    if (mcp2515.readMessage(MCP2515::RXB1, &frame) == MCP2515::ERROR_OK)
    {
      Serial.println("Received message from RXB1");
    }
  }
}

void loop()
{

  if (interrupt)
  {
    recieveData();
  }

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