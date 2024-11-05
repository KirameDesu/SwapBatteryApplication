#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include "ElaApplication.h"
#include "ElaWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ElaApplication::getInstance()->init();
    MainWindow e;
    e.show();

    return a.exec();
}
