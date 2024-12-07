// ParameterSettings.cpp 寄存器定义
// 每个同一组的寄存器起始地址必须要连续
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
		{_SW, "故障状态", "", 0, 2 ^ 16 - 1},
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
	"SOC数据", 	0X0800 + BatteryOverview::getCellSize(0),
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
	BatteryOverview::SOCItems,
};
qint16 BatteryOverview::startAddress = calculateStartAddress(BatteryOverview::settingsList);
int BatteryOverview::totalRegisters = calculateTotalRegisters(BatteryOverview::settingsList);
//======================================================================================================
//                                          电压设置
//======================================================================================================
const SETTINGS_CELL VoltSettings::CELL_UV =
{
	"单体低压设置", 	0X1200,
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
		{_SEMA, "解除保护SOC", "%", 2000, 5000},
		{_SEMA, "解除保护SOC延时", "%", 2000, 5000},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
		{_SEMA, "解除保护电流延时", "ms", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::CELL_OV =
{
	"单体高压设置",	0X1220,
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
		{_SEMA, "解除保护SOC", "%", 2000, 5000},
		{_SEMA, "解除保护SOC延时", "%", 2000, 5000},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
		{_SEMA, "解除保护电流延时", "ms", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::DiffVolt =
{
	"单体压差设置",	0X1240,
	{
		{_SEMA, "警告压差", "mV", 2000, 5000},
		{_SEMA, "警告压差延时", "ms", 2000, 5000},
		{_SEMA, "警告失效压差", "mV", 2000, 5000},
		{_SEMA, "警告失效压差延时", "ms", 2000, 5000},
		{_SEMA, "保护压差", "mV", 2000, 5000},
		{_SEMA, "保护压差延时", "ms", 2000, 5000},
		{_SEMA, "保护失效压差", "mV", 2000, 5000},
		{_SEMA, "保护失效压差延时", "ms", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::MinFailVolt =
{
	"单体失效最小电压设置",	0X1250,
	{
		{_SEMA, "单体失效警告电压", "mV", 2000, 5000},
		{_SEMA, "单体失效警告延时", "ms", 2000, 5000},
		{_SEMA, "单体失效释放电压", "mV", 2000, 5000},
		{_SEMA, "单体失效释放延时", "ms", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::MaxFailVolt =
{
	"单体失效最大电压设置",	0X1258,
	{
		{_SEMA, "单体失效警告电压", "mV", 2000, 5000},
		{_SEMA, "单体失效警告延时", "ms", 2000, 5000},
		{_SEMA, "单体失效释放电压", "mV", 2000, 5000},
		{_SEMA, "单体失效释放延时", "ms", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::PACK_UV =
{
	"总体欠压设置", 	0X1260,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "警告电压延时", "ms", 2000, 5000},
		{_SEMA, "警告失效电压", "mV", 2000, 5000},
		{_SEMA, "警告失效电压延时", "ms", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
		{_SEMA, "保护1恢复延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复SOC", "%", 0, 100},
		{_SEMA, "保护1恢复SOC延时", "%", 0, 100},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
		{_SEMA, "解除保护延时", "mA", 2000, 5000},
	}
};

const SETTINGS_CELL VoltSettings::PACK_OV =
{
	"总体过压设置",	0X1278,
	{
		{_SEMA, "警告电压", "mV", 2000, 5000},
		{_SEMA, "警告电压延时", "ms", 2000, 5000},
		{_SEMA, "警告失效电压", "mV", 2000, 5000},
		{_SEMA, "警告失效电压延时", "ms", 2000, 5000},
		{_SEMA, "保护1电压", "mV", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复电压", "mV", 0, 19900},
		{_SEMA, "保护1恢复延时", "ms", 2000, 5000},
		{_SEMA, "保护1恢复SOC", "%", 0, 100},
		{_SEMA, "保护1恢复SOC延时", "%", 0, 100},
		{_SEMA, "解除保护电流", "mA", 2000, 5000},
		{_SEMA, "解除保护延时", "mA", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS VoltSettings::settingsList = {
	VoltSettings::CELL_OV,
	VoltSettings::CELL_UV,
	VoltSettings::DiffVolt,
	VoltSettings::MinFailVolt,
	VoltSettings::MaxFailVolt,
	VoltSettings::PACK_UV,
	VoltSettings::PACK_OV,
};
//qint16 VoltSettings::startAddress = calculateStartAddress(VoltSettings::settingsList);
qint16 VoltSettings::startAddress = 0x1200;
int VoltSettings::totalRegisters = calculateTotalRegisters(VoltSettings::settingsList);

//======================================================================================================
//                                          电流设置
//======================================================================================================
const SETTINGS_CELL CurrentSettings::CHG_OC =
{
	"充电过流设置",	0X1310,
	{
		{_SEMA, "警告电流", "mA", 2000, 5000},
		{_SEMA, "警告延时", "mA", 2000, 5000},
		{_SEMA, "警告释放电流", "mA", 2000, 5000},
		{_SEMA, "警告释放延时", "mA", 2000, 5000},
		{_SEMA, "保护1电流", "mA", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护2电流", "mA", 0, 19900},
		{_SEMA, "保护2延时", "ms", 2000, 5000},
		{_SEMA, "保护恢复电流", "mA", 0, 19900},
		{_SEMA, "保护恢复延时", "ms", 0, 19900},
		{_SEMA, "最大锁住次数", "/", 1, 30},
		{_SEMA, "尝试自动解除时间", "ms", 1, 30},
		{_SEMA, "自锁监控周期", "ms", 1, 30},
	}
};

const SETTINGS_CELL CurrentSettings::DSG_OC =
{
	"放电过流设置",	0X1310,
	{
		{_SEMA, "警告电流", "mA", 2000, 5000},
		{_SEMA, "警告延时", "mA", 2000, 5000},
		{_SEMA, "警告释放电流", "mA", 2000, 5000},
		{_SEMA, "警告释放延时", "mA", 2000, 5000},
		{_SEMA, "保护1电流", "mA", 0, 19900},
		{_SEMA, "保护1延时", "ms", 2000, 5000},
		{_SEMA, "保护2电流", "mA", 0, 19900},
		{_SEMA, "保护2延时", "ms", 2000, 5000},
		{_SEMA, "保护恢复电流", "mA", 0, 19900},
		{_SEMA, "保护恢复延时", "ms", 0, 19900},
		{_SEMA, "最大锁住次数", "/", 1, 30},
		{_SEMA, "尝试自动解除时间", "ms", 1, 30},
		{_SEMA, "自锁监控周期", "ms", 1, 30},
	}
};

const SETTINGS_CELL CurrentSettings::DSG_SC =
{
	"放电短路设置",	0X1310,
	{
		{_SEMA, "短路电流", "mA", 0, 19900},
		{_SEMA, "短路延时", "ms", 2000, 5000},
		{_SEMA, "短路恢复电流", "mA", 2000, 5000},
		{_SEMA, "短路恢复延时", "ms", 2000, 5000},
		{_SEMA, "最大锁住次数", "/", 1, 30},
		{_SEMA, "尝试自动解除时间", "ms", 1, 30},
		{_SEMA, "自锁监控周期", "ms", 1, 30},
	}
};

const SETTINGS_CELL CurrentSettings::CHG_MOS_FAIL =
{
	"充电MOS失效设置",	0X1310,
	{
		{_SEMA, "警告电流", "mA", 2000, 5000},
		{_SEMA, "警告延时", "mA", 2000, 5000},
		{_SEMA, "警告释放电流", "mA", 2000, 5000},
		{_SEMA, "警告释放延时", "mA", 2000, 5000},
	}
};

const SETTINGS_CELL CurrentSettings::DSG_MOS_FAIL =
{
	"放电MOS失效设置",	0X1310,
	{
		{_SEMA, "警告电流", "mA", 2000, 5000},
		{_SEMA, "警告延时", "mA", 2000, 5000},
		{_SEMA, "警告释放电流", "mA", 2000, 5000},
		{_SEMA, "警告释放延时", "mA", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS CurrentSettings::settingsList = {
	CurrentSettings::CHG_OC,
	CurrentSettings::DSG_OC,
	CurrentSettings::DSG_SC,
	CurrentSettings::CHG_MOS_FAIL,
	CurrentSettings::DSG_MOS_FAIL,
};
qint16 CurrentSettings::startAddress = calculateStartAddress(CurrentSettings::settingsList);
int CurrentSettings::totalRegisters = calculateTotalRegisters(CurrentSettings::settingsList);


//======================================================================================================
//                                          温度设置
//======================================================================================================
const SETTINGS_CELL TemperatureSettings::CHG_UT =
{
	"充电低温",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

const SETTINGS_CELL TemperatureSettings::CHG_OT =
{
	"充电高温",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

const SETTINGS_CELL TemperatureSettings::DSG_UT =
{
	"放电低温",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

const SETTINGS_CELL TemperatureSettings::DSG_OT =
{
	"放电高温",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

const SETTINGS_CELL TemperatureSettings::Temp_Diff =
{
	"电芯温差",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

const SETTINGS_CELL TemperatureSettings::ENV_UT =
{
	"环境低温",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

const SETTINGS_CELL TemperatureSettings::ENV_OT =
{
	"环境高温",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

const SETTINGS_CELL TemperatureSettings::MOS_OT =
{
	"MOS高温",		0X1290,
	{
		{_SEMA, "警告温度", "℃", 2000, 5000},
		{_SEMA, "警告延时", "℃", 2000, 5000},
		{_SEMA, "警告释放温度", "℃", 2000, 5000},
		{_SEMA, "警告释放延时", "℃", 2000, 5000},
		{_SEMA, "保护1温度", "℃", 0, 19900},
		{_SEMA, "保护1延时", "℃", 0, 19900},
		{_SEMA, "保护1释放温度", "℃", 0, 19900},
		{_SEMA, "保护1延时延时", "℃", 0, 19900},
	}
};

//const SETTINGS_CELL TemperatureSettings::HEAT =
//{
//	"加热膜参数", 	0X2500,
//	{
//		{_SEMA, "启动温度", "℃", 2000, 5000},
//		{_SEMA, "解除温度", "℃", 0, 19900},
//	}
//};

// 定义并初始化settingsList
const SETTINGS_CLASS TemperatureSettings::settingsList = {
	TemperatureSettings::CHG_UT,
	TemperatureSettings::CHG_OT,
	TemperatureSettings::DSG_UT,
	TemperatureSettings::DSG_OT,
	TemperatureSettings::Temp_Diff,
	TemperatureSettings::ENV_UT,
	TemperatureSettings::ENV_OT,
	TemperatureSettings::MOS_OT,
	//TemperatureSettings::HEAT,
};
qint16 TemperatureSettings::startAddress = calculateStartAddress(TemperatureSettings::settingsList);
int TemperatureSettings::totalRegisters = calculateTotalRegisters(TemperatureSettings::settingsList);


//======================================================================================================
//                                          低电量设置
//======================================================================================================
const SETTINGS_CELL LowSOCSettings::LOW_SOC =
{
	"SOC低电量",		0X1362,
	{
		{_SEMA, "警告容量", "%", 2000, 5000},
		{_SEMA, "警告延时", "%", 2000, 5000},
		{_SEMA, "警告释放容量", "%", 2000, 5000},
		{_SEMA, "警告释放延时", "%", 2000, 5000},
		{_SEMA, "保护容量", "%", 2000, 5000},
		{_SEMA, "保护延时", "%", 2000, 5000},
		{_SEMA, "保护释放容量", "%", 2000, 5000},
		{_SEMA, "保护释放延时", "%", 2000, 5000},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS LowSOCSettings::settingsList = {
	LowSOCSettings::LOW_SOC,
};
qint16 LowSOCSettings::startAddress = calculateStartAddress(LowSOCSettings::settingsList);
int LowSOCSettings::totalRegisters = calculateTotalRegisters(LowSOCSettings::settingsList);

//======================================================================================================
//                                          电池参数设置
//======================================================================================================
const SETTINGS_CELL BatterySettings::Func_Switch =
{
	"功能开关",		0X1400,
	{
		{_SW, "功能开关1", "", 0, 65535},
		{_SW, "功能开关2", "", 0, 65535},
		{_SW, "功能开关3", "", 0, 65535},
		{_SW, "功能开关4", "", 0, 65535},
	}
};

const SETTINGS_CELL BatterySettings::Battery_Para =
{
	"电池参数",		0X1400,
	{
		{_SEMA, "电芯数量", "/", 0, 65535},
		{_SEMA, "电芯种类", "mAH", 0, 65535},
		{_SEMA, "设计容量", "mAH", 0, 65535},
		{_SEMA, "满充容量", "mAH", 0, 65535},
		{_SEMA, "剩余容量", "mAH", 0, 65535},
		{_SEMA, "放电循环次数", "/", 0, 65535},
		{_SEMA, "充电循环次数", "/", 0, 65535},
		{_SEMA, "SOC", "%", 0, 65535},
		{_SEMA, "SOH", "%", 0, 65535},
		{_SEMA, "充电最长持续时间", "min", 0, 65535},
	}
};

const SETTINGS_CELL BatterySettings::CHG_DSG_INFO =
{
	"充放电信息",	0X1400,
	{
		{_SEMA, "放电总容量1", "mAH", 0, 65535},
		{_SEMA, "放电总容量2", "mAH", 0, 65535},
		{_SEMA, "充电总容量1", "mAH", 0, 65535},
		{_SEMA, "充电总容量2", "mAH", 0, 65535},
		{_SEMA, "总充电时间1", "s", 0, 65535},
		{_SEMA, "总充电时间2", "s", 0, 65535},
		{_SEMA, "总放电时间1", "s", 0, 65535},
		{_SEMA, "总放电时间2", "s", 0, 65535},
		{_SEMA, "最近未放电时间1", "s", 0, 65535},
		{_SEMA, "最近未放电时间2", "s", 0, 65535},
		{_SEMA, "最近未充电时间1", "s", 0, 65535},
		{_SEMA, "最近未充电时间2", "s", 0, 65535},
		{_SEMA, "最长未充电时间1", "s", 0, 65535},
		{_SEMA, "最长未充电时间2", "s", 0, 65535},
		{_SEMA, "最长未充电时间1", "s", 0, 65535},
		{_SEMA, "最长未充电时间2", "s", 0, 65535},
	}
};

const SETTINGS_CELL BatterySettings::Other =
{
	"电池参数",		0X1400,
	{
		{_SEMA, "采样电阻1阻值", "Ω", 0, 65535},
		{_SEMA, "采样电阻2阻值", "Ω", 0, 65535},
		{_SEMA, "满充单体电压", "mV", 0, 65535},
		{_SEMA, "满充总压", "mV", 0, 65535},
		{_SEMA, "充电截止电流", "mV", 0, 65535},
		{_SEMA, "满充解除SOC值", "mA", 0, 65535},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS BatterySettings::settingsList = {
	BatterySettings::Func_Switch,
	BatterySettings::Battery_Para,
	BatterySettings::CHG_DSG_INFO,
	BatterySettings::Other,
};
qint16 BatterySettings::startAddress = calculateStartAddress(BatterySettings::settingsList);
int BatterySettings::totalRegisters = calculateTotalRegisters(BatterySettings::settingsList);


//======================================================================================================
//                                          BMS功能参数设置
//======================================================================================================
const SETTINGS_CELL FunctionSettings::Limit_Broad =
{
	"限流板设置",		0x1448,
	{
		{_SEMA, "启动电流", "mA", 0, 65535},
		{_SEMA, "启动单体电压", "mV", 0, 65535},
		{_SEMA, "线路板工作累计时间", "s", 0, 65535},
	}
};

const SETTINGS_CELL FunctionSettings::Pre_CHG_DSG =
{
	"预充预放设置",		0x1448,
	{
		{_SW, "预充/预放打开", "Ω", 0, 65535},
		{_SEMA, "预充打开持续时间", "ms", 0, 65535},
		{_SEMA, "预放打开持续时间", "ms", 0, 65535},
	}
};

const SETTINGS_CELL FunctionSettings::Balance =
{
	"均衡设置",		0x1448,
	{
		{_SEMA, "充电/静置 均衡触发单体电压", "mV", 0, 65535},
		{_SEMA, "充电/静置 均衡触发单体压差", "mV", 0, 65535},
		{_SEMA, "充电/静置 均衡解除单体压差", "mV", 0, 65535},
		{_SEMA, "均衡触发单体电压", "mV", 0, 65535},
		{_SEMA, "均衡触发单体压差", "mV", 0, 65535},
		{_SEMA, "均衡解除单体压差", "mA", 0, 65535},
	}
};

const SETTINGS_CELL FunctionSettings::Heat =
{
	"加热膜设置",		0x1448,
	{
		{_SEMA, "加热膜启动温度", "℃", 0, 65535},
		{_SEMA, "加热膜解除温度", "℃", 0, 65535},
	}
};

const SETTINGS_CELL FunctionSettings::Power_Loss =
{
	"电源功耗管理",		0x1448,
	{
		{_SEMA, "采样电阻1阻值", "Ω", 0, 65535},
		{_SEMA, "采样电阻2阻值", "Ω", 0, 65535},
		{_SEMA, "满充单体电压", "mV", 0, 65535},
		{_SEMA, "满充总压", "mV", 0, 65535},
		{_SEMA, "充电截止电流", "mV", 0, 65535},
		{_SEMA, "满充解除SOC值", "mA", 0, 65535},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS FunctionSettings::settingsList = {
	FunctionSettings::Limit_Broad,
	FunctionSettings::Pre_CHG_DSG,
	FunctionSettings::Balance,
	FunctionSettings::Heat,
	FunctionSettings::Power_Loss,
};
qint16 FunctionSettings::startAddress = calculateStartAddress(FunctionSettings::settingsList);
int FunctionSettings::totalRegisters = calculateTotalRegisters(FunctionSettings::settingsList);


//======================================================================================================
//                                          逆变器设置
//======================================================================================================
const SETTINGS_CELL InverterSettings::Inverter_Protocol =
{
	"通讯协议设置",		0x14CC,
	{
		{_SEMA, "CAN协议", "", 0, 65535},
		{_SEMA, "485协议", "", 0, 65535},
		{_SEMA, "充电截止电压", "mV", 0, 65535},
		{_SEMA, "放电截止电压", "mV", 0, 65535},
		{_SEMA, "充电最大电流", "mA", 0, 65535},
		{_SEMA, "放电最大电流", "mA", 0, 65535},
	}
};

const SETTINGS_CELL InverterSettings::Force_CHG =
{
	"强充参数",		0x14CC,
	{
		{_SEMA, "启动SOC", "%", 0, 65535},
		{_SEMA, "解除SOC", "%", 0, 65535},
		{_SEMA, "放电使能SOC阀值", "%", 0, 65535},
	}
};

// 定义并初始化settingsList
const SETTINGS_CLASS InverterSettings::settingsList = {
	InverterSettings::Inverter_Protocol,
	InverterSettings::Force_CHG,
};
qint16 InverterSettings::startAddress = calculateStartAddress(InverterSettings::settingsList);
int InverterSettings::totalRegisters = calculateTotalRegisters(InverterSettings::settingsList);