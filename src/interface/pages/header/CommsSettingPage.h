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
	explicit CommsSettingPage(std::shared_ptr<AbstractCommunication> c, QWidget* parent = nullptr);
	~CommsSettingPage();

	QWidget* getSettingsWidget();

private:
	std::shared_ptr<AbstractCommunication> _c;
	QWidget* _settingsWidget;


signals:
	void confirm();
	void cancel();
};

#endif