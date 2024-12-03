#include "BatteryOverviewModel.h"

BatteryOverviewModel::BatteryOverviewModel(BaseModel* parent)
{
	initializeSettings(BatteryOverview::getAllSettings());
}

BatteryOverviewModel::~BatteryOverviewModel()
{
}

void BatteryOverviewModel::parseFromRegAddr(int addrStart, const QByteArray& rawData)
{
    int AFEListIndexStart = 0;
    int SOCListIndexStart = BatteryOverview::getCellSize(0);

	// AFE数据
	if (BatteryOverview::isAddrInCellAddr(0, addrStart))
	{
        bool func = false;
        for (int i = 0; i + 1 < rawData.size() && i / 2 < settingsList.size(); i += 2) {
            // 获取 settingsList 中的元素
            int index = i / 2;
            QPair<QString, ModelData>& setting = settingsList[AFEListIndexStart + index];

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
            emit AFEDataChanged();
	}
	// SOC数据
	else if (BatteryOverview::isAddrInCellAddr(1, addrStart))
	{
        bool func = false;
        for (int i = 0; i + 1 < rawData.size() && i / 2 < settingsList.size(); i += 2) {
            // 获取 settingsList 中的元素
            int index = i / 2;
            QPair<QString, ModelData>& setting = settingsList[SOCListIndexStart + index];

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
            emit SOCDataChanged();
	}
}

void BatteryOverviewModel::emitDataChanged()
{
	// 此类不使用基类的数据改变信号
	return;
}
