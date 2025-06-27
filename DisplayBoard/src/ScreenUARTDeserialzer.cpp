#include "ScreenUARTDeserializer.h"
#include "debug.h"
#include <cstring>  // for memcpy


// Helpers
static void read_uint8(const uint8_t **buf_ptr, uint8_t &val) {
    val = **buf_ptr;
    (*buf_ptr)++;
}

static void read_uint16(const uint8_t **buf_ptr, uint16_t &val) {
    val  = (*buf_ptr)[0];
    val |= ((uint16_t)(*buf_ptr)[1]) << 8;
    *buf_ptr += 2;
}

static void read_int16(const uint8_t **buf_ptr, int16_t &val) {
    uint16_t temp;
    read_uint16(buf_ptr, temp);
    val = (int16_t)temp;
}

static void read_float(const uint8_t **buf_ptr, float &val) {
    memcpy(&val, *buf_ptr, sizeof(float));
    *buf_ptr += sizeof(float);
}

bool deserializeScreenData(ScreenDataDictionary &out, const uint8_t *buffer, size_t len) {
    const uint8_t *p = buffer;

    // Helper macro
    #define READ_BOARDSTATUS(bs) \
        read_uint8(&p, bs.heartbeat); \
        { uint8_t tmp; read_uint8(&p, tmp); bs.prechargerState = static_cast<PrechargeState>(tmp); } \
        { uint8_t tmp; read_uint8(&p, tmp); bs.contactorState  = static_cast<ContactorState>(tmp); } \
        read_float(&p, bs.lineCurrent); \
        read_float(&p, bs.chargeCurrent);

    // ContactorScreen
    READ_BOARDSTATUS(out.contactorScreen.commonBoard);
    READ_BOARDSTATUS(out.contactorScreen.motorBoard);
    READ_BOARDSTATUS(out.contactorScreen.arrayBoard);
    READ_BOARDSTATUS(out.contactorScreen.lvBoard);
    READ_BOARDSTATUS(out.contactorScreen.chargeBoard);

    // TripScreen
    #define READ_TRIP(trip) read_uint8(&p, out.tripScreen.trip)
    READ_TRIP(highCellVoltageTrip);
    READ_TRIP(lowCellVoltageTrip);
    READ_TRIP(commonHighCurrentTrip);
    READ_TRIP(motorHighCurrentTrip);
    READ_TRIP(arrayHighCurrentTrip);
    READ_TRIP(lvHighCurrentTrip);
    READ_TRIP(chargeHighCurrentTrip);
    READ_TRIP(protectionTrip);
    READ_TRIP(orionMsgTimeoutTrip);
    READ_TRIP(contactorDiscUnexpected);
    READ_TRIP(contactorConnUnexpected);
    READ_TRIP(commonHeartbeatDead);
    READ_TRIP(motorHeartbeatDead);
    READ_TRIP(arrayHeartbeatDead);
    READ_TRIP(lvHeartbeatDead);
    READ_TRIP(chargeHeartbeatDead);
    READ_TRIP(mpsDisabledTrip);
    READ_TRIP(esdEnabledTrip);
    READ_TRIP(highTempTrip);
    READ_TRIP(lowTempTrip);

    // PowerSelectionStatus
    read_uint8(&p, out.powerStatus.nMainPowerSwitch);
    read_uint8(&p, out.powerStatus.externalShutdown);
    read_uint8(&p, out.powerStatus.en1);
    read_uint8(&p, out.powerStatus.nDCDCFault);
    read_uint8(&p, out.powerStatus.n3A_OC);
    read_uint8(&p, out.powerStatus.nDCDC_On);
    read_uint8(&p, out.powerStatus.nCHGFault);
    read_uint8(&p, out.powerStatus.nCHG_On);
    read_uint8(&p, out.powerStatus.nCHG_LV_En);
    read_uint8(&p, out.powerStatus.abattDisable);
    read_uint8(&p, out.powerStatus.key);

    // MBMSStatusScreen
    read_float(&p, out.mbmsStatus.auxBatteryVoltage);
    read_uint8(&p, out.mbmsStatus.strobeBMSLight);
    read_uint8(&p, out.mbmsStatus.nChargeEnable);
    read_uint8(&p, out.mbmsStatus.nChargeSafety);
    read_uint8(&p, out.mbmsStatus.nDischargeEnable);
    read_uint8(&p, out.mbmsStatus.orionCANRx);
    read_uint8(&p, out.mbmsStatus.dischargeShouldTrip);
    read_uint8(&p, out.mbmsStatus.chargeShouldTrip);
    { uint8_t tmp; read_uint8(&p, tmp); out.mbmsStatus.startupState = static_cast<StartupState>(tmp); }
    { uint8_t tmp; read_uint8(&p, tmp); out.mbmsStatus.systemState  = static_cast<CarState>(tmp); }

    // BatteryInfoScreen
    read_int16(&p,  out.batteryInfo.packCurrent);
    read_uint16(&p, out.batteryInfo.packVoltage);
    read_uint8(&p,  out.batteryInfo.packSOC);
    read_uint16(&p, out.batteryInfo.packAmphours);
    read_uint8(&p,  out.batteryInfo.packDOD);
    read_uint8(&p,  out.batteryInfo.lowTemp);
    read_uint8(&p,  out.batteryInfo.avgTemp);
    read_uint8(&p,  out.batteryInfo.highTemp);
    read_uint16(&p, out.batteryInfo.lowCellVoltage);
    read_uint16(&p, out.batteryInfo.highCellVoltage);
    read_uint16(&p, out.batteryInfo.maxCellVoltage);

    return true;
}


void UARTReceiverTask(void *pvParameters){
   while (true) {
    int len = uart1.readBytes(rxBuffer, UART_BUFFER_SIZE);
    if (len > 0) {
      ScreenDataDictionary temp;
      if (deserializeScreenData(temp, rxBuffer, len)) {
        screenData = temp; // copy into global
        updateUI();
        Serial.println("Received and deserialized screen data.");
      } else {
        Serial.println("Failed to deserialize data.");
      }
    }
    vTaskDelay(pdMS_TO_TICKS(100)); // small delay
  }
}