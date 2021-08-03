#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QLabel>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

    QLabel *startLabel;
    QLabel *ctrlLabel1;
    QLabel *ctrlLabel2;
    QLabel *endLabel;

    QLabel *ctrlLabel3;
    QLabel *ctrlLabel4;
    QLabel *endLabel2;

    QWidget *selectedWidget;

private:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYWIDGET_H
