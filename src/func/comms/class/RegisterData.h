// RegisterData.h 定义寄存器数据的结构
#ifndef REGISTER_DATA_H
#define REGISTER_DATA_H

#include <QVariant>
#include <QWidget>
#include <QLineEdit>

#include "BaseSetting.h"


class RegisterData
{
public:
    RegisterData(const qint16 regStart, const Setting& set);
    ~RegisterData();

    // 设置显示项
    void setDispalyWidget(QWidget* w) {
        if (w) {
            _valSetWidget = w;
        }
    }

    /*
    * FuncName: getDisplayValue
    * Describe: 获取寄存器对应控件所显示的值
    * return: 
    *   当为Semaphore时返回整型；
    *   当为Switch时返回布尔值；
    */
    QVariant getDisplayValue() {
        if (!_valSetWidget)
            return QVariant();

        QVariant ret;
        QLineEdit* ed;
        switch (_type) {
        case Semaphore:
            ed = qobject_cast<QComboBox*>(_valSetWidget)->lineEdit();
            if (ed) {
                ret = ed->text().toInt();
            }
            break;
        case Switch:
            ret = qobject_cast<ElaToggleSwitch*>(_valSetWidget)->getIsToggled();
        }

        return ret;
    }

    qint16 getRegisterGroupStart() {
        return _registerGroupStart;
    }

    int getRegisterSize() {
        return _size;
    }

    RegisterDataType getRegisterType() {
        return _type;
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
    QWidget* _valSetWidget{ nullptr };
};

using REGISTERS_GROUP = QPair<QString, QSet<RegisterData*>>;

#endif // !REGISTER_DATA_H
