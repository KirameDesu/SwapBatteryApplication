#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <QByteArray>

#include "VoltageProtectModel.h"
#include "CurrentProtectModel.h"
#include "TempSettingsModel.h"
#include "LowSOCSettingsModel.h"
#include "BatterySettingsModel.h"
#include "FunctionSettingsModel.h"
#include "InverterSettingsModel.h"
#include "BatteryOverviewModel.h"

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	bool parseHandle(int startAddr, QByteArray rawData);

	static BatteryOverviewModel* getBatteryOverviewModel() {
		return _battOverviewModel;
	}
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
	static FunctionSettingsModel* getFunctionSettingsModel() {
		return _funcSettingsModel;
	}
	static InverterSettingsModel* getInverterSettingsModel() {
		return _inverterSettingsModel;
	}
private:
	static BatteryOverviewModel* _battOverviewModel;

	static VoltageProtectModel* _voltProtModel;
	static CurrentProtectModel* _currProtModel;
	static TempSettingsModel* _tempSettingsModel;
	static LowSOCSettingsModel* _lowSOCSettingsModel;
	static BatterySettingsModel* _battSettingsModel;
	static FunctionSettingsModel* _funcSettingsModel;
	static InverterSettingsModel* _inverterSettingsModel;
};



#endif // !MODEL_MANAGER_H
