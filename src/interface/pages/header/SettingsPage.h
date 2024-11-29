#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "BasePage.h"

#include "CellSettingFrame.h"

#include "ParameterSettings.h"
#include "RegisterData.h"

class SettingsPage : public BasePage
{
	Q_OBJECT
public:
	explicit SettingsPage(QWidget* parent = nullptr);
	explicit SettingsPage(QWidget* parent, BaseModel* model);
	~SettingsPage();

	void setSettings(SETTINGS_CLASS settings);

	void setModel(BaseModel* m) override;

protected:
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;

private:
	static const int MAX_COLUMN = 3;
	static const int MAX_ROW = 5;

	QGridLayout* _mainLayout{ nullptr };
	 
	Q_SLOT void updatePageData() override;
	
	// 页面设置组列表
	QList<CellSettingFrame*> _settingList;

	void _initWidget();

};

#endif // !VOLT_SETTINGS_PAGE_H