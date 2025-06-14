#pragma once
#include "MBMS.hpp"

//                                      Parsing Helpers                               //
void parseMBMSStatus(const uint8_t *data, MBMSStatusScreen &status);
void parsePowerSelectionStatus(const uint8_t *data, PowerSelectionStatus &status);
void parseMBMSTrip(const uint8_t *data, TripScreen &status);
void parseHeartbeat(const uint8_t *data, BoardStatus &status);
void parseContactorBoardStatus(const uint8_t *data, BoardStatus &status, bool ignoreLineCurrent);
void parsePackInfo(const uint8_t *data, BatteryInfoScreen &info, BoardStatus &status);
void parseTemperatureInfo(const uint8_t *data, BatteryInfoScreen &info);
void parseCellVoltages(const uint8_t *data, BatteryInfoScreen &info);
void parseMaxCellVoltage(const uint8_t *data, BatteryInfoScreen &info);

void processCAN(void);