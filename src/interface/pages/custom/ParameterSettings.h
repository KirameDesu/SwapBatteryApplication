#ifndef PARAMETER_SETTINGS_H
#define PARAMETER_SETTINGS_H

#include "BaseSetting.h"

#include <QList>
#include <QPair>

#include "typedef.h"


using SETTINGS_TYPE = QList<QPair<QString, QList<Setting>>>;


struct ProtectSettingRegisterList
{
	const static uint16_t REGSTER_START = 0x1000;
	struct VoltSet {
		struct COV {
			uint16_t alarmVolt;
			uint16_t protect1Volt;
			uint16_t protect1Delay;
			uint16_t protect1RecoveryVolt;
			uint16_t protect2Volt;
		};
		struct POV {
			uint16_t alarmVolt;
			uint16_t protect1Volt;
			uint16_t protect1Delay;
			uint16_t protect1RecoveryVolt;
			uint16_t protect2Volt;
		};
	};
	const static uint16_t REGSTER_END = REGSTER_START + sizeof(VoltSet) / sizeof(uint16_t) - 1;
};


// 电压设置
class VoltSettings
{
public:
	static const SETTINGS_TYPE getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_TYPE settingsList;

	static const QPair<QString, QList<Setting>> CELL_OV;
	static const QPair<QString, QList<Setting>> CELL_UV;
	static const QPair<QString, QList<Setting>> PACK_OV;
	static const QPair<QString, QList<Setting>> PACK_UV;
	static const QPair<QString, QList<Setting>> DISABLE_VOLT;
};

// 电流设置
class CurrentSettings
{
public:
	static const SETTINGS_TYPE getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_TYPE settingsList;
	static const QPair<QString, QList<Setting>> CHG_OC;
	static const QPair<QString, QList<Setting>> DSG_OC;
	static const QPair<QString, QList<Setting>> DSG_OC2;
};

// 温度设置
class TemperatureSettings
{
public:
	static const SETTINGS_TYPE getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_TYPE settingsList;
	static const QPair<QString, QList<Setting>> CHG_OT_UT;
	static const QPair<QString, QList<Setting>> DSG_OT_UT;
	static const QPair<QString, QList<Setting>> ENV_OT_UT;
	static const QPair<QString, QList<Setting>> MOS_OT_UT;
	static const QPair<QString, QList<Setting>> HEAT;
};

// 低电量设置
class LowSOCSettings
{
public:
	static const SETTINGS_TYPE getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_TYPE settingsList;
	static const QPair<QString, QList<Setting>> LOW_SOC;
};

// 低电量设置
class BatterySettings
{
public:
	static const SETTINGS_TYPE getAllSettings() {
		return settingsList;
	}

private:
	static const SETTINGS_TYPE settingsList;
	static const QPair<QString, QList<Setting>> SLEEP;
	static const QPair<QString, QList<Setting>> CELL;
};

#endif // !PROTECT_SETTINGS_H