#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include <QObject>

#include "ParameterSettings.h"

struct ModelData {
    QVariant val = -1;        // 当前值

    bool isUpdated = false;      // 数据是否更新

    // 设置更新标志
    void setUpdated()
    {
        isUpdated = false;
    }
};

// 定义 BaseModel 基类
class BaseModel : public QObject
{
    Q_OBJECT
public:
    // 析构函数定义为虚函数
    virtual ~BaseModel() = default;

    // 获取所有的设置项
    const QList<QPair<QString, ModelData>>& getSettings() const {
        return settingsList;
    }

    // 通过QString查找
    ModelData* findModelDataFromTitle(const QString& key) {
        for (auto& pair : settingsList) {
            if (pair.first == key) {
                return &pair.second;
            }
        }
        throw std::runtime_error("Key not found");
    }

    virtual void emitDataChanged() = 0;

    // 解析函数
    virtual void parse(const QByteArray& rawData) {
        bool func = false;
        for (int i = 0; i + 1 < rawData.size() && i / 2 < settingsList.size(); i += 2) {
            // 获取 settingsList 中的元素
            int index = i / 2;
            QPair<QString, ModelData>& setting = settingsList[index];

            // 提取两个字节并合成一个 16 位值
            uint16_t val = (static_cast<uint16_t>(rawData.at(i)) << 8) | static_cast<uint8_t>(rawData.at(i + 1));

            // 如果值改变，则更新并发送信号
            if (setting.second.val.toUInt() != val) {
                func = true;
                setting.second.val = val;
                setting.second.isUpdated = true;
            }
        }
        if (func)
            // 发送更新界面信号
            emitDataChanged();
    };

protected:
    QList<QPair<QString, ModelData>> settingsList;

    // 初始化设置列表
    void initializeSettings(const SETTINGS_CLASS& settingGroups) {
        for (const auto& gourp : settingGroups) {
            for (Setting set : gourp.setList) {
                ModelData m;
                settingsList.append(QPair<QString, ModelData>(set.title, m));
            }
        }
    }

signals:
    void dataChanged();
};

#endif
