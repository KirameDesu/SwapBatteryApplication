#ifndef T_BASEPAGE_H
#define T_BASEPAGE_H

#include <ElaScrollPage.h>

class QVBoxLayout;
class BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BasePage(QWidget* parent = nullptr);
    ~BasePage();

protected:
    void createCustomWidget(QString desText);
};

#endif // T_BASEPAGE_H
