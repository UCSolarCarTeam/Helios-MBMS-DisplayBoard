// #include "spi_helper.h"

// void updateBatteryInfoUI(const uint8_t* data, size_t length) {
//   if (length != sizeof(BatteryInfo)) return;

//   BatteryInfo info;
//   memcpy(&info, data, sizeof(BatteryInfo));

//   // Format and update each label
//   char buf[16];

//   // Current (display with sign, in A)
//   snprintf(buf, sizeof(buf), "%.1f A", info.packCurrent / 100.0f);
//   lv_label_set_text(ui_PackCurrentVal, buf);

//   // Voltage (in V)
//   snprintf(buf, sizeof(buf), "%.1f V", info.packVoltage / 100.0f);
//   lv_label_set_text(ui_PackVoltageVal, buf);

//   // SOC (%)
//   snprintf(buf, sizeof(buf), "%d %%", info.packSOC);
//   lv_label_set_text(ui_StateOfChargeVal, buf);

//   // DOD (%)
//   snprintf(buf, sizeof(buf), "%d %%", info.packDOD);
//   lv_label_set_text(ui_DepthOfDischargeVal, buf);

//   // Amp-hours (in Ah)
//   snprintf(buf, sizeof(buf), "%.1f Ah", info.packAmphours / 100.0f);
//   lv_label_set_text(ui_AmpHoursVal, buf);

//   // Temperatures (in °C)
//   snprintf(buf, sizeof(buf), "%d °C", info.highTemp);
//   lv_label_set_text(ui_HighTempVal, buf);

//   snprintf(buf, sizeof(buf), "%d °C", info.lowTemp);
//   lv_label_set_text(ui_LowTempVal, buf);

//   snprintf(buf, sizeof(buf), "%d °C", info.avgTemp);
//   lv_label_set_text(ui_AvgTempVal, buf);

//   // Voltages (in V)
//   snprintf(buf, sizeof(buf), "%.2f V", info.maxCellVoltage / 1000.0f);
//   lv_label_set_text(ui_MaxCellVoltageVal, buf);

//   snprintf(buf, sizeof(buf), "%.2f V", info.minCellVoltage / 1000.0f);
//   lv_label_set_text(ui_MinCellVoltageVal, buf);

//   snprintf(buf, sizeof(buf), "%.1f V", info.maxPackVoltage / 100.0f);
//   lv_label_set_text(ui_MaxPackVoltageVal, buf);

//   snprintf(buf, sizeof(buf), "%.1f V", info.minPackVoltage / 100.0f);
//   lv_label_set_text(ui_MinPackVoltageVal, buf);
// }
