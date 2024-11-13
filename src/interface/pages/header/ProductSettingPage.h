#ifndef PRODUCT_SETTING_PAGE
#define PRODUCT_SETTING_PAGE

#include "BasePage.h"

#include <QVariant>

class ProductSettingPage : public BasePage
{
	Q_OBJECT
public:
	explicit ProductSettingPage(QWidget* parent = nullptr);
	~ProductSettingPage();

private:
	QList<QVariant*> _dataList;
	QVBoxLayout* _mainLayout{ nullptr };
};

#endif // !PRODUCT_SETTING_PAGE
