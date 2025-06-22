#include "CAN.hpp"

void parseMBMSStatus(const uint8_t* data, MBMSStatusScreen& status) {

    uint8_t voltageBits = data[0] & 0x1F; // bits 0–4
    status.auxBatteryVoltage = voltageBits * 1.0f; 

    status.strobeBMSLight        = (data[0] >> 5) & 0x01;
    status.nChargeEnable         = (data[0] >> 6) & 0x01;
    status.nChargeSafety         = (data[0] >> 7) & 0x01;


    status.nDischargeEnable      = (data[1] >> 0) & 0x01;
    status.orionCANRx            = (data[1] >> 1) & 0x01;
    status.dischargeShouldTrip   = (data[1] >> 2) & 0x01;
    status.chargeShouldTrip      = (data[1] >> 3) & 0x01;

    status.startupState = static_cast<StartupState>((data[1] >> 4) & 0x0F);
    status.systemState  = static_cast<CarState>((data[2]) & 0x07);         // bits 0–2
}

void parsePowerSelectionStatus(const uint8_t* data ,PowerSelectionStatus& status) {
    uint16_t raw = (static_cast<uint16_t>(data[1]) << 8) | data[0];

    status.nMainPowerSwitch  = (raw >> 0) & 0x01;
    status.externalShutdown  = (raw >> 1) & 0x01;
    status.en1               = (raw >> 2) & 0x01;
    status.nDCDCFault        = (raw >> 3) & 0x01;
    status.n3A_OC            = (raw >> 4) & 0x01;
    status.nDCDC_On          = (raw >> 5) & 0x01;
    status.nCHGFault         = (raw >> 6) & 0x01;
    status.nCHG_On           = (raw >> 7) & 0x01;
    status.nCHG_LV_En        = (raw >> 8) & 0x01;
    status.abattDisable      = (raw >> 9) & 0x01;
    status.key               = (raw >> 10) & 0x01;
}

void parseMBMSTrip(const uint8_t* data, TripScreen& status) {
    uint32_t raw = static_cast<uint32_t>(data[2] << 16 | data[1] << 8 | data[0]);

    status.highCellVoltageTrip         = (raw >> 0)  & 0x01;
    status.lowCellVoltageTrip          = (raw >> 1)  & 0x01;
    status.commonHighCurrentTrip       = (raw >> 2)  & 0x01;
    status.motorHighCurrentTrip        = (raw >> 3)  & 0x01;
    status.arrayHighCurrentTrip        = (raw >> 4)  & 0x01;
    status.lvHighCurrentTrip           = (raw >> 5)  & 0x01;
    status.chargeHighCurrentTrip       = (raw >> 6)  & 0x01;
    status.protectionTrip              = (raw >> 7)  & 0x01;
    status.orionMsgTimeoutTrip         = (raw >> 8)  & 0x01;
    status.contactorDiscUnexpected     = (raw >> 9)  & 0x01;
    status.contactorConnUnexpected     = (raw >> 10) & 0x01;
    status.commonHeartbeatDead         = (raw >> 11) & 0x01;
    status.motorHeartbeatDead          = (raw >> 12) & 0x01;
    status.arrayHeartbeatDead          = (raw >> 13) & 0x01;
    status.lvHeartbeatDead             = (raw >> 14) & 0x01;
    status.chargeHeartbeatDead         = (raw >> 15) & 0x01;
    status.mpsDisabledTrip             = (raw >> 16) & 0x01;
    status.esdEnabledTrip              = (raw >> 17) & 0x01;
    status.highTempTrip                = (raw >> 18) & 0x01;
    status.lowTempTrip                 = (raw >> 19) & 0x01;
}

void parseHeartbeat(const uint8_t* data, BoardStatus &status) {
    uint16_t bits = static_cast<uint16_t>(data[1] << 8 | data[0]);
    status.heartbeat = bits != 0;
}

void parseContactorBoardStatus(const uint8_t* data, BoardStatus &status, bool ignoreLineCurrent = false) {
    // Byte array to 32-bit bitfield
    uint32_t bits = (static_cast<uint32_t>(data[3]) << 24) |
                    (static_cast<uint32_t>(data[2]) << 16) |
                    (static_cast<uint32_t>(data[1]) << 8)  |
                    static_cast<uint32_t>(data[0]);

    // --- Precharger State ---
    const bool prechargerOpenClosed = bits & (1 << 0);
    const bool prechargerClosing    = bits & (1 << 1);
    const bool prechargerError      = bits & (1 << 2);

    if (prechargerError) {
        status.prechargerState = PrechargeState::ERROR;
    } else if (prechargerClosing) {
        status.prechargerState = PrechargeState::CLOSING;
    } else if (prechargerOpenClosed) {
        status.prechargerState = PrechargeState::CLOSED;
    } else {
        status.prechargerState = PrechargeState::OPEN;
    }

    // --- Contactor State ---
    const bool contactorOpenClosed = bits & (1 << 3);
    const bool contactorClosing    = bits & (1 << 4);
    const bool contactorError      = bits & (1 << 5);

    if (contactorError) {
        status.contactorState = ContactorState::ERROR;
    } else if (contactorClosing) {
        status.contactorState = ContactorState::CLOSING;
    } else if (contactorOpenClosed) {
        status.contactorState = ContactorState::CLOSED;
    } else {
        status.contactorState = ContactorState::OPEN;
    }

    // --- Line Current (bits 6–17, 12 bits) ---
    uint16_t lineCurrentRaw = static_cast<uint16_t>((bits >> 6) & 0x0FFF);
    float scalingFactor = 0.1f; 
    if (!ignoreLineCurrent) {
        status.lineCurrent = static_cast<float>(lineCurrentRaw * scalingFactor);
    }

    // --- Charge Current (bits 18–29, 12 bits) ---
    uint16_t chargeCurrentRaw = static_cast<uint16_t>((bits >> 18) & 0x0FFF);
    status.chargeCurrent = static_cast<float>(chargeCurrentRaw * scalingFactor);

    // Bit 30 is ignored here
}

void parsePackInfo(const uint8_t* data, BatteryInfoScreen& info, BoardStatus& status) {
    // Bytes 0–1: Pack Current (signed, scale 0.1 A)
    int16_t rawCurrent = static_cast<int16_t>((data[1] << 8) | data[0]);
    info.packCurrent = rawCurrent * 0.1f;
    status.lineCurrent = info.packCurrent; // For Common Board Contactor, line current is the same as pack current

    // Bytes 2–3: Pack Voltage (unsigned, scale 0.1 V)
    uint16_t rawVoltage = (data[3] << 8) | data[2];
    info.packVoltage = rawVoltage * 0.1f;

    // Byte 4: SOC (% * 0.5)
    info.packSOC = static_cast<uint8_t>(data[4] * 0.5f);

    // Bytes 5–6: Amphours (unsigned, scale 0.1 Ah)
    uint16_t rawAmphours = (data[6] << 8) | data[5];
    info.packAmphours = rawAmphours * 0.1f;

    // Byte 7: DOD (% * 0.5)
    info.packDOD = static_cast<uint8_t>(data[7] * 0.5f);
}

void parseTemperatureInfo(const uint8_t* data, BatteryInfoScreen& info) {
    // Byte 0: High Temperature (°C)
    info.highTemp = data[0];

    // Byte 1: High Thermistor ID → not used

    // Byte 2: Low Temperature (°C)
    info.lowTemp = data[2];

    // Byte 3: Low Thermistor ID → not used

    // Byte 4: Average Temperature (°C)
    info.avgTemp = data[4];

    // Byte 5: Internal Temperature → not used
    // Byte 6: Fan Speed (0–6) → not used
}


void parseCellVoltages(const uint8_t* data, BatteryInfoScreen& info) {
    // Byte 0-1: Low Cell Voltage (0.1 mV units)
    uint16_t lowRaw = (static_cast<uint16_t>(data[0]) << 8) | data[1];
    info.lowCellVoltage = static_cast<uint16_t>(lowRaw * 0.1f);  // Convert to mV

    // Byte 2: Low Cell Voltage ID → not used

    // Byte 3-4: High Cell Voltage (0.1 mV units)
    uint16_t highRaw = (static_cast<uint16_t>(data[3]) << 8) | data[4];
    info.highCellVoltage = static_cast<uint16_t>(highRaw * 0.1f);  // Convert to mV

    // Byte 5: High Cell Voltage ID → not used

    // Byte 6-7: Average Cell Voltage → not stored in BatteryInfoScreen (optional)
}

void parseMaxCellVoltage(const uint8_t* data, BatteryInfoScreen& info) {
    // Byte 0-1: Maximum Cell Voltage
    info.maxCellVoltage = (static_cast<uint16_t>(data[0]) << 8) | data[1];
}
