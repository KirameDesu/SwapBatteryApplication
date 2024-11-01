#ifndef BASE_COMMS_SETTING_H
#define BASE_COMMS_SETTING_H

#include <QWidget>

enum class CommunicationType {
	Bluetooth,
	Serial,
	TCP,
	UDP,
};

class AbstractCommsSetting
{
public:
	virtual ~AbstractCommsSetting() = default;
	virtual CommunicationType getCommsType() const = 0;			//获取通讯类型
	virtual void applyWidget(QWidget* settingsWidget) = 0;					//应用设置界面

	virtual QWidget* getWidget() = 0;							//返回界面指针
	virtual QString getSettingsString() = 0;					//返回设置字符串

	QWidget* settingsWidget{ nullptr };										//界面指针
};

#endif // !BASE_COMMS_SETTING_H