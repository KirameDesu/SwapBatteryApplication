#ifndef COMMS_SETTING_PAGE_H
#define COMMS_SETTING_PAGE_H

#include "ElaWidget.h"
#include "Communication.h"

#include <QWidget>
#include <QVBoxLayout>

class CommsSettingPage : public ElaWidget
{
	Q_OBJECT
public:
	explicit CommsSettingPage(QWidget* parent = nullptr);
	~CommsSettingPage();

	QWidget* getSettingsWidget();

private:
	SerialSettings _set;
	QWidget* _settingsWidget;


Q_SIGNALS:
	//Q_SIGNAL void confirm(SerialSettings set);
	Q_SIGNAL void confirm();
};

#endif