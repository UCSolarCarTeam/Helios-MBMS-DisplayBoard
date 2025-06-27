#include "ui_update.h"

lv_obj_t **screen_list[NUM_SCREENS] = {
    &ui_Contactor_Screen,
    &ui_TripScreen,
    &ui_BatteryInfoScreen,
    &ui_MBMSStatusScreen,
    &ui_PowerSelectionStatusScreen};

void load_screen(ScreenID screen_id)
{
    if (screen_id >= NUM_SCREENS)
        return;

    current_screen = screen_id;
    if (*screen_list[screen_id])
    {
        lv_scr_load(*screen_list[screen_id]);
    }
}

void load_next_screen(void)
{
    ScreenID next = (ScreenID)((current_screen + 1) % NUM_SCREENS);
    load_screen(next);
}

ScreenID get_current_screen(void)
{
    return current_screen;
}

void updateUI(void)
{
    updateBatteryInfoUI();
    mbmsStatusScreenUpdate();
    powerSelectionStatusScreenUpdate();
    tripScreenUpdate();
    contactorScreenUpdate();
}

void updateBatteryInfoUI(void)
{
    char buf[32];

    // Update the UI elements with the latest data
    snprintf(buf, sizeof(buf), "%.1f A", screenData.batteryInfo.packCurrent);
    lv_label_set_text(ui_PackCurrentVal, buf);

    snprintf(buf, sizeof(buf), "%d V", screenData.batteryInfo.packVoltage);
    lv_label_set_text(ui_PackVoltageVal, buf);

    snprintf(buf, sizeof(buf), "%d %%", screenData.batteryInfo.packSOC);
    lv_label_set_text(ui_StateOfChargeVal, buf);

    snprintf(buf, sizeof(buf), "%d %%", screenData.batteryInfo.packDOD);
    lv_label_set_text(ui_DepthOfDischargeVal, buf);

    snprintf(buf, sizeof(buf), "%.1f Ah", screenData.batteryInfo.packAmphours / 100.0f);
    lv_label_set_text(ui_AmpHoursVal, buf);

    snprintf(buf, sizeof(buf), "%d °C", screenData.batteryInfo.lowTemp);
    lv_label_set_text(ui_LowTempVal, buf);

    snprintf(buf, sizeof(buf), "%d °C", screenData.batteryInfo.avgTemp);
    lv_label_set_text(ui_AvgTempVal, buf);

    snprintf(buf, sizeof(buf), "%d °C", screenData.batteryInfo.highTemp);
    lv_label_set_text(ui_HighTempVal, buf);

    snprintf(buf, sizeof(buf), "%.1f mV", screenData.batteryInfo.lowCellVoltage);
    lv_label_set_text(ui_LowCellVoltageVal, buf);

    snprintf(buf, sizeof(buf), "%.1f mV", screenData.batteryInfo.highCellVoltage);
    lv_label_set_text(ui_HighCellVoltageVal, buf);

    snprintf(buf, sizeof(buf), "%d V", screenData.batteryInfo.maxCellVoltage);
    lv_label_set_text(ui_MaxCellVoltageVal, buf);
}

void setCheckboxState(lv_obj_t *checkbox, bool checked)
{
    if (checked)
    {
        lv_obj_add_state(checkbox, LV_STATE_CHECKED); // Check the box
    }
    else
    {
        lv_obj_clear_state(checkbox, LV_STATE_CHECKED); // Uncheck the box
    }
}

const char* getStartupStateString(StartupState state) {
    switch (state) {
        case StartupState::nMPS_ENABLED:     return "nMPS EN";
        case StartupState::nMPS_DISABLED:    return "nMPS DIS";
        case StartupState::ESD_DISABLED:     return "ESD DIS";
        case StartupState::CHECKS_PASSED:    return "Checks OK";
        case StartupState::COMMON_CLOSED:    return "Common On";
        case StartupState::LV_CLOSED:        return "LV On";
        case StartupState::EN1_ON:           return "EN1 On";
        case StartupState::MOTORS_PERMS:     return "Motor OK";
        case StartupState::ARRAY_PERMS:      return "Array OK";
        case StartupState::COMPLETED:        return "Startup OK";
        default:                             return "Unknown";
    }
}

const char* getCarStateString(CarState state) {
    switch (state) {
        case CarState::BOOT:               return "Boot";
        case CarState::STARTUP:            return "Startup";
        case CarState::FULLY_OPERATIONAL:  return "Fully Op.";
        case CarState::CHARGING:           return "Charging";
        case CarState::BPS_FAULT:          return "BPS Fault";
        case CarState::MPS_DISCONNECTED:   return "MPS Discon.";
        case CarState::SOFT_TRIP:          return "Soft Trip";
        default:                           return "Unknown";
    }
}


void mbmsStatusScreenUpdate(void)
{
    char buf[32];

    snprintf(buf, sizeof(buf), "%d V", screenData.mbmsStatus.auxBatteryVoltage);
    lv_label_set_text(ui_AuxBatteryVoltageVal, buf);

    setCheckboxState(ui_StrobeBMSLightCheck, screenData.mbmsStatus.strobeBMSLight);

    setCheckboxState(ui_AllowChargeCheck, screenData.mbmsStatus.nChargeEnable);
    setCheckboxState(ui_AllowDischargeCheck, screenData.mbmsStatus.nDischargeEnable);
    setCheckboxState(ui_ChargeSafetyCheck, screenData.mbmsStatus.nChargeSafety);

    setCheckboxState(ui_OrionCanReceivedCheck, screenData.mbmsStatus.orionCANRx);
    setCheckboxState(ui_DischargeShouldTripCheck, screenData.mbmsStatus.dischargeShouldTrip);
    setCheckboxState(ui_ChargeShouldTripCheck, screenData.mbmsStatus.chargeShouldTrip);

    lv_label_set_text(ui_StartupStateVal, getStartupStateString(screenData.mbmsStatus.startupState));
    lv_label_set_text(ui_CarStateVal, getCarStateString(screenData.mbmsStatus.systemState));

}

const char* boolToYesNo(bool value) {
    return value ? "YES" : "NO";
}

void powerSelectionStatusScreenUpdate(void){
    setCheckboxState(ui_ExternalShutdownCheck, screenData.powerStatus.externalShutdown);
    setCheckboxState(ui_DCDCFaultCheck, screenData.powerStatus.nDCDCFault);
    setCheckboxState(ui_ThreeAmpOverCurrentCheck, screenData.powerStatus.n3A_OC);
    setCheckboxState(ui_DCDCOnCheck, screenData.powerStatus.nDCDC_On);
    setCheckboxState(ui_ChargeFaultCheck, screenData.powerStatus.nCHGFault);
    setCheckboxState(ui_ChargeOnCheck, screenData.powerStatus.nCHG_On);
    setCheckboxState(ui_ChargeLVEnableCheck, screenData.powerStatus.nCHG_LV_En);
    setCheckboxState(ui_AuxBattDisableCheck, screenData.powerStatus.abattDisable);

    lv_label_set_text(ui_MainPowerSwitchVal, boolToYesNo(screenData.powerStatus.nMainPowerSwitch));
    lv_label_set_text(ui_EN1Val, boolToYesNo(screenData.powerStatus.en1));
    lv_label_set_text(ui_KeyVal, boolToYesNo(screenData.powerStatus.key));
}

void tripScreenUpdate(void){
    setCheckboxState(ui_HighCellVoltageTrip, screenData.tripScreen.highCellVoltageTrip);
    setCheckboxState(ui_LowCellVoltageTrip, screenData.tripScreen.lowCellVoltageTrip);
    setCheckboxState(ui_CommonHighCurrTrip, screenData.tripScreen.commonHighCurrentTrip);

    setCheckboxState(ui_MotorHighCurrTrip, screenData.tripScreen.motorHighCurrentTrip);
    setCheckboxState(ui_ArrayHighCurrTrip, screenData.tripScreen.arrayHighCurrentTrip);
    setCheckboxState(ui_LVHighCurrTrip, screenData.tripScreen.lvHighCurrentTrip);
    setCheckboxState(ui_ChargeHighCurrTrip, screenData.tripScreen.chargeHighCurrentTrip);
    setCheckboxState(ui_ProtectionTrip, screenData.tripScreen.protectionTrip);

    setCheckboxState(ui_OrionMsgTimeoutTrip, screenData.tripScreen.orionMsgTimeoutTrip);
    setCheckboxState(ui_ContactorDisconnectedUnexpectedlyTrip, screenData.tripScreen.contactorDiscUnexpected);
    setCheckboxState(ui_ContactorConnectedUnexpectedlyTrip, screenData.tripScreen.contactorConnUnexpected);


    setCheckboxState(ui_CommonHeartBeatTrip, screenData.tripScreen.commonHeartbeatDead);
    setCheckboxState(ui_MotorHeartbeatTrip, screenData.tripScreen.motorHeartbeatDead);
    setCheckboxState(ui_ArrayHeartbeatTrip, screenData.tripScreen.arrayHeartbeatDead);
    setCheckboxState(ui_LVHeartBeatTrip, screenData.tripScreen.lvHeartbeatDead);
    setCheckboxState(ui_ChargeHeartbeatTrip, screenData.tripScreen.chargeHeartbeatDead);

    setCheckboxState(ui_MPSDisabledTrip, screenData.tripScreen.mpsDisabledTrip);
    setCheckboxState(ui_ESDEnabledTrip, screenData.tripScreen.esdEnabledTrip);
    setCheckboxState(ui_HighTempTrip, screenData.tripScreen.highTempTrip);
    setCheckboxState(ui_LowTempTrip, screenData.tripScreen.lowTempTrip);
}

inline const char* toString(PrechargeState state) {
  switch (state) {
    case PrechargeState::OPEN:    return "OPEN";
    case PrechargeState::CLOSED:  return "CLOSED";
    case PrechargeState::CLOSING: return "CLOSING";
    case PrechargeState::ERROR:   return "ERROR";
    default:                      return "UNKNOWN";
  }
}

inline const char* toString(ContactorState state) {
  switch (state) {
    case ContactorState::OPEN:    return "OPEN";
    case ContactorState::CLOSED:  return "CLOSED";
    case ContactorState::CLOSING: return "CLOSING";
    case ContactorState::ERROR:   return "ERROR";
    default:                      return "UNKNOWN";
  }
}

void contactorScreenUpdate(void){
    setCheckboxState(ui_CommonCheck, screenData.contactorScreen.commonBoard.heartbeat);
    setCheckboxState(ui_MotorCheck, screenData.contactorScreen.motorBoard.heartbeat);
    setCheckboxState(ui_ArrayCheck, screenData.contactorScreen.arrayBoard.heartbeat);
    setCheckboxState(ui_LowVCheck, screenData.contactorScreen.lvBoard.heartbeat);
    setCheckboxState(ui_ChargeCheck, screenData.contactorScreen.chargeBoard.heartbeat);

    lv_label_set_text(ui_CommonContactorLabel, toString(screenData.contactorScreen.commonBoard.contactorState));
    lv_label_set_text(ui_MotorContactorLabel, toString(screenData.contactorScreen.motorBoard.contactorState));
    lv_label_set_text(ui_ArrayContactorLabel, toString(screenData.contactorScreen.arrayBoard.contactorState));
    lv_label_set_text(ui_LowVContactorLabel, toString(screenData.contactorScreen.lvBoard.contactorState));
    lv_label_set_text(ui_ChargeContactorLabel, toString(screenData.contactorScreen.chargeBoard.contactorState));

    char buf[32];

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.commonBoard.lineCurrent);
    lv_label_set_text(ui_CommonLA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.commonBoard.chargeCurrent);
    lv_label_set_text(ui_CommonCA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.motorBoard.lineCurrent);
    lv_label_set_text(ui_MotorLA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.motorBoard.chargeCurrent);
    lv_label_set_text(ui_MotorCA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.arrayBoard.lineCurrent);
    lv_label_set_text(ui_ArrayLA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.arrayBoard.chargeCurrent);
    lv_label_set_text(ui_ArrayCA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.lvBoard.lineCurrent);
    lv_label_set_text(ui_LowVLA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.lvBoard.chargeCurrent);
    lv_label_set_text(ui_LowVCA, buf);
    
    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.chargeBoard.lineCurrent);
    lv_label_set_text(ui_ChargeLA, buf);

    snprintf(buf, sizeof(buf), "%.1f A", screenData.contactorScreen.chargeBoard.chargeCurrent);
    lv_label_set_text(ui_ChargeCA, buf);

}