#ifndef CONTROL_UPGRADE_H
#define CONTROL_UPGRADE_H

#include <QByteArray>

#include "BaseProtocol.h"

class ControlProtocol : public BaseProtocol
{
public:
	ControlProtocol();
	~ControlProtocol();

	QByteArray startUpgradeRawData() override;
	QByteArray UpgradePackRawData(int packNo) override;
	QByteArray endUpgradeRawData() override;
	void setFilePath(const QString& path) override;
private:

};



#endif // !CONTROL_UPGRADE_H
