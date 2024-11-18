#ifndef PARAMETER_SETTINGS_H
#define PARAMETER_SETTINGS_H

#include "BaseSetting.h"

#include <QList>
#include <QPair>

#include "typedef.h"


struct SettingsStruct
{
	QString title;
	qint16 regStart;
	QList<Setting> setList;
};

//using SETTINGS_CELL = QPair<QString, QList<Setting>>
using SETTINGS_CELL = SettingsStruct;
using SETTINGS_CLASS = QList<SettingsStruct>;


//struct ProtectSettingRegisterList
//{
//	const static uint16_t REGSTER_START = 0x1000;
//	struct VoltSet {
//		struct COV {
//			uint16_t alarmVolt;
//			uint16_t protect1Volt;
//			uint16_t protect1Delay;
//			uint16_t protect1RecoveryVolt;
//			uint16_t protect2Volt;
//		};
//		struct POV {
//			uint16_t alarmVolt;
//			uint16_t protect1Volt;
//			uint16_t protect1Delay;
//			uint16_t protect1RecoveryVolt;
//			uint16_t protect2Volt;
//		};
//	};
//	const static uint16_t REGSTER_END = REGSTER_START + sizeof(VoltSet) / sizeof(uint16_t) - 1;
//};


// 电压设置
class VoltSettings
{
public:
	static const SETTINGS_CLASS getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_CLASS settingsList;

	static const SETTINGS_CELL CELL_OV;
	static const SETTINGS_CELL CELL_UV;
	static const SETTINGS_CELL PACK_OV;
	static const SETTINGS_CELL PACK_UV;
	static const SETTINGS_CELL DISABLE_VOLT;
};

// 电流设置
class CurrentSettings
{
public:
	static const SETTINGS_CLASS getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CHG_OC;
	static const SETTINGS_CELL DSG_OC;
	static const SETTINGS_CELL DSG_OC2;
};

// 温度设置
class TemperatureSettings
{
public:
	static const SETTINGS_CLASS getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CHG_OT_UT;
	static const SETTINGS_CELL DSG_OT_UT;
	static const SETTINGS_CELL ENV_OT_UT;
	static const SETTINGS_CELL MOS_OT_UT;
	static const SETTINGS_CELL HEAT;
};

// 低电量设置
class LowSOCSettings
{
public:
	static const SETTINGS_CLASS getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL LOW_SOC;
};

// 低电量设置
class BatterySettings
{
public:
	static const SETTINGS_CLASS getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL SLEEP;
	static const SETTINGS_CELL CELL;
};

#endif // !PROTECT_SETTINGS_H