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
  bool heartbeat;
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
  bool highCellVoltageTrip;
  bool lowCellVoltageTrip;
  bool commonHighCurrentTrip;
  bool motorHighCurrentTrip;
  bool arrayHighCurrentTrip;
  bool lvHighCurrentTrip;
  bool chargeHighCurrentTrip;
  bool protectionTrip;
  bool orionMsgTimeoutTrip;
  bool contactorDiscUnexpected;
  bool contactorConnUnexpected;
  bool commonHeartbeatDead;
  bool motorHeartbeatDead;
  bool arrayHeartbeatDead;
  bool lvHeartbeatDead;
  bool chargeHeartbeatDead;
  bool mpsDisabledTrip;
  bool esdEnabledTrip;
  bool highTempTrip;
  bool lowTempTrip;
};

// POWER SELECTION STATUS
struct PowerSelectionStatus {
  bool nMainPowerSwitch;
  bool externalShutdown;
  bool en1;
  bool nDCDCFault;
  bool n3A_OC;
  bool nDCDC_On;
  bool nCHGFault;
  bool nCHG_On;
  bool nCHG_LV_En;
  bool abattDisable;
  bool key;
};

// MBMS STATUS SCREEN
struct MBMSStatusScreen {
  float auxBatteryVoltage; // scaled value
  bool strobeBMSLight;
  bool nChargeEnable;
  bool nChargeSafety;
  bool nDischargeEnable;
  bool orionCANRx;
  bool dischargeShouldTrip;
  bool chargeShouldTrip;
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