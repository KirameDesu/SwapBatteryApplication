#include "FunctionSettingsModel.h"

FunctionSettingsModel::FunctionSettingsModel(BaseModel* parent)
{
	initializeSettings(FunctionSettings::getAllSettings());
}

FunctionSettingsModel::~FunctionSettingsModel()
{
}

void FunctionSettingsModel::emitDataChanged()
{
	emit FunctionSettingsModel::dataChanged();
}
