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
#if 1
    // 设置指令管理器指针
    void setCmdManager(BMSCmdManager* m);

    // 设置需要定时读取的寄存器列表
    //void setTimedMessageSending(const QList<REGISTERS_GROUP*>& regGroup);

    // 是否定时读取全部寄存器
    void setTimedReadAllRegister(bool);

    // 获取数据组名称列表
    QSet<QString> getAllDataGourpName();

protected:
    void createCustomWidget(QString desText);
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

    void writeData();

    void readDataTiming();

    // 页面数据寄存器组列表
    //QList<REGISTERS_GROUP*> _registerList;

    // 页面所有数据组名字
    QSet<QString> _DataGroupNameList;

private:
    BMSCmdManager* _cmdManager{ nullptr };

    QTimer* _timer{ nullptr };

    bool _timedRead = false;
    // 定时发送数组
    //QList<REGISTERS_GROUP*> _timedReadRegGroup;

//signals:
//    // 发送报文信号
//    void TimeToSendData(const QByteArray);

    // 定时发送报文
    //Q_SLOT void readDataTiming();
    //// 发送写入报文
    //Q_SLOT void writeData();
#endif
};

#endif // BASEPAGE_H
