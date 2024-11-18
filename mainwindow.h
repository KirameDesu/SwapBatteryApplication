#pragma once

#include <QtWidgets/QMainWindow>
#include <QElapsedTimer>
//#include "ui_mainwindow.h"

#include "ElaWindow.h"
#include "ElaWidget.h"

#include "BMSCmdManager.h"
#include "RDManager.h"
#include "Logger.h"
#include "TimerManager.h"
#include "LoggerManager.h"

#include "home.h"
#include "SystemSettingPage.h"
#include "CommsSettingPage.h"
#include "BMSUpdatePage.h"
#include "SettingsPage.h"
#include "ProductSettingPage.h"
#include "RecordPage.h"



//QT_BEGIN_NAMESPACE
//namespace Ui { class mainwindowClass; };
//QT_END_NAMESPACE

//前向声明
class T_Home;
class SystemSettingPage;
class CommsSettingPage;

class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    MainWindow(ElaWindow* parent = nullptr);
    ~MainWindow();

    void initWindow();
    void initEdgeLayout();
    void initContent();

    void startConnect();
    void endConnect();
private:
    BMSCmdManager* cmdManager{ nullptr };
    //Ui::mainwindowClass *ui;

    //AbstractCommunication* _communication{ nullptr };

    T_Home* _homePage{ nullptr };
    RecordPage* _recordPage{ nullptr };
    SystemSettingPage* _systemSettingPage{ nullptr };
    CommsSettingPage* _commsSettingPage{ nullptr };
    BMSUpdatePage* _bmsUpdatePage{ nullptr };

    SettingsPage* _voltSettingsPage{ nullptr };
    SettingsPage* _currSettingsPage{ nullptr };
    SettingsPage* _tempSettingsPage{ nullptr };
    SettingsPage* _lowSOCSettingsPage{ nullptr };

    SettingsPage* _BattSettingsPage{ nullptr };
    ProductSettingPage* _productSettingPage{ nullptr };
};
