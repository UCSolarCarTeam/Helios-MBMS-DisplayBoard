#include "ScreenUARTDeserializer.h"  
#include <Arduino.h>

#define DEBUG_UART 1

// Helper: Enum to string (feel free to expand/clean these)
const char* toString(PrechargeState s) {
  switch (s) {
    case PrechargeState::OPEN: return "OPEN";
    case PrechargeState::CLOSED: return "CLOSED";
    case PrechargeState::CLOSING: return "CLOSING";
    case PrechargeState::ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}

const char* toString(ContactorState s) {
  switch (s) {
    case ContactorState::OPEN: return "OPEN";
    case ContactorState::CLOSED: return "CLOSED";
    case ContactorState::CLOSING: return "CLOSING";
    case ContactorState::ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}

const char* toString(StartupState s) {
  switch (s) {
    case StartupState::nMPS_ENABLED: return "nMPS_ENABLED";
    case StartupState::nMPS_DISABLED: return "nMPS_DISABLED";
    case StartupState::ESD_DISABLED: return "ESD_DISABLED";
    case StartupState::CHECKS_PASSED: return "CHECKS_PASSED";
    case StartupState::COMMON_CLOSED: return "COMMON_CLOSED";
    case StartupState::LV_CLOSED: return "LV_CLOSED";
    case StartupState::EN1_ON: return "EN1_ON";
    case StartupState::MOTORS_PERMS: return "MOTORS_PERMS";
    case StartupState::ARRAY_PERMS: return "ARRAY_PERMS";
    case StartupState::COMPLETED: return "COMPLETED";
    default: return "UNKNOWN";
  }
}

const char* toString(CarState s) {
  switch (s) {
    case CarState::BOOT: return "BOOT";
    case CarState::STARTUP: return "STARTUP";
    case CarState::FULLY_OPERATIONAL: return "FULLY_OPERATIONAL";
    case CarState::CHARGING: return "CHARGING";
    case CarState::BPS_FAULT: return "BPS_FAULT";
    case CarState::MPS_DISCONNECTED: return "MPS_DISCONNECTED";
    case CarState::SOFT_TRIP: return "SOFT_TRIP";
    default: return "UNKNOWN";
  }
}

void printBoardStatus(const char* label, const BoardStatus& b) {
  Serial.printf("[%s] Heartbeat: %d, Precharge: %s, Contactor: %s, LineCur: %.2f, ChargeCur: %.2f\n",
                label,
                b.heartbeat,
                toString(b.prechargerState),
                toString(b.contactorState),
                b.lineCurrent,
                b.chargeCurrent);
}

void printScreenDataDictionary(const ScreenDataDictionary& d) {

  if(!DEBUG_UART) return; // Only print if debugging is enabled

  Serial.println("======= Screen Data =======");

  printBoardStatus("Common", d.contactorScreen.commonBoard);
  printBoardStatus("Motor", d.contactorScreen.motorBoard);
  printBoardStatus("Array", d.contactorScreen.arrayBoard);
  printBoardStatus("LV",    d.contactorScreen.lvBoard);
  printBoardStatus("Charge", d.contactorScreen.chargeBoard);

  Serial.println("---- Trip Flags ----");
  const uint8_t* trip = reinterpret_cast<const uint8_t*>(&d.tripScreen);
  for (int i = 0; i < 20; ++i) {
    Serial.printf("Trip[%02d] = %u\n", i, trip[i]);
  }

  Serial.println("---- Power Selection ----");
  const uint8_t* power = reinterpret_cast<const uint8_t*>(&d.powerStatus);
  for (int i = 0; i < 11; ++i) {
    Serial.printf("Power[%02d] = %u\n", i, power[i]);
  }

  Serial.println("---- MBMS Status ----");
  Serial.printf("Aux Voltage: %.2f\n", d.mbmsStatus.auxBatteryVoltage);
  Serial.printf("StrobeBMS: %u, nChargeEn: %u, nChargeSafe: %u, nDischargeEn: %u, OrionRx: %u\n",
                d.mbmsStatus.strobeBMSLight,
                d.mbmsStatus.nChargeEnable,
                d.mbmsStatus.nChargeSafety,
                d.mbmsStatus.nDischargeEnable,
                d.mbmsStatus.orionCANRx);
  Serial.printf("DisTrip: %u, ChgTrip: %u\n",
                d.mbmsStatus.dischargeShouldTrip,
                d.mbmsStatus.chargeShouldTrip);
  Serial.printf("StartupState: %s\n", toString(d.mbmsStatus.startupState));
  Serial.printf("SystemState:  %s\n", toString(d.mbmsStatus.systemState));

  Serial.println("---- Battery Info ----");
  Serial.printf("PackCur: %d, Voltage: %u, SOC: %u%%, Ah: %u, DOD: %u%%\n",
                d.batteryInfo.packCurrent,
                d.batteryInfo.packVoltage,
                d.batteryInfo.packSOC,
                d.batteryInfo.packAmphours,
                d.batteryInfo.packDOD);
  Serial.printf("Temps: Low: %u, Avg: %u, High: %u\n",
                d.batteryInfo.lowTemp,
                d.batteryInfo.avgTemp,
                d.batteryInfo.highTemp);
  Serial.printf("CellVoltages: Low: %u, High: %u, Max: %u\n",
                d.batteryInfo.lowCellVoltage,
                d.batteryInfo.highCellVoltage,
                d.batteryInfo.maxCellVoltage);
}
