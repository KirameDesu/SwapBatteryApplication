#include "VoltageProtectModel.h"

VoltageProtectModel::VoltageProtectModel(BaseModel* parent)
{
	initializeSettings(VoltSettings::getAllSettings());
}

VoltageProtectModel::~VoltageProtectModel()
{
}

void VoltageProtectModel::emitDataChanged()
{
    emit VoltageProtectModel::dataChanged();
}

//void VoltageProtectModel::parse(const QByteArray& rawData)
//{
//	/// 将报文数据解析到对应值上
//    bool func = false;
//    for (int i = 0; i + 1 < rawData.size() && i / 2 < settingsList.size(); i += 2) {
//        // 获取 settingsList 中的元素
//        int index = i / 2;
//        QPair<QString, ModelData>& setting = settingsList[index];
//
//        // 提取两个字节并合成一个 16 位值
//        uint16_t val = (static_cast<uint16_t>(rawData.at(i)) << 8) | static_cast<uint8_t>(rawData.at(i + 1));
//
//        // 如果值改变，则更新并发送信号
//        if (setting.second.val != val) {
//            func = true;
//            setting.second.val = val;
//        }
//    }
//    if (func)
//        emit BaseModel::dataChanged();
//}
