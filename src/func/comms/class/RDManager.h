// 基于单例模式实现，类负责接收数据名称，输出寄存器地址

#ifndef RDMANAGER_H
#define RDMANAGER_H

#include <QHash>
#include <QString>
#include <QVariant>

#include "RegisterData.h"
#include "SettingsPage.h"

class RDManager
{
public:
    static RDManager& instance() {
        static RDManager _instance;
        return _instance;
    }

    // 添加寄存器数据
    void addRegisterData(const RegisterData& regData);
    //void addRegDataFromPage(const SettingsPage* page);
    bool addRegisterGroup(REGISTERS_GROUP gp);

    // 删除寄存器数据
    void removeRegisterData(int registerStart);

    // 获取寄存器数据
    RegisterData* getRegisterData(int registerStart) const;

    // 更新寄存器数据
    void updateRegisterData(int registerStart, const QVariant& newVal);

    // 获取所有寄存器数据
    QMap<QString, RegisterData*> getAllRegisterData() const;

    QPair<qint16, qint16> getRegGroupAddrAndLen(QString gourpName);

private:
    RDManager();
    ~RDManager();
    // 禁止拷贝构造和拷贝赋值
    RDManager(const RDManager&) = delete;
    RDManager& operator=(const RDManager&) = delete;
    /*
    EXP:
    GroupName(QString)              RegisterData*
                       ------------>>  警告电压
                     -------------->>  保护1电压
        单体过压设置 ---------------->>  保护1延时
                     -------------->>  保护1恢复电压
                       ...
    */
    QMap<QString, RegisterData*> _registerList;  // 存储寄存器数据的列表
};

#endif // RDMANAGER_H
