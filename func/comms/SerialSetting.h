#ifndef SERIAL_SETTING_H
#define SERIAL_SETTING_H

#include "AbstractCommsSetting.h"

class SerialSetting : public AbstractCommsSetting
{
public:
	explicit SerialSetting(AbstractCommsSetting* parenet = nullptr);
	~SerialSetting();

	CommunicationType getCommsType() const override;			//获取通讯类型
	void applyWidget(QWidget* w) override;				//得到设置界面
	virtual void apply() override;						//应用设置
};

#endif // !SERIAL_SETTING_H
