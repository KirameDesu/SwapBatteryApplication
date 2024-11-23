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

	static VoltageProtectModel* getVoltProtectModel() {
		return _voltProtModel;
	}
	static CurrentProtectModel* getCurrProtectModel() {
		return _currProtModel;
	}
	static TempSettingsModel* getTempSettingsModel() {
		return _tempSettingsModel;
	}
	static LowSOCSettingsModel* getLowSOCSettingsModel() {
		return _lowSOCSettingsModel;
	}
	static BatterySettingsModel* getBattSettingsModel() {
		return _battSettingsModel;
	}
private:
	static VoltageProtectModel* _voltProtModel;
	static CurrentProtectModel* _currProtModel;
	static TempSettingsModel* _tempSettingsModel;
	static LowSOCSettingsModel* _lowSOCSettingsModel;
	static BatterySettingsModel* _battSettingsModel;
};



#endif // !MODEL_MANAGER_H
