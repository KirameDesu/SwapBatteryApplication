#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "CellSettingFrame.h"

#include "BasePage.h"

#include "ParameterSettings.h"

class SettingsPage : public BasePage
{
	Q_OBJECT
public:
	explicit SettingsPage(QWidget* parent = nullptr);
	~SettingsPage();

	void setSettings(SETTINGS_TYPE settings);
private:
	static const int MAX_COLUMN = 2;
	static const int MAX_ROW = 5;

	QList<CellSettingFrame*> _settingList;
	QGridLayout* _mainLayout{ nullptr };
};

#endif // !VOLT_SETTINGS_PAGE_H