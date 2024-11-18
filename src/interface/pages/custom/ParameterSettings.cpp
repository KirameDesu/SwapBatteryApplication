#include "ParameterSettings.h"

#define _SEMA RegisterDataType::Semaphore
#define _Ana RegisterDataType::Analog

const SETTINGS_CELL VoltSettings::CELL_OV =
{
	"单体过压设置", 	0X1000,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
		{_SEMA, "保护2电压", "mV", 2000, 5000},
		{_SEMA, "保护2延时", "ms", 2000, 5000},
		{_SEMA, "保护2恢复电压", "mV", 2000, 5000},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::CELL_UV =
{
	"单体欠压设置",	0X1000,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA,"保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
		{_SEMA, "保护2电压", "mV", 2000, 5000},
		{_SEMA, "保护2延时", "ms", 2000, 5000},
		{_SEMA, "保护2恢复电压", "mV", 2000, 5000},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::PACK_OV =
{
	"总体过压设置",	0X1000,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::PACK_UV =
{
	"总体欠压设置", 	0X1000,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
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
	"放电过流设置",	0X1000,
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
	"放电过流+短路设置",	0X1000,
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

const SETTINGS_CELL TemperatureSettings::CHG_OT_UT =
{
	"充电高低温",		0X1000,
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
	"放电高低温", 	0X1000,
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
	"环境高低温",		0X1000,
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
	"MOS高低温",		0X1000,
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
	"加热膜参数", 	0X1000,
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

const SETTINGS_CELL LowSOCSettings::LOW_SOC =
{
	"SOC低电量",		0X1000,
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

const SETTINGS_CELL BatterySettings::SLEEP =
{
	"休眠设置",		0X1000,
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
	"Pack参数设置",	0X1000,
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