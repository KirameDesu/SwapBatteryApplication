#include "mainwindow.h"

#include "ElaNavigationBar.h"
#include <QString>

mainwindow::mainwindow(ElaWindow* parent)
    : ElaWindow(parent)
    , ui(new Ui::mainwindowClass())
{
    ui->setupUi(this);

    setProperty("ElaBaseClassName", "ElaWindow");
    resize(1020, 680); // д╛хо©М╦ъ

    /*this->setIsNavigationBarEnable(false);

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    centralWidget->installEventFilter(this);*/

    QWidget* wg_t1 = new QWidget(this);
    QWidget* wg_t2 = new QWidget(this);

    ui->naviBar->addPageNode(QString("Test1"), wg_t1, ElaIconType::AlarmClock);
    ui->naviBar->addPageNode(QString("Test2"), wg_t2, ElaIconType::Airplay);
}

mainwindow::~mainwindow()
{
    delete ui;
}
