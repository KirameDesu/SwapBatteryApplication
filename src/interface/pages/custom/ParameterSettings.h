#ifndef PARAMETER_SETTINGS_H
#define PARAMETER_SETTINGS_H

#include "BaseSetting.h"

#include <QList>
#include <QPair>

#include "typedef.h"


struct SettingsStruct
{
	QString groupTitle;
	qint16 regStart;
	QList<Setting> setList;
};

using SETTINGS_CELL = SettingsStruct;
using SETTINGS_CLASS = QList<SettingsStruct>;


class Base {
public:
	// 计算起始地址
	static qint16 calculateStartAddress(const QList<SETTINGS_CELL>& settingsList) {
		qint16 minStartAddress = std::numeric_limits<qint16>::max();  // 初始化为最大值
		for (const SETTINGS_CELL& cell : settingsList) {
			if (cell.regStart < minStartAddress) {
				minStartAddress = cell.regStart;
			}
		}
		return minStartAddress;
	}

	// 计算寄存器数量
	static int calculateTotalRegisters(const QList<SETTINGS_CELL>& settingsList) {
		int total = 0;
		for (const SETTINGS_CELL& cell : settingsList) {
			total += cell.setList.size();  // 累加 setList 的个数
		}
		return total;
	}
};


class BatteryOverview : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	};

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL AFEItems;	
	static const SETTINGS_CELL SOCItems;
};

// 电压设置
class VoltSettings : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	};

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CELL_OV;
	static const SETTINGS_CELL CELL_UV;
	static const SETTINGS_CELL PACK_OV;
	static const SETTINGS_CELL PACK_UV;
	static const SETTINGS_CELL DISABLE_VOLT;
};

// 电流设置
class CurrentSettings : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	}

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CHG_OC;
	static const SETTINGS_CELL DSG_OC;
	static const SETTINGS_CELL DSG_OC2;
};

// 温度设置
class TemperatureSettings : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	}

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CHG_OT_UT;
	static const SETTINGS_CELL DSG_OT_UT;
	static const SETTINGS_CELL ENV_OT_UT;
	static const SETTINGS_CELL MOS_OT_UT;
	static const SETTINGS_CELL HEAT;
};

// 低电量设置
class LowSOCSettings : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	}

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL LOW_SOC;
};

// 低电量设置
class BatterySettings : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	}

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL SLEEP;
	static const SETTINGS_CELL CELL;
};

#endif // !PROTECT_SETTINGS_H