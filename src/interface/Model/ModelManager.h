#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <QByteArray>

#include "VoltageProtectModel.h"
#include "CurrentProtectModel.h"
#include "TempSettingsModel.h"
#include "LowSOCSettingsModel.h"
#include "BatterySettingsModel.h"

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	bool parseHandle(int startAddr, QByteArray rawData);
private:
	VoltageProtectModel* _voltProtModel{ nullptr };
	CurrentProtectModel* _currProtModel{ nullptr };
	TempSettingsModel* _tempSettingsModel{ nullptr };
	LowSOCSettingsModel* _lowSOCSettingsModel{ nullptr };
	BatterySettingsModel* _battSettingsModel{ nullptr };
};

#endif // !MODEL_MANAGER_H
