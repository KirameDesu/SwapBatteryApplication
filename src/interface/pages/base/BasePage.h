#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QSet>
#include <QObject>
#include <QTimer>

#include "ElaScrollPage.h"

#include "RegisterData.h"
#include "BMSCmdManager.h"

class BMSCmdManager;
class BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BasePage(QWidget* parent = nullptr);
    ~BasePage();

    // 设置指令管理器指针
    void setCmdManager(BMSCmdManager* m);

    // 设置定时器状态
    static void setTimerStatus(bool status);

    // 获取数据组名称列表
    QSet<QString> getAllDataGourpName();

protected:
    void createCustomWidget(QString desText);
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

    void writeData();

    void readDataTiming();

    // 页面所有数据组名字
    QSet<QString> _DataGroupNameList;

    // 所有子类共用一个定时器
    static QTimer* _timer;

private:
    BMSCmdManager* _cmdManager{ nullptr };



    //bool _timedRead = false;
    // 定时发送数组
    //QList<REGISTERS_GROUP*> _timedReadRegGroup;
};

#endif // BASEPAGE_H
