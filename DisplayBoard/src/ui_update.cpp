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

    // TODO: Double check the not of these boolean with Dylan/ Millaine
    setCheckboxState(ui_AllowChargeCheck, !screenData.mbmsStatus.nChargeEnable);
    setCheckboxState(ui_AllowDischargeCheck, !screenData.mbmsStatus.nDischargeEnable);
    setCheckboxState(ui_ChargeSafetyCheck, !screenData.mbmsStatus.nChargeSafety);

    setCheckboxState(ui_OrionCanReceivedCheck, screenData.mbmsStatus.orionCANRx);
    setCheckboxState(ui_DischargeShouldTripCheck, screenData.mbmsStatus.dischargeShouldTrip);
    setCheckboxState(ui_ChargeShouldTripCheck, screenData.mbmsStatus.chargeShouldTrip);

    lv_label_set_text(ui_StartupStateVal, getStartupStateString(screenData.mbmsStatus.startupState));
    lv_label_set_text(ui_CarStateVal, getCarStateString(screenData.mbmsStatus.systemState));

}