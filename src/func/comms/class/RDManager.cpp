#include "RDManager.h"

RDManager::RDManager()
{
}

RDManager::~RDManager()
{
    qDeleteAll(_registerList);  // 删除所有的RegisterData对象
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

bool RDManager::addRegisterGroup(REGISTERS_GROUP gp)
{
    if (!gp.first.isEmpty() && !gp.second.isEmpty()) {
        for (auto c : gp.second)
            _registerList.insert(gp.first, c);
        return true;
    }

    return false;
}

QMap<QString, RegisterData*> RDManager::getAllRegisterData() const
{
    return _registerList;
}

QPair<qint16, qint16> RDManager::getRegGroupAddrAndLen(QString gourpName)
{
    QPair<qint16, qint16> ret;
    RegisterData* reg = _registerList.value(gourpName);
    ret.first = reg->getRegisterGroupStart();
    ret.second = static_cast<qint16>(reg->getRegisterSize());
    return ret;
}
