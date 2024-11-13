#ifndef SYSTEM_SETTING_H
#define SYSTEM_SETTING_H

#include "BasePage.h"
class ElaRadioButton;
class ElaToggleSwitch;
class ElaComboBox;
class SystemSettingPage : public BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SystemSettingPage(QWidget* parent = nullptr);
    ~SystemSettingPage();

private:
    ElaComboBox* _themeComboBox{ nullptr };
    ElaToggleSwitch* _micaSwitchButton{ nullptr };
    ElaToggleSwitch* _logSwitchButton{ nullptr };
    ElaRadioButton* _minimumButton{ nullptr };
    ElaRadioButton* _compactButton{ nullptr };
    ElaRadioButton* _maximumButton{ nullptr };
    ElaRadioButton* _autoButton{ nullptr };
};

#endif // SYSTEM_SETTING_H
