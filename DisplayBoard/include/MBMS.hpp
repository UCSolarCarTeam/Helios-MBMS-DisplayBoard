#pragma once
#include <cstdint>

// ENUMS
enum class PrechargeState : uint8_t {
  OPEN,
  CLOSED,
  CLOSING,
  ERROR
};

enum class ContactorState : uint8_t {
  OPEN,
  CLOSED,
  CLOSING,
  ERROR
};

enum class StartupState : uint8_t {
  nMPS_ENABLED = 0,
  nMPS_DISABLED,
  ESD_DISABLED,
  CHECKS_PASSED,
  COMMON_CLOSED,
  LV_CLOSED,
  EN1_ON,
  MOTORS_PERMS,
  ARRAY_PERMS,
  COMPLETED
};

enum class CarState : uint8_t {
  BOOT,
  STARTUP,
  FULLY_OPERATIONAL,
  CHARGING,
  BPS_FAULT,
  MPS_DISCONNECTED,
  SOFT_TRIP
};

// COMMON STRUCT FOR BOARD STATUS
struct BoardStatus {
  uint8_t heartbeat;
  PrechargeState prechargerState;
  ContactorState contactorState;
  float lineCurrent;   // Scaled from uint12_t
  float chargeCurrent; // Scaled from uint12_t
};

// CONTACTOR SCREEN
struct ContactorScreen {
  BoardStatus commonBoard;
  BoardStatus motorBoard;
  BoardStatus arrayBoard;
  BoardStatus lvBoard;
  BoardStatus chargeBoard;
};

// TRIP SCREEN
struct TripScreen {
  uint8_t highCellVoltageTrip;
  uint8_t lowCellVoltageTrip;
  uint8_t commonHighCurrentTrip;
  uint8_t motorHighCurrentTrip;
  uint8_t arrayHighCurrentTrip;
  uint8_t lvHighCurrentTrip;
  uint8_t chargeHighCurrentTrip;
  uint8_t protectionTrip;
  uint8_t orionMsgTimeoutTrip;
  uint8_t contactorDiscUnexpected;
  uint8_t contactorConnUnexpected;
  uint8_t commonHeartbeatDead;
  uint8_t motorHeartbeatDead;
  uint8_t arrayHeartbeatDead;
  uint8_t lvHeartbeatDead;
  uint8_t chargeHeartbeatDead;
  uint8_t mpsDisabledTrip;
  uint8_t esdEnabledTrip;
  uint8_t highTempTrip;
  uint8_t lowTempTrip;
};

// POWER SELECTION STATUS
struct PowerSelectionStatus {
  uint8_t nMainPowerSwitch;
  uint8_t externalShutdown;
  uint8_t en1;
  uint8_t nDCDCFault;
  uint8_t n3A_OC;
  uint8_t nDCDC_On;
  uint8_t nCHGFault;
  uint8_t nCHG_On;
  uint8_t nCHG_LV_En;
  uint8_t abattDisable;
  uint8_t key;
};

// MBMS STATUS SCREEN
struct MBMSStatusScreen {
  float auxBatteryVoltage; // scaled value
  uint8_t strobeBMSLight;
  uint8_t nChargeEnable;
  uint8_t nChargeSafety;
  uint8_t nDischargeEnable;
  uint8_t orionCANRx;
  uint8_t dischargeShouldTrip;
  uint8_t chargeShouldTrip;
  StartupState startupState; // 4 bits
  CarState systemState; // 3 bits
};

// BATTERY INFO SCREEN
struct BatteryInfoScreen {
  int16_t packCurrent;       // 2 bytes
  uint16_t packVoltage;      // 2 bytes
  uint8_t packSOC;           // 1 byte
  uint16_t packAmphours;     // 2 bytes
  uint8_t packDOD;           // 1 byte
  uint8_t lowTemp;           // 1 byte
  uint8_t avgTemp;           // 1 byte
  uint8_t highTemp;          // 1 byte
  uint16_t lowCellVoltage;   // mV, 2 bytes
  uint16_t highCellVoltage;  // mV, 2 bytes
  uint16_t maxCellVoltage;   // mV, 2 bytes
};

// ROOT DATA STRUCTURE
struct ScreenDataDictionary {
  ContactorScreen contactorScreen;
  TripScreen tripScreen;
  PowerSelectionStatus powerStatus;
  MBMSStatusScreen mbmsStatus;
  BatteryInfoScreen batteryInfo;
};

// Example global dictionary
extern ScreenDataDictionary screenData;