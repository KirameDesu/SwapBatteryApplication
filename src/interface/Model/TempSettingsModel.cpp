#include "TempSettingsModel.h"

TempSettingsModel::TempSettingsModel(BaseModel* parent)
{
	initializeSettings(TemperatureSettings::getAllSettings());
}

TempSettingsModel::~TempSettingsModel()
{
}

void TempSettingsModel::parse(const QByteArray& rawData)
{
	/// 将报文数据解析到对应值上
	settingsList.value("123");

	// 如果有修改值，则发送信号
	emit dataChanged();
}
