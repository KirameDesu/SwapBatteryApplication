#ifndef PROTECT_SETTING_PAGE
#define PROTECT_SETTING_PAGE

#include "BasePage.h"

#include <QVector>

class ProtectSettingPage : public BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ProtectSettingPage(QWidget* parent = nullptr);
    ~ProtectSettingPage();

private:
    QVector<BaseSetting*> _allSettings;
};

#endif // !PROTECT_SETTING_PAGE
