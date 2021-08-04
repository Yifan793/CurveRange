#include "mainwindow.h"
#include "MyWidget.h"
#include "MyWidget2.h"
#include "MyWidget3.h"
#include "CurveManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qmlRegisterType<CurveManager>("CurveManager", 1, 0, "CurveManager");
    MyWidget3 w;
    w.resize(300, 300);
    w.show();
    return a.exec();
}
