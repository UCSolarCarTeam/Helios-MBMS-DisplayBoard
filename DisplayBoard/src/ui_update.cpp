#include "ui_update.h"

lv_obj_t ** screen_list[NUM_SCREENS] = {
    &ui_Contactor_Screen,
    &ui_TripScreen,
    &ui_BatteryInfoScreen,
    &ui_MBMSStatusScreen,
    &ui_PowerSelectionStatusScreen
};

void load_screen(ScreenID screen_id) {
    if (screen_id >= NUM_SCREENS) return;

    current_screen = screen_id;
    if (*screen_list[screen_id]) {
        lv_scr_load(*screen_list[screen_id]);
    }
}

void load_next_screen(void) {
    ScreenID next = (ScreenID)((current_screen + 1) % NUM_SCREENS);
    load_screen(next);
}


ScreenID get_current_screen(void) {
    return current_screen;
}


void updateUI(void){
    updateBatteryInfoUI();
}

void updateBatteryInfoUI(void){
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
