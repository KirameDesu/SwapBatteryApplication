#include "mainwindow.h"
#include <QtWidgets/QApplication>

#include "ElaApplication.h"
#include "ElaWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ElaApplication::getInstance()->init();
    mainwindow e;
    e.show();

    return a.exec();
}
