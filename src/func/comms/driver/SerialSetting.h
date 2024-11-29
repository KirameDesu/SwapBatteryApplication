#ifndef SERIAL_SETTING_H
#define SERIAL_SETTING_H

#include "AbstractCommsSetting.h"

#include <QComboBox>

#include "ElaComboBox.h"

class SerialSetting : public AbstractCommsSetting
{
	Q_OBJECT

public:
	explicit SerialSetting(AbstractCommsSetting* parenet = nullptr);
	~SerialSetting();

	CommunicationType getCommsType() const override;		//获取通讯类型
	void applyWidget(QWidget* settingsWidget) override;		//设置界面

	QWidget* getWidget() override;							//返回界面指针
	QString getSettingsString() override;					//返回设置字符串

	QWidget* getWidgetFromName(QString name) override;		//通过控件名称获取控件指针

	ElaComboBox* getCOMComboBox();
	ElaComboBox* getBaudComboBox();							
	void updateSerialPortNamesToComboBox(QComboBox* cb);	//刷新串口列表到多选框
	QStringList getSerialNameList();						//得到串口列表

private:
	ElaComboBox* _portComboBox{ nullptr };
	ElaComboBox* _baudComboBox{ nullptr };
};

#endif // !SERIAL_SETTING_H
