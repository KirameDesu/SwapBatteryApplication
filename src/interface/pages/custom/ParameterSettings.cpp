#include "ParameterSettings.h"


const QPair<QString, QList<Setting>> VoltSettings::CELL_OV =
{
	"单体过压设置", 
	{
		{"警告电压", "mV", 2000, 5000},
		{"保护1电压", "mV", 0, 19900},
		{"保护1延时", "ms", 2000, 5000},
		{"保护1恢复电压", "mV", 0, 19900},
		{"保护2电压", "mV", 2000, 5000},
		{"保护2延时", "ms", 2000, 5000},
		{"保护2恢复电压", "mV", 2000, 5000},
		{"解除保护电流", "mA", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> VoltSettings::CELL_UV =
{
	"单体欠压设置",
	{
		{"警告电压", "mV", 2000, 5000},
		{"保护1电压", "mV", 0, 19900},
		{"保护1延时", "ms", 2000, 5000},
		{"保护1恢复电压", "mV", 0, 19900},
		{"保护2电压", "mV", 2000, 5000},
		{"保护2延时", "ms", 2000, 5000},
		{"保护2恢复电压", "mV", 2000, 5000},
		{"解除保护电流", "mA", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> VoltSettings::PACK_OV =
{
	"总体过压设置",
	{
		{"警告电压", "mV", 2000, 5000},
		{"保护1电压", "mV", 0, 19900},
		{"保护1延时", "ms", 2000, 5000},
		{"保护1恢复电压", "mV", 0, 19900},
		{"解除保护电流", "mA", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> VoltSettings::PACK_UV =
{
	"总体欠压设置",
	{
		{"警告电压", "mV", 2000, 5000},
		{"保护1电压", "mV", 0, 19900},
		{"保护1延时", "ms", 2000, 5000},
		{"保护1恢复电压", "mV", 0, 19900},
		{"解除保护电流", "mA", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_TYPE VoltSettings::settingsList = {
	VoltSettings::CELL_OV,
	VoltSettings::CELL_UV,
	VoltSettings::PACK_OV,
	VoltSettings::PACK_UV
};


const QPair<QString, QList<Setting>> CurrentSettings::CHG_OC =
{
	"充电过流设置",
	{
		{"警告电流", "mA", 2000, 5000},
		{"保护1电流", "mA", 0, 19900},
		{"保护1延时", "ms", 2000, 5000},
		{"保护自动解除", "ms", 0, 19900},
		{"锁住次数", "/", 1, 30},
		{"解除保护电流", "mA", 1, 30},
	}
};

const QPair<QString, QList<Setting>> CurrentSettings::DSG_OC =
{
	"放电过流设置",
	{
		{"警告电流", "mA", 2000, 5000},
		{"保护1.1电流", "mA", 0, 19900},
		{"保护1.1延时", "ms", 2000, 5000},
		{"保护1.2电流", "mA", 0, 19900},
		{"保护1.2延时", "ms", 2000, 5000},
		{"保护自动解除", "ms", 0, 19900},
		{"锁住次数", "/", 1, 30},
		{"解除保护电流", "mA", 1, 30},
	}
};

const QPair<QString, QList<Setting>> CurrentSettings::DSG_OC2 =
{
	"放电过流+短路设置",
	{
		{"保护2电流", "mA", 0, 19900},
		{"保护2延时", "ms", 2000, 5000},
		{"短路电流", "mA", 0, 19900},
		{"短路延时", "us", 2000, 5000},
		{"保护自动解除", "ms", 0, 19900},
		{"锁住次数", "/", 1, 30},
		{"充电解除", "mA", 1, 30},
	}
};

// 定义并初始化settingsList
const SETTINGS_TYPE CurrentSettings::settingsList = {
	CurrentSettings::CHG_OC,
	CurrentSettings::DSG_OC,
	CurrentSettings::DSG_OC2,
};

const QPair<QString, QList<Setting>> TemperatureSettings::CHG_OT_UT =
{
	"充电高低温",
	{
		{"高温警告", "℃", 2000, 5000},
		{"高温保护1温度", "℃", 0, 19900},
		{"高温保护1恢复", "℃", 2000, 5000},
		{"低温警告", "℃", 0, 19900},
		{"低温保护1温度", "℃", 2000, 5000},
		{"低温保护1温度", "℃", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> TemperatureSettings::DSG_OT_UT =
{
	"放电高低温",
	{
		{"高温警告", "℃", 2000, 5000},
		{"高温保护1温度", "℃", 0, 19900},
		{"高温保护1恢复", "℃", 2000, 5000},
		{"低温警告", "℃", 0, 19900},
		{"低温保护1温度", "℃", 2000, 5000},
		{"低温保护1温度", "℃", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> TemperatureSettings::ENV_OT_UT =
{
	"环境高低温",
	{
		{"高温警告", "℃", 2000, 5000},
		{"高温保护1温度", "℃", 0, 19900},
		{"高温保护1恢复", "℃", 2000, 5000},
		{"低温警告", "℃", 0, 19900},
		{"低温保护1温度", "℃", 2000, 5000},
		{"低温保护1温度", "℃", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> TemperatureSettings::MOS_OT_UT =
{
	"MOS高低温",
	{
		{"充电低温警告", "℃", 0, 19900},
		{"充电低温保护", "℃", 2000, 5000},
		{"充电低温恢复", "℃", 2000, 5000},
		{"放电高温警告", "℃", 2000, 5000},
		{"放电高温保护", "℃", 0, 19900},
		{"放电高温恢复", "℃", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> TemperatureSettings::HEAT =
{
	"加热膜参数",
	{
		{"启动温度", "℃", 2000, 5000},
		{"解除温度", "℃", 0, 19900},
	}
};

// 定义并初始化settingsList
const SETTINGS_TYPE TemperatureSettings::settingsList = {
	TemperatureSettings::CHG_OT_UT,
	TemperatureSettings::DSG_OT_UT,
	TemperatureSettings::ENV_OT_UT,
	TemperatureSettings::MOS_OT_UT,
	TemperatureSettings::HEAT,
};

const QPair<QString, QList<Setting>> LowSOCSettings::LOW_SOC =
{
	"SOC低电量",
	{
		{"警告", "%", 2000, 5000},
		{"放电截止容量", "%", 0, 19900},
		{"放电截止解除容量", "%", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_TYPE LowSOCSettings::settingsList = {
	LowSOCSettings::LOW_SOC,
};

const QPair<QString, QList<Setting>> BatterySettings::SLEEP =
{
	"休眠设置",
	{
		{"系统自损耗", "mW", 2000, 5000},
		{"单体休眠电压", "mV", 0, 19900},
		{"静置休眠延时", "ms", 2000, 5000},
		{"定时巡检时间", "ms", 0, 19900},
		{"单体SHIP电压", "mV", 2000, 5000},
	}
};

const QPair<QString, QList<Setting>> BatterySettings::CELL =
{
	"Pack参数设置",
	{
		{"电芯串数", "/", 2000, 5000},
		{"电芯类型", "/", 0, 19900},
		{"设计容量", "mAH", 2000, 5000},
		{"满充容量", "mAH", 0, 19900},
		{"剩余容量", "mAH", 2000, 5000},
		{"充电循环次数", "/", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_TYPE BatterySettings::settingsList = {
	BatterySettings::SLEEP,
	BatterySettings::CELL,
};