﻿// ParameterSettings.cpp 寄存器定义
// 同一组的寄存器起始地址必须要连续
#include "ParameterSettings.h"

#define _SEMA RegisterDataType::Semaphore
#define _SW RegisterDataType::Switch



//======================================================================================================
//                                          电池概况设置
//======================================================================================================
const SETTINGS_CELL BatteryOverview::AFEItems =
{
	"AFE数据", 	0X0800,
	{
		{_SW, "系统功能状态", "", 0, 2 ^ 16 - 1},
		{_SW, "保护状态", "", 0, 2 ^ 16 - 1},
		{_SW, "错误状态", "", 0, 2 ^ 16 - 1},
		{_SW, "保留", "", 0, 2 ^ 16 - 1},

		{_SEMA, "电池电压", "V", 20, 5000},// 100mV
		{_SEMA, "总电压", "V", 20, 5000},// 100mV
		{_SEMA, "平均电流1", "mV", -3000, 3000},// 100mA
		{_SEMA, "平均电流2", "mV", -3000, 3000},// 100mA
		{_SEMA, "实时电流1", "mV", -3000, 3000},// 100mA
		{_SEMA, "实时电流2", "mV", -3000, 3000},// 100mA

		{_SEMA, "最大电芯电压", "mV", -3000, 3000},
		{_SEMA, "最小电芯电压", "mV", -3000, 3000},
		{_SEMA, "平均电芯电压", "mV", -3000, 3000},

		{_SEMA, "最大电芯温度", "℃", -3000, 3000},
		{_SEMA, "最小电芯温度", "℃", -3000, 3000},
		{_SEMA, "平均电芯温度", "℃", -3000, 3000},

		{_SEMA, "环境温度", "℃", -80, 160},	//0.1℃
		{_SEMA, "MOS温度", "℃", -80, 160}, 

		{_SW, "均衡标志1", "", 0, 2 ^ 16 - 1},
		{_SW, "均衡标志2", "", 0, 2 ^ 16 - 1},

		{_SEMA, "电芯数量", "", 1, 2 ^ 16 - 1},
		{_SEMA, "电芯电压1", "mV", 1000, 5000},
		{_SEMA, "电芯电压2", "mV", 1000, 5000},
		{_SEMA, "电芯电压3", "mV", 1000, 5000},
		{_SEMA, "电芯电压4", "mV", 1000, 5000},
		{_SEMA, "电芯电压5", "mV", 1000, 5000},
		{_SEMA, "电芯电压6", "mV", 1000, 5000},
		{_SEMA, "电芯电压7", "mV", 1000, 5000},
		{_SEMA, "电芯电压8", "mV", 1000, 5000},
		{_SEMA, "电芯电压9", "mV", 1000, 5000},
		{_SEMA, "电芯电压10", "mV", 1000, 5000},
		{_SEMA, "电芯电压11", "mV", 1000, 5000},
		{_SEMA, "电芯电压12", "mV", 1000, 5000},
		{_SEMA, "电芯电压13", "mV", 1000, 5000},
		{_SEMA, "电芯电压14", "mV", 1000, 5000},
		{_SEMA, "电芯电压15", "mV", 1000, 5000},
		{_SEMA, "电芯电压16", "mV", 1000, 5000},
		{_SEMA, "电芯电压17", "mV", 1000, 5000},
		{_SEMA, "电芯电压18", "mV", 1000, 5000},
		{_SEMA, "电芯电压19", "mV", 1000, 5000},
		{_SEMA, "电芯电压20", "mV", 1000, 5000},
		{_SEMA, "电芯电压21", "mV", 1000, 5000},
		{_SEMA, "电芯电压22", "mV", 1000, 5000},
		{_SEMA, "电芯电压23", "mV", 1000, 5000},
		{_SEMA, "电芯电压24", "mV", 1000, 5000},

		{_SEMA, "温度采集点数量", "", 0, 30},
		{_SEMA, "电芯温度1", "℃", -80, 160},
		{_SEMA, "电芯温度2", "℃", -80, 160},
		{_SEMA, "电芯温度3", "℃", -80, 160},
		{_SEMA, "电芯温度4", "℃", -80, 160},
	}
};

const SETTINGS_CELL BatteryOverview::SOCItems =
{
	"SOC数据", 	0X0900,
	{
		{_SEMA, "设计容量", "AH", 10, 6000},	// 100mAH
		{_SEMA, "满充容量", "AH", 10, 6000},
		{_SEMA, "剩余容量", "AH", 10, 6000},
		{_SEMA, "放电循环次数", "/", 0, 15000},
		{_SEMA, "充电循环次数", "/", 0, 15000},
		{_SEMA, "SOC", "%", 0, 100},
		{_SEMA, "SOH", "%", 0, 100},
		
		{_SEMA, "放电总容量1", "AH", 0, 2 ^ 16 - 1},
		{_SEMA, "放电总容量2", "AH", 0, 2 ^ 16 - 1},
		{_SEMA, "充电总容量1", "AH", 0, 2 ^ 16 - 1},
		{_SEMA, "充电总容量2", "AH", 0, 2 ^ 16 - 1},
		{_SEMA, "充电总时间1", "%", 0, 2 ^ 16 - 1},
		{_SEMA, "充电总时间2", "%", 0, 2 ^ 16 - 1},
		{_SEMA, "放电总时间1", "%", 0, 2 ^ 16 - 1},
		{_SEMA, "放电总时间2", "%", 0, 2 ^ 16 - 1},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS BatteryOverview::settingsList = {
	BatteryOverview::AFEItems,
	//BatteryOverview::SOCItems,
};
qint16 BatteryOverview::startAddress = calculateStartAddress(BatteryOverview::settingsList);
int BatteryOverview::totalRegisters = calculateTotalRegisters(BatteryOverview::settingsList);
//======================================================================================================
//                                          电压设置
//======================================================================================================
const SETTINGS_CELL VoltSettings::CELL_OV =
{
	"单体过压设置", 	0X12AA,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "警告电压延时", "ms", 2000, 5000},
		{_SEMA, "警告失效电压", "mV", 2000, 5000},
		{_SEMA, "警告失效电压延时", "ms", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
		{_SEMA, "保护1恢复电压延时", "ms", 0, 19900},
		{_SEMA, "保护2电压", "mV", 2000, 5000},
		{_SEMA, "保护2延时", "ms", 2000, 5000},
		{_SEMA, "保护2恢复电压", "mV", 2000, 5000},
		{_SEMA, "保护2恢复延时", "ms", 2000, 5000},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
		{_SEMA, "解除保护电流延时", "ms", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::CELL_UV =
{
	"单体欠压设置",	0X13BB,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "警告电压延时", "ms", 2000, 5000},
		{_SEMA, "警告失效电压", "mV", 2000, 5000},
		{_SEMA, "警告失效电压延时", "ms", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
		{_SEMA, "保护1恢复电压延时", "ms", 0, 19900},
		{_SEMA, "保护2电压", "mV", 2000, 5000},
		{_SEMA, "保护2延时", "ms", 2000, 5000},
		{_SEMA, "保护2恢复电压", "mV", 2000, 5000},
		{_SEMA, "保护2恢复延时", "ms", 2000, 5000},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
		{_SEMA, "解除保护电流延时", "ms", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::PACK_OV =
{
	"总体过压设置",	0X14CC,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "警告电压延时", "ms", 2000, 5000},
		{_SEMA, "警告失效电压", "mV", 2000, 5000},
		{_SEMA, "警告失效电压延时", "ms", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复SOC", "%", 0, 100},
		{_SEMA, "保护1恢复SOC延时", "%", 0, 100},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::PACK_UV =
{
	"总体欠压设置", 	0X15DD,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "警告电压延时", "ms", 2000, 5000},
		{_SEMA, "警告失效电压", "mV", 2000, 5000},
		{_SEMA, "警告失效电压延时", "ms", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复SOC", "%", 0, 100},
		{_SEMA, "保护1恢复SOC延时", "%", 0, 100},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS VoltSettings::settingsList = {
	VoltSettings::CELL_OV,
	VoltSettings::CELL_UV,
	VoltSettings::PACK_OV,
	VoltSettings::PACK_UV
};
qint16 VoltSettings::startAddress = calculateStartAddress(VoltSettings::settingsList);
int VoltSettings::totalRegisters = calculateTotalRegisters(VoltSettings::settingsList);


//======================================================================================================
//                                          电流设置
//======================================================================================================
const SETTINGS_CELL CurrentSettings::CHG_OC =
{
	"充电过流设置",	0X1000,
	{
		{_SEMA, "警告电流", "mA", 2000, 5000},
		{_SEMA, "保护1电流", "mA", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护自动解除", "ms", 0, 19900},
		{_SEMA, "锁住次数", "/", 1, 30},
		{_SEMA, "解除保护电流", "mA", 1, 30},
	}
};

const SETTINGS_CELL CurrentSettings::DSG_OC =
{
	"放电过流设置",	0X1100,
	{
		{_SEMA, "警告电流", "mA", 2000, 5000},
		{_SEMA, "保护1.1电流", "mA", 0, 19900},
		{_SEMA, "保护1.1延时", "ms", 2000, 5000},
		{_SEMA, "保护1.2电流", "mA", 0, 19900},
		{_SEMA, "保护1.2延时", "ms", 2000, 5000},
		{_SEMA, "保护自动解除", "ms", 0, 19900},
		{_SEMA, "锁住次数", "/", 1, 30},
		{_SEMA, "解除保护电流", "mA", 1, 30},
	}
};

const SETTINGS_CELL CurrentSettings::DSG_OC2 =
{
	"放电过流+短路设置",	0X1200,
	{
		{_SEMA, "保护2电流", "mA", 0, 19900},
		{_SEMA, "保护2延时", "ms", 2000, 5000},
		{_SEMA, "短路电流", "mA", 0, 19900},
		{_SEMA, "短路延时", "us", 2000, 5000},
		{_SEMA, "保护自动解除", "ms", 0, 19900},
		{_SEMA, "锁住次数", "/", 1, 30},
		{_SEMA, "充电解除", "mA", 1, 30},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS CurrentSettings::settingsList = {
	CurrentSettings::CHG_OC,
	CurrentSettings::DSG_OC,
	CurrentSettings::DSG_OC2,
};
qint16 CurrentSettings::startAddress = calculateStartAddress(CurrentSettings::settingsList);
int CurrentSettings::totalRegisters = calculateTotalRegisters(CurrentSettings::settingsList);


//======================================================================================================
//                                          温度设置
//======================================================================================================
const SETTINGS_CELL TemperatureSettings::CHG_OT_UT =
{
	"充电高低温",		0X2100,
	{
		{_SEMA, "高温警告", "℃", 2000, 5000},
		{_SEMA, "高温保护1温度", "℃", 0, 19900},
		{_SEMA, "高温保护1恢复", "℃", 2000, 5000},
		{_SEMA, "低温警告", "℃", 0, 19900},
		{_SEMA, "低温保护1温度", "℃", 2000, 5000},
		{_SEMA, "低温保护1温度", "℃", 2000, 5000},
	}
};

const SETTINGS_CELL TemperatureSettings::DSG_OT_UT =
{
	"放电高低温", 	0X2200,
	{
		{_SEMA, "高温警告", "℃", 2000, 5000},
		{_SEMA, "高温保护1温度", "℃", 0, 19900},
		{_SEMA, "高温保护1恢复", "℃", 2000, 5000},
		{_SEMA, "低温警告", "℃", 0, 19900},
		{_SEMA, "低温保护1温度", "℃", 2000, 5000},
		{_SEMA, "低温保护1温度", "℃", 2000, 5000},
	}
};

const SETTINGS_CELL TemperatureSettings::ENV_OT_UT =
{
	"环境高低温",		0X2300,
	{
		{_SEMA, "高温警告", "℃", 2000, 5000},
		{_SEMA, "高温保护1温度", "℃", 0, 19900},
		{_SEMA, "高温保护1恢复", "℃", 2000, 5000},
		{_SEMA, "低温警告", "℃", 0, 19900},
		{_SEMA, "低温保护1温度", "℃", 2000, 5000},
		{_SEMA, "低温保护1温度", "℃", 2000, 5000},
	}
};

const SETTINGS_CELL TemperatureSettings::MOS_OT_UT =
{
	"MOS高低温",		0X2400,
	{
		{_SEMA, "充电低温警告", "℃", 0, 19900},
		{_SEMA, "充电低温保护", "℃", 2000, 5000},
		{_SEMA, "充电低温恢复", "℃", 2000, 5000},
		{_SEMA, "放电高温警告", "℃", 2000, 5000},
		{_SEMA, "放电高温保护", "℃", 0, 19900},
		{_SEMA, "放电高温恢复", "℃", 2000, 5000},
	}
};

const SETTINGS_CELL TemperatureSettings::HEAT =
{
	"加热膜参数", 	0X2500,
	{
		{_SEMA, "启动温度", "℃", 2000, 5000},
		{_SEMA, "解除温度", "℃", 0, 19900},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS TemperatureSettings::settingsList = {
	TemperatureSettings::CHG_OT_UT,
	TemperatureSettings::DSG_OT_UT,
	TemperatureSettings::ENV_OT_UT,
	TemperatureSettings::MOS_OT_UT,
	TemperatureSettings::HEAT,
};
qint16 TemperatureSettings::startAddress = calculateStartAddress(TemperatureSettings::settingsList);
int TemperatureSettings::totalRegisters = calculateTotalRegisters(TemperatureSettings::settingsList);


//======================================================================================================
//                                          低电量设置
//======================================================================================================
const SETTINGS_CELL LowSOCSettings::LOW_SOC =
{
	"SOC低电量",		0X3000,
	{
		{_SEMA, "警告", "%", 2000, 5000},
		{_SEMA, "放电截止容量", "%", 0, 19900},
		{_SEMA, "放电截止解除容量", "%", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS LowSOCSettings::settingsList = {
	LowSOCSettings::LOW_SOC,
};
qint16 LowSOCSettings::startAddress = calculateStartAddress(LowSOCSettings::settingsList);
int LowSOCSettings::totalRegisters = calculateTotalRegisters(LowSOCSettings::settingsList);

//======================================================================================================
//                                          电池设置
//======================================================================================================
const SETTINGS_CELL BatterySettings::SLEEP =
{
	"休眠设置",		0X4000,
	{
		{_SEMA, "系统自损耗", "mW", 2000, 5000},
		{_SEMA, "单体休眠电压", "mV", 0, 19900},
		{_SEMA, "静置休眠延时", "ms", 2000, 5000},
		{_SEMA, "定时巡检时间", "ms", 0, 19900},
		{_SEMA, "单体SHIP电压", "mV", 2000, 5000},
	}
};

const SETTINGS_CELL BatterySettings::CELL =
{
	"Pack参数设置",	0X4100,
	{
		{_SEMA, "电芯串数", "/", 2000, 5000},
		{_SEMA, "电芯类型", "/", 0, 19900},
		{_SEMA, "设计容量", "mAH", 2000, 5000},
		{_SEMA, "满充容量", "mAH", 0, 19900},
		{_SEMA, "剩余容量", "mAH", 2000, 5000},
		{_SEMA, "充电循环次数", "/", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS BatterySettings::settingsList = {
	BatterySettings::SLEEP,
	BatterySettings::CELL,
};
qint16 BatterySettings::startAddress = calculateStartAddress(BatterySettings::settingsList);
int BatterySettings::totalRegisters = calculateTotalRegisters(BatterySettings::settingsList);
