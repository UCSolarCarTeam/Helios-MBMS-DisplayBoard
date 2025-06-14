#pragma once
#include "MBMS.hpp"


//                                      Parsing Helpers                               //
void parseMBMSStatus(const uint8_t* data, MBMSStatusScreen& status);
void parsePowerSelectionStatus(const uint8_t* data, PowerSelectionStatus& status);
void parseMBMSTrip(const uint8_t* data, TripScreen& status);



void processCAN(void);