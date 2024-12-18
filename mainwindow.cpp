﻿#include "MainWindow.h"

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
#include "ElaMessageBar.h"

#include "Communication.h"
#include "ParameterSettings.h"


MainWindow::MainWindow(ElaWindow* parent)
    : ElaWindow(parent)
    //, ui(new Ui::mainwindowClass())
{
#if 0
    //ui->setupUi(this);
#endif
    TimerManager::instance().start();  // 启动计时器

    cmdManager = new BMSCmdManager();

    setProperty("ElaBaseClassName", "ElaWindow");

    // 初始化窗口
    initWindow();
    // 初始化额外控件
    initEdgeLayout();
    // 初始化内容页面
    initContent();

    LoggerManager::instance().appendLogList("初始化成功~");
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::initWindow() {
    resize(1020, 680); // 默认宽高

    setUserInfoCardVisible(false);

    setWindowIcon(QIcon(":/src/image/logo.ico"));
    setWindowTitle("BMS Tools V0.0.1");
}

void MainWindow::initEdgeLayout() {
#if 0
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
#endif

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
    tbStartComms->setObjectName("startConnect");
    connect(tbStartComms, &ElaToolButton::clicked, this, &MainWindow::startConnect);
    toolBar->addWidget(tbStartComms);
#if defined(TEST_MODE)
    // 工具栏--串口选择
    ElaComboBox* COMComboBox = new ElaComboBox(this);
    COMComboBox->addItem("COM1");
    toolBar->addWidget(COMComboBox);
    ElaComboBox* baudComboBox = new ElaComboBox(this);
    baudComboBox->addItem("115200");
    toolBar->addWidget(baudComboBox);
#endif
    // 工具栏--监控设置
    ElaToolButton* tbCommsSetting = new ElaToolButton(this);
    tbCommsSetting->setElaIcon(ElaIconType::Gears);
    _commsSettingPage = new CommsSettingPage(cmdManager->getConnect()); // 初始化设置页面
    _commsSettingPage->hide();
    connect(tbCommsSetting, &ElaToolButton::clicked, this, [=]() {
        // 刷新对应协议widget
        cmdManager->getConnect()->settingWidget->applyWidget(_commsSettingPage->getSettingsWidget());
        _commsSettingPage->show();
    });
    //connect(_commsSettingPage, &CommsSettingPage::confirm, cmdManager->getConnect()->settingAction, &BaseCommsSetting::apply);
    connect(_commsSettingPage, &CommsSettingPage::confirm, this, [=] {
        try {
            // 应用设置
            cmdManager->getConnect()->applySettings();
            //LoggerManager::instance().appendLogList(cmdManager->getConnect()->settingWidget->getSettingsString());
        } catch (const std::runtime_error& e) {
            LoggerManager::instance().appendLogList(e.what());
        }
        _commsSettingPage->hide();
    });
    connect(_commsSettingPage, &CommsSettingPage::cancel, _commsSettingPage, &QWidget::hide);
    toolBar->addWidget(tbCommsSetting);
    toolBar->addSeparator();
    //ElaToolButton* tbTest = new ElaToolButton(this);
    //tbTest->setElaIcon(ElaIconType::Brush);
    //connect(tbTest, &QPushButton::clicked, this, [=] {
    //    cmdManager->standardModbusTest();
    //});
    //toolBar->addWidget(tbTest);
    //ElaToolButton* tbTest2 = new ElaToolButton(this);
    //tbTest2->setElaIcon(ElaIconType::Clouds);
    //connect(tbTest2, &QPushButton::clicked, this, [=] {
    //    cmdManager->customModbusTest();
    //    });
    //toolBar->addWidget(tbTest2);
    //ElaToolButton* tbClock = new ElaToolButton(this);
    //tbClock->setElaIcon(ElaIconType::Clock);
    //connect(tbClock, &QPushButton::clicked, this, [=] {
    //    LoggerManager::instance().appendLogList(QString::number((uint32_t)static_cast<quint32>(TimerManager::instance().elapsed())));
    //});
    //toolBar->addWidget(tbClock);
    //toolBar->addSeparator();
    // 开启与关闭页面定时器
    ElaToggleSwitch* timerSwitch = new ElaToggleSwitch();
    connect(timerSwitch, &ElaToggleSwitch::toggled, this, [=](bool status) {
        BasePage::setTimerStatus(status);
    });
    toolBar->addWidget(timerSwitch);
    this->addToolBar(Qt::TopToolBarArea, toolBar);


    // 日志停靠窗口
    logDockWidget = new ElaDockWidget("日志信息", this);
    logDockWidget->setWidget(new Logger(this));
    this->addDockWidget(Qt::RightDockWidgetArea, logDockWidget);
    resizeDocks({ logDockWidget }, { 200 }, Qt::Horizontal);
    logDockWidget->hide();
}

void MainWindow::initContent() {    
    _homePage = new MonitorPage(this);
    _homePage->setCmdManager(cmdManager);
    addPageNode("监控", _homePage, ElaIconType::House);

    _recordPage = new RecordPage(this);
    connect(_recordPage, &RecordPage::fetchOneRecord, _homePage, &MonitorPage::readDataTiming);
    addPageNode("监控记录", _recordPage, ElaIconType::RecordVinyl);

    QString protect_settings;
    addExpanderNode("电池保护设置", protect_settings, ElaIconType::Calculator);
    _voltSettingsPage = new SettingsPage(this, ModelManager::getVoltProtectModel());
    _voltSettingsPage->setSettings(VoltSettings::getAllSettings());
    _voltSettingsPage->setCmdManager(cmdManager);
    addPageNode("电压设置", _voltSettingsPage, protect_settings, ElaIconType::List);
    _currSettingsPage = new SettingsPage(this, ModelManager::getCurrProtectModel());
    _currSettingsPage->setSettings(CurrentSettings::getAllSettings());
    _currSettingsPage->setCmdManager(cmdManager);
    addPageNode("电流设置", _currSettingsPage, protect_settings, ElaIconType::List);
    _tempSettingsPage = new SettingsPage(this, ModelManager::getTempSettingsModel());
    _tempSettingsPage->setSettings(TemperatureSettings::getAllSettings());
    _tempSettingsPage->setCmdManager(cmdManager);
    addPageNode("温度设置", _tempSettingsPage, protect_settings, ElaIconType::List);
    _lowSOCSettingsPage = new SettingsPage(this, ModelManager::getLowSOCSettingsModel());
    _lowSOCSettingsPage->setSettings(LowSOCSettings::getAllSettings());
    _lowSOCSettingsPage->setCmdManager(cmdManager);
    addPageNode("低电量设置", _lowSOCSettingsPage, protect_settings, ElaIconType::List);

    QString parameter_settings;
    addExpanderNode("电池参数设置", parameter_settings, ElaIconType::Viruses);
    // 子项--系统参数设置
    _BattSettingsPage = new SettingsPage(this, ModelManager::getBattSettingsModel());
    _BattSettingsPage->setSettings(BatterySettings::getAllSettings());
    _BattSettingsPage->setCmdManager(cmdManager);
    addPageNode("系统参数设置", _BattSettingsPage, parameter_settings, ElaIconType::List);
    // 子项--功能参数设置
    _FuncSettingsPage = new SettingsPage(this, ModelManager::getFunctionSettingsModel());
    _FuncSettingsPage->setSettings(FunctionSettings::getAllSettings());
    _FuncSettingsPage->setCmdManager(cmdManager);
    addPageNode("功能参数设置", _FuncSettingsPage, parameter_settings, ElaIconType::List);
    // 子项--逆变器设置
    _InverterSettingsPage = new SettingsPage(this, ModelManager::getInverterSettingsModel());
    _InverterSettingsPage->setSettings(InverterSettings::getAllSettings());
    _InverterSettingsPage->setCmdManager(cmdManager);
    addPageNode("逆变器设置", _InverterSettingsPage, parameter_settings, ElaIconType::List);
    // 子项--生产参数设置
    _productSettingPage = new ProductSettingPage(this);
    addPageNode("生产参数设置", _productSettingPage, parameter_settings, ElaIconType::List);

    _bmsCalibratePage = new BMSCalibratePage(this);
    addPageNode("BMS校准", _bmsCalibratePage, ElaIconType::GripDots);

    _bmsUpdatePage = new BMSUpdatePage(this);
    connect(cmdManager, &BMSCmdManager::upgradeProcess, _bmsUpdatePage, &BMSUpdatePage::setPercentage);
    _bmsUpdatePage->setCmdManager(cmdManager);
    _bmsUpdatePage->setIAPVer("v1.0.0");
    //_bmsUpdatePage->setPercentage(0);
    addPageNode("BMS固件升级", _bmsUpdatePage, ElaIconType::Upload);

    QString _settingKey{ "" };
    _systemSettingPage = new SystemSettingPage(this);
    connect(_systemSettingPage, &SystemSettingPage::openLogWidget, this, &MainWindow::showLogWidget);
    addFooterNode("软件设置", _systemSettingPage, _settingKey, 0, ElaIconType::GearComplex);
}

void MainWindow::startConnect()
{
    if (cmdManager->getConnect()->isOpen()) {
        LoggerManager::instance().appendLogList("串口已经打开了哦~");
    }
    if (cmdManager->getConnect()->open()) {
        // 开启线程
        cmdManager->startThread();

        ElaMessageBar::success(ElaMessageBarType::BottomRight, cmdManager->getConnect()->getCommTypeString(), "Connect Success!", 2000);
        ElaToolBar* toolBar = this->findChild<ElaToolBar*>();
        ElaToolButton* btn = toolBar->findChild<ElaToolButton*>("startConnect");
        // 断开旧的连接
        disconnect(btn, &ElaToolButton::clicked, this, &MainWindow::startConnect);
        // 连接新的槽
        connect(btn, &ElaToolButton::clicked, this, &MainWindow::endConnect);
        btn->setElaIcon(ElaIconType::Pause);
    } else {
        QString error = cmdManager->getConnect()->errorString();
        LoggerManager::instance().appendLogList(error);
        ElaMessageBar::error(ElaMessageBarType::BottomRight, cmdManager->getConnect()->getCommTypeString(), error, 2000);
    }
}

void MainWindow::endConnect()
{
    if (!cmdManager->getConnect()->isOpen()) {
        LoggerManager::instance().appendLogList("串口已经关闭了哦~");
    }

    if (cmdManager->getConnect()->close()) {
        // 退出线程
        cmdManager->waitThreadEnd();

        ElaMessageBar::information(ElaMessageBarType::BottomRight, cmdManager->getConnect()->getCommTypeString(), "Close Success!", 2000);
        ElaToolBar* toolBar = this->findChild<ElaToolBar*>();
        ElaToolButton* btn = toolBar->findChild<ElaToolButton*>("startConnect");
        // 断开旧的连接
        disconnect(btn, &ElaToolButton::clicked, this, &MainWindow::endConnect);
        // 连接新的槽
        connect(btn, &ElaToolButton::clicked, this, &MainWindow::startConnect);
        btn->setElaIcon(ElaIconType::CaretRight);
    }
    else {
        QString error = cmdManager->getConnect()->errorString();
        LoggerManager::instance().appendLogList(error);
        ElaMessageBar::error(ElaMessageBarType::BottomRight, cmdManager->getConnect()->getCommTypeString(), error, 2000);
    }
}

void MainWindow::showLogWidget()
{
    logDockWidget->show();
}
