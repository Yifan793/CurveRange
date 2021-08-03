#include "MyWidget2.h"

#include "ui_widget.h"
#include <QPainter>
#include <QPainterPath>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *) {
    // 曲线上的点
    static QList<QPointF> points = QList<QPointF>() << QPointF(0, 0) << QPointF(100, 100) << QPointF(200, -100)
                                                    << QPointF(300, 100) << QPointF(330, -80) << QPointF(350, -70);
    QPainterPath path(points[0]);
    //计算
    for (int i = 0; i < points.size() - 1; ++i) {
        // 控制点的 x 坐标为 sp 与 ep 的 x 坐标和的一半
        // 第一个控制点 c1 的 y 坐标为起始点 sp 的 y 坐标
        // 第二个控制点 c2 的 y 坐标为结束点 ep 的 y 坐标
        QPointF sp = points[i];
        QPointF ep = points[i+1];
        QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
        QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
        path.cubicTo(c1, c2, ep);
    }
    QPainter painter(this);
    //设置渲染提示为消除锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    //设置画笔颜色和宽度
    painter.setPen(QPen(Qt::black, 2));
    //将坐标系转换为矢量
    painter.translate(40, 130);
    //绘制path
    painter.drawPath(path);
    // 绘制曲线上的点
    painter.setBrush(Qt::gray);
    //绘制曲线上的点
    for (int i = 0; i < points.size(); ++i) {
        painter.drawEllipse(points[i], 4, 4);
    }
}
