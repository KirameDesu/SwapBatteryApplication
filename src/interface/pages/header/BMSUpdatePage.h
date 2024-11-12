#ifndef BMS_UPDATE_PAGE_H
#define BMS_UPDATE_PAGE_H

#include "BasePage.h"

#include "ElaProgressBar.h"
#include "ElaText.h"

class BMSUpdatePage : public BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BMSUpdatePage(QWidget* parent = nullptr);
    ~BMSUpdatePage();

    void setIAPVer(const QString& ver);
    void setFilePath(const QString& path);
    void setPercentage(int p);
protected:
    //virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    //ElaMenu* _homeMenu{ nullptr };
    QString _IAPVer = "";
    ElaText* _IAPVerText{ nullptr };
    QString _filePath = "";
    ElaText* _filePathText{ nullptr };
    int _percentage;
    ElaProgressBar* _updateProgressBar{ nullptr };
};
#endif // !BMS_UPDATE_PAGE_H
