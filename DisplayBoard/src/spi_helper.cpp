#include "spi_helper.h"


void processCAN(void){
    //TODO: Contactor Screen : Name | Precharger State | Contactor State | Line Current | Charge Current
    //TODO: Battery Info Screen : Low Cell Voltage, High Cell Voltage  

    //TODO : Take this as extended ID to parse bits 0-29
    uint16_t id = frame.can_id & 0x7FF;
    const uint8_t* data = frame.data;
    uint8_t len = frame.can_dlc;

    Serial.printf("\nReceived CAN ID: 0x%X, Length: %d, Data: ", id, len);
    switch(id) {
        case 0x102:
            parseMBMSStatus(data, screenData.mbmsStatus);
            break;
        case 0x103:
            parsePowerSelectionStatus(data, screenData.powerStatus);
            break;
        case 0x104:
            parseMBMSTrip(data, screenData.tripScreen);
            break;
        case 0x200:
            parseHeartbeat(data, screenData.contactorScreen.commonBoard);
            break;
        case 0x201:
            parseHeartbeat(data, screenData.contactorScreen.motorBoard);
            break;
        case 0x202:
            parseHeartbeat(data, screenData.contactorScreen.arrayBoard);
            break;
        case 0x203:
            parseHeartbeat(data, screenData.contactorScreen.lvBoard);
            break;
        case 0x204:
            parseHeartbeat(data, screenData.contactorScreen.chargeBoard);
            break;
        case 0x210:
            parseContactorBoardStatus(data, screenData.contactorScreen.commonBoard, /*ignoreLineCurrent=*/true);
            break;
        case 0x211:
            parseContactorBoardStatus(data, screenData.contactorScreen.motorBoard, /*ignoreLineCurrent=*/false);
            break;
        case 0x212:
            parseContactorBoardStatus(data, screenData.contactorScreen.arrayBoard, /*ignoreLineCurrent=*/false);
            break;
        case 0x213:
            parseContactorBoardStatus(data, screenData.contactorScreen.lvBoard, /*ignoreLineCurrent=*/false);
            break;
        case 0x214:
            parseContactorBoardStatus(data, screenData.contactorScreen.chargeBoard, /*ignoreLineCurrent=*/false);
            break;
        case 0x302:
            parsePackInfo(data, screenData.batteryInfo, screenData.contactorScreen.commonBoard);
            break;
        case 0x304:
            parseTemperatureInfo(data, screenData.batteryInfo);
            break;
        case 0x305:
            parseCellVoltages(data, screenData.batteryInfo);
            break;
        case 0x30A:
            parseMaxCellVoltage(data, screenData.batteryInfo);
            break;
        default:
            Serial.printf("Unhandled CAN ID: 0x%X\n", id);
            break;
    }

}