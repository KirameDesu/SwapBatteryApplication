#include "InverterSettingsModel.h"

InverterSettingsModel::InverterSettingsModel(BaseModel* parent)
{
	initializeSettings(InverterSettings::getAllSettings());
}

InverterSettingsModel::~InverterSettingsModel()
{
}

void InverterSettingsModel::emitDataChanged()
{
	emit InverterSettingsModel::dataChanged();
}
