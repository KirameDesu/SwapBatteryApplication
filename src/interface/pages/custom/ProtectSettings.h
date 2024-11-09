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
	{"�����ѹ", "mV", 2000, 5000},
	{"����1��ѹ", "mV", 0, 19900},
	{"����1��ʱ", "ms", 2000, 5000},
	{"����1�ָ���ѹ", "mV", 0, 19900},
	{"����2��ѹ", "mV", 2000, 5000},
};

#endif // !PROTECT_SETTINGS_H