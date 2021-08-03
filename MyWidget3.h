#ifndef MYWIDGET3_H
#define MYWIDGET3_H

#include <QQuickWidget>

class MyWidget3 : public QQuickWidget
{
    Q_OBJECT
public:
    MyWidget3();
    QString getQmlUrl();
};

#endif // MYWIDGET3_H
