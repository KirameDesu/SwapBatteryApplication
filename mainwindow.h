#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include "ElaWindow.h"
#include "ElaWidget.h"

#include "home.h"
#include "BatterySetting.h"

//QT_BEGIN_NAMESPACE
//namespace Ui { class mainwindowClass; };
//QT_END_NAMESPACE

class T_Home;
class BatterySetting;
class mainwindow : public ElaWindow
{
    Q_OBJECT

public:
    mainwindow(ElaWindow* parent = nullptr);
    ~mainwindow();

    void initWindow();
    void initEdgeLayout();
    void initContent();
private:
    //Ui::mainwindowClass *ui;

    T_Home* _homePage{ nullptr };
    BatterySetting* _batterySettingPage{ nullptr };
};
