// RegisterData.h 定义寄存器数据的结构
#ifndef REGISTER_DATA_H
#define REGISTER_DATA_H

#include <QVariant>
#include <QWidget>

#include "BaseSetting.h"


class RegisterData
{
public:
    RegisterData(const qint16 regStart, const Setting& set);
    ~RegisterData();

    // 设置显示项
    void setDispalyWidget(QWidget* w) {
        if (w)
        {
            _displayWidget = w;
        }
    }

    qint16 getRegisterGroupStart() {
        return _registerGroupStart;
    }

    int getRegisterSize() {
        return _size;
    }

private:
    // 寄存器标题
    QString _title;
    // 为模拟量还是信号量
    RegisterDataType _type;
    // 数据值
    QVariant _val;
    // 寄存器组的起始位，注意不是数据的地址
    qint16 _registerGroupStart;
    // 所占寄存器大小, 单位字节
    int _size = 2;
    // 读写权限
    PermissionType _permission = ReadAndWrite;
    // 所处显示控件
    QWidget* _displayWidget{ nullptr };
};

using REGISTERS_GROUP = QPair<QString, QList<RegisterData*>>;

#endif // !REGISTER_DATA_H
