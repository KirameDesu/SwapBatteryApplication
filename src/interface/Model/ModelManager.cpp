#include "ModelManager.h"

ModelManager::ModelManager()
{
	_voltProtModel = new VoltageProtectModel();
	_currProtModel = new CurrentProtectModel();
	_tempSettingsModel = new TempSettingsModel();
	_lowSOCSettingsModel = new LowSOCSettingsModel();
	_battSettingsModel = new BatterySettingsModel();
}

ModelManager::~ModelManager()
{
	delete _voltProtModel;
}

bool ModelManager::parseHandle(int startAddr, QByteArray rawData)
{
	// 根据起始地址判断对应Model
	if (VoltSettings::isAddrInRange(startAddr))
		_voltProtModel->parse(rawData);
	else if (CurrentSettings::isAddrInRange(startAddr))
		_currProtModel->parse(rawData);
	else if (TemperatureSettings::isAddrInRange(startAddr))
		_tempSettingsModel->parse(rawData);
	else if (LowSOCSettings::isAddrInRange(startAddr))
		_lowSOCSettingsModel->parse(rawData);
	else if (BatterySettings::isAddrInRange(startAddr))
		_battSettingsModel->parse(rawData);

	return false;
}
