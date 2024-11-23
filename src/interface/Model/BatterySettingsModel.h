#ifndef BATTERY_SETTINGS_MODEL_H
#define BATTERY_SETTINGS_MODEL_H

#include "BaseModel.h"

class BatterySettingsModel : public BaseModel
{
	Q_OBJECT

public:
	explicit BatterySettingsModel(BaseModel* parent = nullptr);
	~BatterySettingsModel();
	
	void emitDataChanged() override;
private:

};

#endif // !BATTERY_SETTINGS_MODEL_H
