#ifndef BASE_UPGRADE_H
#define BASE_UPGRADE_H

#include <QString>

class BaseProtocol {

public:
	virtual ~BaseProtocol() {
	}
	// 写入报文
	//virtual void write() = 0;
	// 升级报文
	virtual QByteArray startUpgradeRawData() = 0;
	virtual QByteArray UpgradePackRawData(int packNo) = 0;
	virtual QByteArray endUpgradeRawData() = 0;
	virtual void setFilePath(const QString& path);
	//virtual QList<QByteArray> getPackList() = 0;
protected:


private:
	QString _upgradeFilePath = "";
};

#endif // !BASE_UPGRADE_H
