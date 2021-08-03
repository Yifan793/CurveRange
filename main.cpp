#include "mainwindow.h"
#include "MyWidget.h"
#include "MyWidget2.h"
#include "MyWidget3.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.resize(300, 300);
    w.show();
    return a.exec();
}
