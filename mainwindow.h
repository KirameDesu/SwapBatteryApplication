#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include "ElaWindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindowClass; };
QT_END_NAMESPACE

class mainwindow : public ElaWindow
{
    Q_OBJECT

public:
    mainwindow(ElaWindow* parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindowClass *ui;
};
