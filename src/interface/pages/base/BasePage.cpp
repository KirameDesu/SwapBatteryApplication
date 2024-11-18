#include "BasePage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToolButton.h"


BasePage::BasePage(QWidget* parent)
    : ElaScrollPage(parent)
{
    _timer = new QTimer(this);
    _timer->setInterval(1000);
    connect(_timer, &QTimer::timeout, this, &BasePage::readDataTiming);
    //connect(this, &BasePage::TimeToSendData, this, [=](QList<RegisterData*> list) {
    //    // 加入读取报文队列
    //    BMSCmdManager::addSendReadQueueFromDataList(list);
    //});

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

//void BasePage::setTimedMessageSending(const QList<REGISTERS_GROUP*>& regGroup)
//{
//    if (!_timedReadRegGroup)
//        _timedReadRegGroup = new QList<REGISTERS_GROUP*>();
//    _timedReadRegGroup = regGroup;
//}

//void BasePage::setTimedMessageSending(const QByteArray& arr)
//{
//    _timedSendMessage = arr;
//}

void BasePage::setTimedReadAllRegister(bool sw)
{
    _timedRead = sw;
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
    if (!_timer->isActive())
        _timer->start();
}

void BasePage::hideEvent(QHideEvent* event)
{
    QWidget::hideEvent(event);
    if (_timer->isActive())
        _timer->stop();
}

void BasePage::writeData()
{
    /// 统计有哪些数据需要写入(?)

    //if (!_writeSendMessage.isEmpty())
    //    emit BMSCmdManager::sendMessage(_writeSendMessage);
}

void BasePage::readDataTiming()
{
    if (!_timedRead || _DataGroupNameList.isEmpty() || _cmdManager == nullptr)
        return;
    // 定时发送读取数据
    _cmdManager->read(_DataGroupNameList);
}
