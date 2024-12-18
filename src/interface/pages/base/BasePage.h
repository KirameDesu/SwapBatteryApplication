﻿#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QSet>
#include <QObject>
#include <QTimer>
#include <QPointer>

#include "ElaScrollPage.h"

#include "RegisterData.h"
#include "BMSCmdManager.h"
#include "BaseModel.h"
#include "CellSettingFrame.h"

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
    const QSet<QString>& getAllDataGourpName() const;

    BMSCmdManager* getPageCMDManager();
    virtual void setModel(BaseModel* m);

    // 定时发送报文函数
    void readDataTiming();

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

    void writeData();

    // 页面所有数据组名字 (报文发送也是参考这个集合)
    QSet<QString> _dataGroupNameList;

    // 设置组指针
    void updateUI(QList<CellSettingFrame*>* _settingsGroup);

    // 所有子类共用一个定时器
    static QPointer<QTimer> _timer;

protected:
    BaseModel* _model{ nullptr };

private:
    BMSCmdManager* _cmdManager{ nullptr };



    // 更新页面数据组
    Q_SLOT virtual void updatePageData();
    //bool _timedRead = false;
    // 定时发送数组
    //QList<REGISTERS_GROUP*> _timedReadRegGroup;


};

#endif // BASEPAGE_H
