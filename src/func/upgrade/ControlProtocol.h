#ifndef CONTROL_UPGRADE_H
#define CONTROL_UPGRADE_H

#include <QByteArray>

#include "BaseProtocol.h"

//namespace control_protocol
//{
//	enum class parseResult{
//		Success,
//		ArrayIsEmpty,		// 数组为空
//		InvalidHead,		// 报文头无效
//		InvalidLength,		// 长度无效
//		InvalidCRC,			// CRC无效
//	};
//
//	parseResult responseHandle(const QByteArray& rawData);
//}

class ControlProtocol : public BaseProtocol
{
public:
	ControlProtocol();
	~ControlProtocol();

	QByteArray startUpgradeRawData() override;
	QByteArray UpgradePackRawData(int packNo) override;
	QByteArray endUpgradeRawData() override;
	void setFilePath(const QString& path) override;
	parseResult responseHandle(const QByteArray& rawData) override;
	//parseResult responseHandle(const QByteArray& rawData);

private:
};



#endif // !CONTROL_UPGRADE_H
