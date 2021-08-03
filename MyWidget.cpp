#include "MyWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{

    startLabel=new QLabel(this);
    startLabel->resize(10, 10);
    startLabel->setStyleSheet("QLabel{background-color:red;}");
    startLabel->move(100, 110);

    ctrlLabel1=new QLabel(this);
    ctrlLabel1->resize(10, 10);
    ctrlLabel1->setStyleSheet("QLabel{background-color:green;}");
    ctrlLabel1->move(120, 120);

    ctrlLabel2=new QLabel(this);
    ctrlLabel2->resize(10, 10);
    ctrlLabel2->setStyleSheet("QLabel{background-color:blue;}");
    ctrlLabel2->move(140, 130);

    endLabel=new QLabel(this);
    endLabel->resize(10, 10);
    endLabel->setStyleSheet("QLabel{background-color:black;}");
    endLabel->move(160, 140);

    ctrlLabel3=new QLabel(this);
    ctrlLabel3->resize(10, 10);
    ctrlLabel3->setStyleSheet("QLabel{background-color:yellow;}");
    ctrlLabel3->move(180, 150);

    ctrlLabel4=new QLabel(this);
    ctrlLabel4->resize(10, 10);
    ctrlLabel4->setStyleSheet("QLabel{background-color:cyan;}");
    ctrlLabel4->move(200, 160);

    endLabel2=new QLabel(this);
    endLabel2->resize(10, 10);
    endLabel2->setStyleSheet("QLabel{background-color:#AAAAEE;}");
    endLabel2->move(220, 170);

    selectedWidget=NULL;
}


void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawLine(startLabel->pos(), ctrlLabel1->pos());
    painter.drawLine(ctrlLabel2->pos(), endLabel->pos());
    painter.drawLine(endLabel->pos(), ctrlLabel3->pos());
    painter.drawLine(ctrlLabel4->pos(), endLabel2->pos());

    QPainterPath myPath;
    myPath.moveTo(startLabel->pos());
    myPath.cubicTo(ctrlLabel1->pos(), ctrlLabel2->pos(), endLabel->pos());
    myPath.cubicTo(ctrlLabel3->pos(), ctrlLabel4->pos(), endLabel2->pos());
    painter.setPen(Qt::red);
    painter.drawPath(myPath);
}


void MyWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget *w=this->childAt(event->pos());
    if(w==NULL) return;
    if(w->inherits("QLabel")){
        selectedWidget=w;
    }
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    selectedWidget=NULL;
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(selectedWidget!=NULL){
        selectedWidget->move(event->pos());
        this->update();
    }
}
