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
	virtual void applyWidget(QWidget* w) = 0;					//应用设置界面
	virtual void apply() = 0;									//应用设置
};

#endif // !BASE_COMMS_SETTING_H