#include "LowSOCSettingsModel.h"

LowSOCSettingsModel::LowSOCSettingsModel(BaseModel* parent)
{
	initializeSettings(LowSOCSettings::getAllSettings());
}

LowSOCSettingsModel::~LowSOCSettingsModel()
{
}

void LowSOCSettingsModel::emitDataChanged()
{
    emit LowSOCSettingsModel::dataChanged();
}

