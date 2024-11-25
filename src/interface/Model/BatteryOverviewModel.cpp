#include "BatteryOverviewModel.h"

BatteryOverviewModel::BatteryOverviewModel(BaseModel* parent)
{
	initializeSettings(BatteryOverview::getAllSettings());
}

BatteryOverviewModel::~BatteryOverviewModel()
{
}

void BatteryOverviewModel::emitDataChanged()
{
	emit BatteryOverviewModel::dataChanged();
}
