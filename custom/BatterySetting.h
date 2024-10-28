#ifndef BATTERY_SETTING_H
#define BATTERY_SETTING_H

#include "BasePage.h"
class ElaRadioButton;
class ElaToggleSwitch;
class ElaComboBox;
class BatterySetting : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BatterySetting(QWidget* parent = nullptr);
    ~BatterySetting();

private:
    ElaComboBox* _themeComboBox{ nullptr };
    ElaToggleSwitch* _micaSwitchButton{ nullptr };
    ElaToggleSwitch* _logSwitchButton{ nullptr };
    ElaRadioButton* _minimumButton{ nullptr };
    ElaRadioButton* _compactButton{ nullptr };
    ElaRadioButton* _maximumButton{ nullptr };
    ElaRadioButton* _autoButton{ nullptr };
};

#endif // BATTERY_SETTING_H
