#include <stdint.h>

typedef struct {
  int16_t packCurrent;
  uint16_t packVoltage;
  uint8_t packSOC;
  uint16_t packAmphours;
  uint8_t packDOD;
  uint8_t highTemp;
  uint8_t lowTemp;
  uint8_t avgTemp;
  uint16_t maxCellVoltage;
  uint16_t minCellVoltage;
  uint16_t maxPackVoltage;
  uint16_t minPackVoltage;
} BatteryInfo;
