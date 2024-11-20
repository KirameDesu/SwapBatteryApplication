#include "RDManager.h"

RDManager::RDManager()
{
}

RDManager::~RDManager()
{
    //qDeleteAll(_registerList);  // 删除所有的RegisterData对象
}

void RDManager::addRegisterData(const RegisterData& regData)
{
    //// 创建新的寄存器数据对象，并添加到列表
    //RegisterData* newRegData = new RegisterData(regData);
    //_registerList.append(newRegData);
}

//void RDManager::addRegDataFromPage(const SettingsPage* page)
//{
//    if (page)
//    {
//        for (auto c : *(page->getRegList()))
//        {
//            for (auto d : c->second)
//                _registerList.insert(c->first, d);
//        }
//    }
//}

void RDManager::removeRegisterData(int registerStart)
{
    // 遍历寄存器列表，找到指定寄存器并删除
    //for (int i = 0; i < _registerList.size(); ++i) {
    //    if (_registerList[i]->getRegisterStart() == registerStart) {
    //        delete _registerList.takeAt(i);
    //        break;
    //    }
    //}
}

RegisterData* RDManager::getRegisterData(int registerStart) const
{
    // 查找并返回对应寄存器数据
    //for (RegisterData* regData : _registerList) {
    //    if (regData->getRegisterStart() == registerStart) {
    //        return regData;
    //    }
    //}
    return nullptr;  // 没有找到
}

void RDManager::updateRegisterData(int registerStart, const QVariant& newVal)
{
    //RegisterData* regData = getRegisterData(registerStart);
    //if (regData != nullptr) {
    //    regData->setValue(newVal);  // 更新寄存器数据的值
    //}
}

bool RDManager::addRegisterGroup(const REGISTERS_GROUP& gp)
{
    if (!gp.first.isEmpty() && !gp.second.isEmpty()) {
        _registerList.insert(gp.first, gp.second);
        return true;
    }

    return false;
}

QMap<QString, QSet<RegisterData*>> RDManager::getAllRegisterData() const
{
    return _registerList;
}

QPair<qint16, qint16> RDManager::getRegGroupAddrAndLen(QString gourpName)
{
    QPair<qint16, qint16> ret;

    QSet<RegisterData*> regSet = _registerList.value(gourpName);
    ret.first = regSet.values().at(0)->getRegisterGroupStart();
    // 获取寄存器组所有的寄存器的大小 
    int len = 0;
    for (auto c : regSet.values())
        len += c->getRegisterSize();
    ret.second = len;
    return ret;
}

int RDManager::getRegGroupAddr(QString gourpName)
{
    QSet<RegisterData*> regSet = _registerList.value(gourpName);

    return regSet.values().at(0)->getRegisterGroupStart();
}

QByteArray RDManager::getDisplayDataArr(QString gourpName) {
    QByteArray a;

    QSet<RegisterData*> regSet = _registerList.value(gourpName);

    // 对于每一个寄存器
    for (auto c : regSet.values()) {
        int regSize = c->getRegisterSize();
        QByteArray fillArr(regSize, 0);
        QVariant variant = c->getDisplayValue();
        if (!variant.isNull()) {
            // 返回值为整型
            if (variant.type() == QVariant::Int) {
                int val = variant.toInt();
                // 按字节拆分填充值
                for (int i = 0; i < regSize; ++i) {
                    fillArr[regSize - 1 - i] = val & 0xFF;  // 获取低8位
                    val >>= 8;  // 将值右移8位，处理下一个字节
                }
            }
            // 返回值为布尔
            else if (variant.type() == QVariant::Bool) {
                int val = variant.toBool();
                //// 按字节拆分填充值
                //for (int i = 0; i < regSize; ++i) {
                //    fillArr[regSize - 1 - i] = val & 0xFF;  // 获取低8位
                //    val >>= 8;  // 将值右移8位，处理下一个字节
                //}
            }
            a.append(fillArr);
        }
    }
    return a;
}
