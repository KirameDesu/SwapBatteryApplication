#include "TempSettingsModel.h"

TempSettingsModel::TempSettingsModel(BaseModel* parent)
{
	initializeSettings(TemperatureSettings::getAllSettings());
}

TempSettingsModel::~TempSettingsModel()
{
}

void TempSettingsModel::emitDataChanged()
{
	emit TempSettingsModel::dataChanged();
}
