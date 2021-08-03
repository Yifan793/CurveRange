#ifndef MYWIDGET2_H
#define MYWIDGET2_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // MYWIDGET2_H
