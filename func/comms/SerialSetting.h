#ifndef SERIAL_SETTING_H
#define SERIAL_SETTING_H

#include "AbstractCommsSetting.h"

class SerialSetting : public AbstractCommsSetting
{
public:
	explicit SerialSetting(AbstractCommsSetting* parenet = nullptr);
	~SerialSetting();

	CommunicationType getCommsType() const override;		//获取通讯类型
	void applyWidget(QWidget* settingsWidget) override;					//设置界面

	QWidget* getWidget() override;							//返回界面指针
	QString getSettingsString() override;					//返回设置字符串
};

#endif // !SERIAL_SETTING_H
