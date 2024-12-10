#include "BaseProtocol.h"

#include <QFile>

void BaseProtocol::setFilePath(const QString& path)
{
	_upgradeFilePath = path;
}

float BaseProtocol::getUpgradeProcessPercent()
{
	if (totalPackNum == 0) {
		// 避免除零
		return 0.0;
	}

	return (static_cast<float>(currentPackNo) / totalPackNum) * 100.0;

	return 0;
}

int BaseProtocol::getUpgradeTotalPackNum()
{
	return totalPackNum;
}

void BaseProtocol::resetUpgradeState()
{
	currentPackNo = 0;
	totalPackNum = 0;
}
