#include "BasePage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToolButton.h"

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

void BasePage::createCustomWidget(QString desText)
{
    // 顶部元素
    QWidget* customWidget = new QWidget(this);
    ElaText* subTitleText = new ElaText(this);
    subTitleText->setText("https://github.com/Liniyous/ElaWidgetTools");
    subTitleText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    subTitleText->setTextPixelSize(11);

    ElaToolButton* documentationButton = new ElaToolButton(this);
    documentationButton->setFixedHeight(35);
    documentationButton->setIsTransparent(false);
    documentationButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //_toolButton->setPopupMode(QToolButton::MenuButtonPopup);
    documentationButton->setText("Documentation");
    documentationButton->setElaIcon(ElaIconType::FileDoc);
    ElaMenu* documentationMenu = new ElaMenu(this);
    documentationMenu->addElaIconAction(ElaIconType::CardsBlank, "CardsBlank");
    documentationMenu->addElaIconAction(ElaIconType::EarthAmericas, "EarthAmericas");
    documentationButton->setMenu(documentationMenu);

    ElaToolButton* sourceButton = new ElaToolButton(this);
    sourceButton->setFixedHeight(35);
    sourceButton->setIsTransparent(false);
    sourceButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    sourceButton->setText("Source");
    sourceButton->setElaIcon(ElaIconType::NfcSymbol);
    ElaMenu* sourceMenu = new ElaMenu(this);
    sourceMenu->addElaIconAction(ElaIconType::FireBurner, "FireBurner");
    sourceMenu->addElaIconAction(ElaIconType::Galaxy, "Galaxy~~~~");
    sourceButton->setMenu(sourceMenu);

    ElaToolButton* themeButton = new ElaToolButton(this);
    themeButton->setFixedSize(35, 35);
    themeButton->setIsTransparent(false);
    themeButton->setElaIcon(ElaIconType::MoonStars);
    connect(themeButton, &ElaToolButton::clicked, this, [=]() {
        eTheme->setThemeMode(eTheme->getThemeMode() == ElaThemeType::Light ? ElaThemeType::Dark : ElaThemeType::Light);
        });

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(documentationButton);
    buttonLayout->addSpacing(5);
    buttonLayout->addWidget(sourceButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(themeButton);
    buttonLayout->addSpacing(15);

    ElaText* descText = new ElaText(this);
    descText->setText(desText);
    descText->setTextPixelSize(13);

    QVBoxLayout* topLayout = new QVBoxLayout(customWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(subTitleText);
    topLayout->addSpacing(5);
    topLayout->addLayout(buttonLayout);
    topLayout->addSpacing(5);
    topLayout->addWidget(descText);
    setCustomWidget(customWidget);
}

void BasePage::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event); // 确保调用父类的 showEvent
    //if (!_timer->isActive())
    //    _timer->start();
}

void BasePage::hideEvent(QHideEvent* event)
{
    QWidget::hideEvent(event);
    //if (_timer->isActive())
    //    _timer->stop();
}

void BasePage::writeData()
{
    /// 统计有哪些数据需要写入(?)

    //if (!_writeSendMessage.isEmpty())
    //    emit BMSCmdManager::sendMessage(_writeSendMessage);
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
