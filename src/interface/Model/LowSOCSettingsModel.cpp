#include "LowSOCSettingsModel.h"

LowSOCSettingsModel::LowSOCSettingsModel(BaseModel* parent)
{
	initializeSettings(LowSOCSettings::getAllSettings());
}

LowSOCSettingsModel::~LowSOCSettingsModel()
{
}

void LowSOCSettingsModel::parse(const QByteArray& rawData)
{
	/// 将报文数据解析到对应值上
	settingsList.value("123");

	// 如果有修改值，则发送信号
	emit dataChanged();
}
