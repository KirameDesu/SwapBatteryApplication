#ifndef BATTERY_OVERVIEW_MODEL_H
#define BATTERY_OVERVIEW_MODEL_H

#include "BaseModel.h"

class BatteryOverviewModel : public BaseModel
{
	Q_OBJECT

public:
	explicit BatteryOverviewModel(BaseModel* parent = nullptr);
	~BatteryOverviewModel();

	void emitDataChanged() override;
private:
};

#endif // !BATTERY_OVERVIEW_MODEL_H
