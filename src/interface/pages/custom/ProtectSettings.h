#ifndef PROTECT_SETTINGS_H
#define PROTECT_SETTINGS_H

#include "BaseSetting.h"

#include <QVector>

#include "typedef.h"

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

QVector<Setting> CELL_OV = {
	{"警告电压", "mV", 2000, 5000},
	{"保护1电压", "mV", 0, 19900},
	{"保护1延时", "ms", 2000, 5000},
	{"保护1恢复电压", "mV", 0, 19900},
	{"保护2电压", "mV", 2000, 5000},
};

#endif // !PROTECT_SETTINGS_H