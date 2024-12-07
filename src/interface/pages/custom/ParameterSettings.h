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

	// 判断地址是否在settingsGroupList的第index个的地址范围内
	static bool isAddrInCellAddr(const SETTINGS_CLASS& settingsGroupList, int index, int addr) {
		int groupSize = settingsGroupList[index].setList.size() * 2;
		return (addr >= settingsGroupList[index].regStart && addr < settingsGroupList[index].regStart + groupSize);
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

	static bool isAddrInCellAddr(int index, int addr) {
		if (index < settingsList.size() && index >= 0)
			return Base::isAddrInCellAddr(settingsList, index, addr);
		return false;
	}
	
	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.size());
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

	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.at(index).setList.size()) * 2;
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CELL_UV;
	static const SETTINGS_CELL CELL_OV;
	static const SETTINGS_CELL DiffVolt;
	static const SETTINGS_CELL MinFailVolt;
	static const SETTINGS_CELL MaxFailVolt;
	static const SETTINGS_CELL PACK_UV;
	static const SETTINGS_CELL PACK_OV;
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

	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.size());
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CHG_OC;
	static const SETTINGS_CELL DSG_OC;
	static const SETTINGS_CELL DSG_SC;
	static const SETTINGS_CELL CHG_MOS_FAIL;
	static const SETTINGS_CELL DSG_MOS_FAIL;
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

	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.size());
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL CHG_UT;
	static const SETTINGS_CELL CHG_OT;
	static const SETTINGS_CELL DSG_UT;
	static const SETTINGS_CELL DSG_OT;
	static const SETTINGS_CELL Temp_Diff;
	static const SETTINGS_CELL ENV_UT;
	static const SETTINGS_CELL ENV_OT;
	static const SETTINGS_CELL MOS_OT;
	//static const SETTINGS_CELL HEAT;
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

	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.size());
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

	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.size());
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL Func_Switch;
	static const SETTINGS_CELL Battery_Para;
	static const SETTINGS_CELL CHG_DSG_INFO;
	static const SETTINGS_CELL Other;
};

// BMS功能设置
class FunctionSettings : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	}

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}

	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.size());
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL Limit_Broad;
	static const SETTINGS_CELL Pre_CHG_DSG;
	static const SETTINGS_CELL Balance;
	static const SETTINGS_CELL Heat;
	static const SETTINGS_CELL Power_Loss;
};

// 逆变器设置
class InverterSettings : public Base
{
public:
	static const SETTINGS_CLASS& getAllSettings() {
		return settingsList;
	}

	static bool isAddrInRange(int addr) {
		return (addr >= startAddress && addr < startAddress + totalRegisters);
	}

	static qint16 getCellSize(int index) {
		return static_cast<qint16>(settingsList.size());
	}
private:
	static qint16 startAddress;
	static int totalRegisters;

	static const SETTINGS_CLASS settingsList;
	static const SETTINGS_CELL Inverter_Protocol;
	static const SETTINGS_CELL Force_CHG;
};

#endif // !PROTECT_SETTINGS_H