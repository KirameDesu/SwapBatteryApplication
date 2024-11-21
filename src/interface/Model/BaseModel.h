#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include <QObject>

#include "ParameterSettings.h"

struct ModelData {
    QVariant val = 0;        // 当前值

    bool needSave = false;      // 是否需要设置
};

// 定义 BaseModel 基类
class BaseModel : public QObject
{
    Q_OBJECT
public:
    // 析构函数定义为虚函数
    virtual ~BaseModel() = default;

    // 获取所有的设置项
    const QMap<QString, ModelData>& getSettings() const {
        return settingsList;
    }

    // 解析函数，纯虚函数，需要在派生类中实现
    virtual void parse(const QByteArray& rawData) = 0;

protected:
    QMap<QString, ModelData> settingsList;

    // 初始化设置列表
    void initializeSettings(const SETTINGS_CLASS& settingGroups) {
        for (const auto& gourp : settingGroups) {
            for (Setting set : gourp.setList) {
                ModelData m;
                settingsList.insert(set.title, m);
            }
        }
    }

signals:
    void dataChanged();
};

#endif
