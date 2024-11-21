#include "ModelManager.h"

ModelManager::ModelManager()
{
	_voltProtModel = new VoltageProtectModel();
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
		_voltProtModel->parse(rawData);
	else if (TemperatureSettings::isAddrInRange(startAddr))
		_voltProtModel->parse(rawData);
	else if (LowSOCSettings::isAddrInRange(startAddr))
		_voltProtModel->parse(rawData);
	else if (BatterySettings::isAddrInRange(startAddr))
		_voltProtModel->parse(rawData);

	return false;
}
