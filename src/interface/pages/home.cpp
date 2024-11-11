﻿#include "home.h"

#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>

#include "ElaAcrylicUrlCard.h"
#include "ElaFlowLayout.h"
#include "ElaImageCard.h"
#include "ElaMenu.h"
#include "ElaMessageBar.h"
#include "ElaNavigationRouter.h"
#include "ElaPopularCard.h"
#include "ElaScrollArea.h"
#include "ElaText.h"
#include "ElaToolTip.h"
#include "CycleProgressBar.h"

#include "SegmentBatteryOverviewWidget.h"
#include "SegmentBatteryFunctionWidget.h"
#include "SegmentBatteryCellVoltWidget.h"


T_Home::T_Home(QWidget* parent)
    : BasePage(parent)
{
    // 预览窗口标题
    setWindowTitle("Home");
    setTitleVisible(false);
    setContentsMargins(2, 2, 0, 0);
    // 标题卡片区域
    ElaText* titleText = new ElaText("电池概况", this);
    titleText->setTextPixelSize(28);

    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(30, 50, 0, 0);
    titleLayout->addWidget(titleText);

    //电池概况部分
    SegmentBatteryOverviewWidget* segmentBattOverView = new SegmentBatteryOverviewWidget(this);
    //segmentBattOverView->setFixedSize(400, 180);
    segmentBattOverView->setTextSize(18);
    //环形进度条
    CycleProgressBar* cycleProgBar = new CycleProgressBar(this);
    cycleProgBar->setFixedSize(200, 200);
    QHBoxLayout* CycleProgBarLayout = new QHBoxLayout(this);
    CycleProgBarLayout->setContentsMargins(30, 30, 30, 30);
    CycleProgBarLayout->setSpacing(40);
    CycleProgBarLayout->addWidget(cycleProgBar);
    CycleProgBarLayout->addWidget(segmentBattOverView);

    ElaScrollArea* cardScrollArea = new ElaScrollArea(this);
    cardScrollArea->setWidgetResizable(true);
    cardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardScrollArea->setIsGrabGesture(true, 0);
    cardScrollArea->setIsOverShoot(Qt::Horizontal, true);
    QWidget* cardScrollAreaWidget = new QWidget(this);
    cardScrollAreaWidget->setStyleSheet("background-color:transparent;");
    cardScrollArea->setWidget(cardScrollAreaWidget);
    QHBoxLayout* urlCardLayout = new QHBoxLayout();
    urlCardLayout->setSpacing(15);
    urlCardLayout->setContentsMargins(30, 0, 0, 6); 
    //urlCardLayout->addWidget(urlCard1);
    //urlCardLayout->addWidget(urlCard2);
    urlCardLayout->addStretch();
    QVBoxLayout* cardScrollAreaWidgetLayout = new QVBoxLayout(cardScrollAreaWidget);
    cardScrollAreaWidgetLayout->setContentsMargins(0, 0, 0, 0);
    cardScrollAreaWidgetLayout->addStretch();
    cardScrollAreaWidgetLayout->addLayout(urlCardLayout);

    //功能开关
    ElaText* funcTitle = new ElaText("电池状态", this);
    funcTitle->setTextPixelSize(28);
    QHBoxLayout* funcTitleLayout = new QHBoxLayout(this);
    funcTitleLayout->setContentsMargins(30, 30, 0, 0);
    funcTitleLayout->addWidget(funcTitle);
    SegmentBatteryFunctionWidget* segmentBatteryFunction = new SegmentBatteryFunctionWidget(this);
    QHBoxLayout* segmentBattFuncLayout = new QHBoxLayout(this);
    segmentBattFuncLayout->addWidget(segmentBatteryFunction);
    segmentBatteryFunction->setContentsMargins(30, 0, 30, 0);
    segmentBatteryFunction->setTextSize(18);

    //单体电压
    ElaText* cellTitle = new ElaText("单体电压", this);
    cellTitle->setTextPixelSize(28);
    QHBoxLayout* cellTitleLayout = new QHBoxLayout(this);
    cellTitleLayout->setContentsMargins(30, 30, 0, 0);
    cellTitleLayout->addWidget(cellTitle);
    SegmentBatteryCellVoltWidget* segmentCellVolt = new SegmentBatteryCellVoltWidget(this);
    segmentCellVolt->setCellDisplayNum(16);
    QHBoxLayout* segmentCellVoltLayout = new QHBoxLayout(this);
    segmentCellVoltLayout->addWidget(segmentCellVolt);
    segmentCellVoltLayout->setContentsMargins(30, 0, 30, 0);
    //segmentBatteryFunction->setTextSize(18);

    // 推荐卡片
    //ElaText* flowText = new ElaText("测试", this);
    //flowText->setTextPixelSize(20);
    //QHBoxLayout* flowTextLayout = new QHBoxLayout();
    //flowTextLayout->setContentsMargins(33, 0, 0, 0);
    //flowTextLayout->addWidget(flowText);
    //// ElaFlowLayout
    //ElaPopularCard* homeCard = new ElaPopularCard(this);
    //connect(homeCard, &ElaPopularCard::popularCardButtonClicked, this, [=]() {
    //    QDesktopServices::openUrl(QUrl("https://github.com/Liniyous/ElaWidgetTools"));
    //    });
    //homeCard->setCardPixmap(QPixmap(":/Resource/Image/Cirno.jpg"));
    //homeCard->setTitle("电压(V)");
    //homeCard->setSubTitle("5.0⭐ 实用程序与工具");
    //homeCard->setInteractiveTips("免费下载");
    //homeCard->setDetailedText("ElaWidgetTools致力于为QWidget用户提供一站式的外观和实用功能解决方案,只需数十MB内存和极少CPU占用以支持高效而美观的界面开发");
    //homeCard->setCardFloatPixmap(QPixmap(":/Resource/Image/IARC/IARC_7+.svg.png"));
    //homeCard->setCardPixmap

    

    //ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    //flowLayout->setContentsMargins(30, 0, 0, 0);
    //flowLayout->setIsAnimation(true);
    //flowLayout->addWidget(homeCard);
    //flowLayout->addWidget(homeCard1);
    //flowLayout->addWidget(homeCard2);
    //flowLayout->addWidget(homeCard3);
    //flowLayout->addWidget(homeCard4);
    //flowLayout->addWidget(homeCard5);

    // 菜单
    _homeMenu = new ElaMenu(this);
    ElaMenu* checkMenu = _homeMenu->addMenu(ElaIconType::Cubes, "查看");
    checkMenu->addAction("查看1");
    checkMenu->addAction("查看2");
    checkMenu->addAction("查看3");
    checkMenu->addAction("查看4");

    ElaMenu* checkMenu1 = _homeMenu->addMenu(ElaIconType::Cubes, "查看");
    checkMenu1->addAction("查看1");
    checkMenu1->addAction("查看2");
    checkMenu1->addAction("查看3");
    checkMenu1->addAction("查看4");

    ElaMenu* checkMenu2 = checkMenu->addMenu(ElaIconType::Cubes, "查看");
    checkMenu2->addAction("查看1");
    checkMenu2->addAction("查看2");
    checkMenu2->addAction("查看3");
    checkMenu2->addAction("查看4");

    // QKeySequence key = QKeySequence(Qt::CTRL | Qt::Key_S);

    _homeMenu->addSeparator();
    _homeMenu->addElaIconAction(ElaIconType::BoxCheck, "排序方式", QKeySequence::Save);
    _homeMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新");
    QAction* action = _homeMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "撤销");
    connect(action, &QAction::triggered, this, [=]() {
        ElaNavigationRouter::getInstance()->navigationRouteBack();
        });

    _homeMenu->addElaIconAction(ElaIconType::Copy, "复制");
    _homeMenu->addElaIconAction(ElaIconType::MagnifyingGlassPlus, "显示设置");

    //centerVLayout->addWidget(backgroundCard);
#if 1
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Home");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addLayout(titleLayout);
    centerVLayout->addSpacing(20);
    centerVLayout->addLayout(CycleProgBarLayout);
    centerVLayout->addSpacing(40); 
    centerVLayout->addLayout(funcTitleLayout);
    centerVLayout->addSpacing(20);
    centerVLayout->addLayout(segmentBattFuncLayout);
    centerVLayout->addSpacing(40);
    centerVLayout->addLayout(cellTitleLayout);
    centerVLayout->addSpacing(20);
    centerVLayout->addLayout(segmentCellVoltLayout);
    centerVLayout->addSpacing(40);
    //centerVLayout->addLayout(flowTextLayout);
    //centerVLayout->addSpacing(10);
    //centerVLayout->addLayout(flowLayout);
    //centerVLayout->addStretch();
#else
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Home");
    QGridLayout* centerVLayout = new QGridLayout(centralWidget);
    centerVLayout->setSpacing(0);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addLayout(titleLayout, 0, 0);
    centerVLayout->addLayout(CycleProgBarLayout, 1, 0);
    centerVLayout->addLayout(funcTitleLayout, 0, 1);
    centerVLayout->addLayout(segmentBattFuncLayout, 1, 1);
    centerVLayout->addLayout(cellTitleLayout, 2, 0);
    centerVLayout->addLayout(segmentCellVoltLayout, 3, 0, 1, 2);
    /*centerVLayout->addLayout(flowTextLayout);
    centerVLayout->addLayout(flowLayout);*/
#endif
    addCentralWidget(centralWidget);

    // 初始化提示
    ElaMessageBar::success(ElaMessageBarType::BottomRight, "Success", "初始化成功!", 2000);
    qDebug() << "初始化成功";
}

T_Home::~T_Home()
{
}

void T_Home::mouseReleaseEvent(QMouseEvent* event)
{
    switch (event->button())
    {
    case Qt::RightButton:
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        _homeMenu->popup(event->globalPosition().toPoint());
#else
        _homeMenu->popup(event->globalPos());
#endif
        break;
    }
    default:
    {
        break;
    }
    }
    ElaScrollPage::mouseReleaseEvent(event);
}
