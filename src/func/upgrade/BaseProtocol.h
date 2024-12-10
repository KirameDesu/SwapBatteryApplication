#ifndef BASE_UPGRADE_H
#define BASE_UPGRADE_H

#include <QObject>
#include <QString>
#include <QByteArray>

enum class UpgradeStep
{
	prepareUpgrade = 0,
	sendPack,
	checkUpgrade,
	endUpgrade
};

class BaseProtocol : public QObject {
	Q_OBJECT

public:
	enum class parseResult {
		Success,
		ArrayIsEmpty,		// 数组为空
		InvalidHead,		// 报文头无效
		InvalidLength,		// 长度无效
		InvalidCRC,			// CRC无效
		InvalidPackNo,		// 应答升级包序号无效
	};


	virtual ~BaseProtocol() {
	}
	// 写入报文
	//virtual void write() = 0;
	// 升级报文
	virtual QByteArray startUpgradeRawData() = 0;
	virtual QByteArray UpgradePackRawData(int packNo) = 0;
	virtual QByteArray endUpgradeRawData() = 0;
	virtual void setFilePath(const QString& path);

	 //原始数据数组解析函数
	virtual parseResult responseHandle(const QByteArray& rawData) = 0;
	//virtual QList<QByteArray> getPackList() = 0;

	float getUpgradeProcessPercent();
	int getUpgradeTotalPackNum();
	void resetUpgradeState();
signals:
	Q_SIGNAL void nextProcess(UpgradeStep step);

protected:
	QByteArray upgradeFileRawData;			// 升级包数组
	int upgradeTotalSize;					// 升级包总数据大小
	int upgradePackSize;					// 升级包一包大小
	int u32UgradeTotalCRC;					// 校验CRC32
	int currentPackNo = 0;					// 当前接收包序号
	int totalPackNum;						// 分包总数量

private:
	QString _upgradeFilePath = "";
};

#endif // !BASE_UPGRADE_H
