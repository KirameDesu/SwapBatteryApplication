#include "BasePage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToolButton.h"
#include "ElaScrollPage.h"

#include "LoggerManager.h"

QTimer* BasePage::_timer = nullptr;

BasePage::BasePage(QWidget* parent)
    : ElaScrollPage(parent)
{
    if (_timer == nullptr) {
        _timer = new QTimer(this);
        _timer->setInterval(3000);
    }

    connect(eTheme, &ElaTheme::themeModeChanged, this, [=]() {
        if (!parent)
        {
            update();
        }
    });
}

BasePage::~BasePage()
{
    // 停止定时器，关闭串口
    if (_timer->isActive()) {
        _timer->stop();
    }
}

void BasePage::setCmdManager(BMSCmdManager* m)
{
    _cmdManager = m;
}

void BasePage::setTimerStatus(bool status)
{
    if (status) {
        _timer->start();
    } else {
        _timer->stop();
    }
}

const QSet<QString>& BasePage::getAllDataGourpName() const
{
    return _dataGroupNameList;
}

BMSCmdManager* BasePage::getPageCMDManager()
{
    return _cmdManager;
}

void BasePage::setModel(BaseModel* m)
{
    _model = m;
}

void BasePage::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event); // 确保调用父类的 showEvent
}

void BasePage::hideEvent(QHideEvent* event)
{
    QWidget::hideEvent(event);
}

void BasePage::writeData()
{
    /// 统计有哪些数据需要写入(?)

}

void BasePage::readDataTiming()
{
    //LoggerManager::log("定时器超时函数" + QString(__FUNCTION__) + "已经触发");
    if (_dataGroupNameList.isEmpty() || _cmdManager == nullptr)
        return;
    // 定时发送读取数据
    _cmdManager->read(_dataGroupNameList);
}

void BasePage::updateUI(QList<CellSettingFrame*>* _settingsGroup)
{
    QList<QPair<QString, ModelData>> settingsList = _model->getSettings();
    for (int i = 0; i < _settingsGroup->size(); ++i) {
        QList<QVariant> list;
        for (int j = 0; j < settingsList.size(); ++j) {
            QVariant var = settingsList.at(j).second.val;
            list.append(var);
        }
        _settingsGroup->at(i)->updateWidgetValue(list);
    }
}

void BasePage::updatePageData()
{
}
