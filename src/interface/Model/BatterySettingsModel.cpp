#include "BatterySettingsModel.h"

BatterySettingsModel::BatterySettingsModel(BaseModel* parent)
{
	initializeSettings(BatterySettings::getAllSettings());
}

BatterySettingsModel::~BatterySettingsModel()
{
}

void BatterySettingsModel::emitDataChanged()
{
	emit BatterySettingsModel::dataChanged();
}
