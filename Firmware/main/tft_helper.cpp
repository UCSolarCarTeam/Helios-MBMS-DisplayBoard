#include "tft_helper.h"

void clearAllCheckMarks(void)
{
    lv_obj_clear_state(ui_HighCellVoltageTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LowCellVoltageTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_CommonHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MotorHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ArrayHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LVHighCurrTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ProtectionTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_OrionMsgTimeoutTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_HighBatteryTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ESDEnabledTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_HighTempTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MPSDisabledTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LowTempTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_CommonHeartBeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MotorHeartbeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ArrayHeartbeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeHeartbeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ContactorDisconnectedUnexpectedlyTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ContactorConnectedUnexpectedlyTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LVHeartBeatTrip, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeHighCurrTrip, LV_STATE_CHECKED);

    lv_obj_clear_state(ui_ArrayCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_LowVCheck, LV_STATE_CHECKED); 
    lv_obj_clear_state(ui_ChargeCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_PreChargerCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MotorCheck, LV_STATE_CHECKED);

    lv_obj_clear_state(ui_OrionCanReceivedCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_DischargeShouldTripCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeShouldTripCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_StrobeBMSLightCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_AllowChargeCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_HighVoltageEnableStateCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_AllowDischargeCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeSafetyCheck, LV_STATE_CHECKED);

    lv_obj_clear_state(ui_ExternalShutdownCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_DCDCFaultCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeFaultCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_DCDCOnCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeOnCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ThreeAmpOverCurrentCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_AuxBattDisableCheck, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_ChargeLVEnableCheck, LV_STATE_CHECKED);
}


void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{

  uint16_t c;

  tftDisplay.startWrite();
  tftDisplay.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1));

  for (int y = area->y1; y <= area->y2; y++)
  {
    for (int x = area->x1; x <= area->x2; x++)
    {
      c = color_p->full; // Convert color
      tftDisplay.pushColor(c);
      color_p++;
    }
  }
  tftDisplay.endWrite();

  lv_disp_flush_ready(disp); // Tell LVGL that flushing is done
}


void tft_init(void){
  lv_init(); // Initialize LVGL


  tftDisplay.begin();

  ui_init();
}