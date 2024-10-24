#include "mainwindow.h"

#include "ElaNavigationBar.h"

mainwindow::mainwindow(ElaWindow* parent)
    : ElaWindow(parent)
    , ui(new Ui::mainwindowClass())
{
    ui->setupUi(this);

    setProperty("ElaBaseClassName", "ElaWindow");
    resize(1020, 680); // Ĭ�Ͽ��

    this->setIsNavigationBarEnable(false);

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    centralWidget->installEventFilter(this);
}

mainwindow::~mainwindow()
{
    delete ui;
}
