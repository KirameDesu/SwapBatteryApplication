﻿#include "mainwindow.h"

#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "ElaNavigationBar.h"
#include "ElaMenuBar.h"
#include "ElaMenu.h"
#include "ElaDockWidget.h"
#include "ElaToolBar.h"
#include "ElaToolButton.h"

#include "Logger.h"
#include "Communication.h"

mainwindow::mainwindow(ElaWindow* parent)
    : ElaWindow(parent)
    //, ui(new Ui::mainwindowClass())
{
#if 0
    //ui->setupUi(this);
#endif
    setProperty("ElaBaseClassName", "ElaWindow");

    // 初始化窗口
    initWindow();
    // 初始化额外控件
    initEdgeLayout();
    // 初始化内容页面
    initContent();

    mainLogger->log("初始化成功~");
}

mainwindow::~mainwindow()
{
    //delete ui;
}

void mainwindow::initWindow() {
    resize(1020, 680); // 默认宽高

    setUserInfoCardVisible(false);
}

void mainwindow::initEdgeLayout() {
    //菜单栏
    ElaMenuBar* menuBar = new ElaMenuBar(this);
    menuBar->setFixedHeight(30);
    QWidget* customWidget = new QWidget(this);
    QVBoxLayout* customLayout = new QVBoxLayout(customWidget);
    customLayout->setContentsMargins(0, 0, 0, 0);
    customLayout->addWidget(menuBar);
    customLayout->addStretch();
    // this->setMenuBar(menuBar);
    this->setCustomWidget(ElaAppBarType::MiddleArea, customWidget);
    this->setCustomWidgetMaximumWidth(500);

    menuBar->addElaIconAction(ElaIconType::AtomSimple, "动作菜单");
    ElaMenu* iconMenu = menuBar->addMenu(ElaIconType::Aperture, "图标菜单");
    iconMenu->setMenuItemHeight(27);
    iconMenu->addElaIconAction(ElaIconType::BoxCheck, "排序方式", QKeySequence::SelectAll);
    iconMenu->addElaIconAction(ElaIconType::Copy, "复制");
    iconMenu->addElaIconAction(ElaIconType::MagnifyingGlassPlus, "显示设置");
    iconMenu->addSeparator();
    iconMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新");
    iconMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "撤销");
    menuBar->addSeparator();
    ElaMenu* shortCutMenu = new ElaMenu("快捷菜单(&A)", this);
    shortCutMenu->setMenuItemHeight(27);
    shortCutMenu->addElaIconAction(ElaIconType::BoxCheck, "排序方式", QKeySequence::Find);
    shortCutMenu->addElaIconAction(ElaIconType::Copy, "复制");
    shortCutMenu->addElaIconAction(ElaIconType::MagnifyingGlassPlus, "显示设置");
    shortCutMenu->addSeparator();
    shortCutMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新");
    shortCutMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "撤销");
    menuBar->addMenu(shortCutMenu);

    menuBar->addMenu("样例菜单(&B)")->addElaIconAction(ElaIconType::ArrowRotateRight, "样例选项");
    menuBar->addMenu("样例菜单(&C)")->addElaIconAction(ElaIconType::ArrowRotateRight, "样例选项");
    menuBar->addMenu("样例菜单(&E)")->addElaIconAction(ElaIconType::ArrowRotateRight, "样例选项");
    menuBar->addMenu("样例菜单(&F)")->addElaIconAction(ElaIconType::ArrowRotateRight, "样例选项");
    menuBar->addMenu("样例菜单(&G)")->addElaIconAction(ElaIconType::ArrowRotateRight, "样例选项");

    // 工具栏
    ElaToolBar* toolBar = new ElaToolBar("工具栏", this);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    toolBar->setToolBarSpacing(3);
    toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolBar->setIconSize(QSize(25, 25));
    toolBar->setFloatable(true);
    toolBar->setMovable(true);
    // 工具栏--启动监控
    ElaToolButton* tbStartComms = new ElaToolButton(this);
    tbStartComms->setElaIcon(ElaIconType::CaretRight);
    connect(tbStartComms, &ElaToolButton::clicked, this, &mainwindow::startComms);
    // 工具栏--监控设置
    toolBar->addWidget(tbStartComms);
    ElaToolButton* tbCommsSetting = new ElaToolButton(this);
    tbCommsSetting->setElaIcon(ElaIconType::Gears);
    toolBar->addWidget(tbCommsSetting);
    toolBar->addSeparator();
    this->addToolBar(Qt::TopToolBarArea, toolBar);

    // 日志停靠窗口
    ElaDockWidget* logDockWidget = new ElaDockWidget("日志信息", this);
    mainLogger = new Logger(this);
    logDockWidget->setWidget(mainLogger);
    this->addDockWidget(Qt::RightDockWidgetArea, logDockWidget);
    resizeDocks({ logDockWidget }, { 200 }, Qt::Horizontal);
}

void mainwindow::initContent() {
    _homePage = new T_Home(this);
    _batterySettingPage = new BatterySetting(this);
    addPageNode("HOME", _homePage, ElaIconType::House);
    addPageNode("Setting", _batterySettingPage, ElaIconType::GearComplex);
}

void mainwindow::startComms()
{
    auto communication = Communication::createCommunication(CommunicationType::Serial);
    if (communication->isOpen())
    {
        mainLogger->log("串口打开了哦~");
    }
    else
    {
        mainLogger->log("串口没有打开...");
    }
}
