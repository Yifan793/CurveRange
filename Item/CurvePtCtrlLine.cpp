#include "CurvePtCtrlLine.h"

#include <math.h>
#include <QDebug>
#include <QPainterPath>

#include "CurveDefines.h"

CurvePtCtrlLine::CurvePtCtrlLine(std::shared_ptr<CurvePt> pBeginPt,
                                 std::shared_ptr<CurvePt> pEndPt,
                                 std::shared_ptr<CurveCtrlOutPt> pLeftCtrlPt,
                                 std::shared_ptr<CurveCtrlInPt> pRightCtrlPt)
    : CurvePaintItem(),
      m_pBeginPt(pBeginPt),
      m_pEndPt(pEndPt),
      m_pLeftCtrlPt(pLeftCtrlPt),
      m_pRightCtrlPt(pRightCtrlPt)
{
}

int CurvePtCtrlLine::getType()
{
    return c_nModelTypeCtrlLine;
}

void CurvePtCtrlLine::paint(QPainter *painter)
{
    painter->setPen(QPen(QColor("#007AFF"), 2));
    QPainterPath path;
    QPointF beginPt = m_pBeginPt->getPos();
    QPointF endPt = m_pEndPt->getPos();

    double dx = endPt.x() - beginPt.x();
    double d1 = dx * m_pBeginPt->getTan();
    double d2 = dx * m_pEndPt->getTan();
    QPointF leftCtrlPt = QPointF( beginPt.x() + dx / 3, beginPt.y() - (d1 / 3));
    QPointF rightCtrlPt = QPointF( endPt.x() - dx / 3, endPt.y() + (d2 / 3));

    path.moveTo(beginPt);
    path.cubicTo(leftCtrlPt, rightCtrlPt, endPt);
    painter->drawPath(path);
}

double CurvePtCtrlLine::getTan(const QPointF &point)
{
    QPointF beginPt = m_pBeginPt->getPos();
    QPointF endPt = m_pEndPt->getPos();
    double dx = endPt.x() - beginPt.x();
    double d1 = dx * m_pBeginPt->getTan();
    double d2 = dx * m_pEndPt->getTan();
    double T = point.x() - beginPt.x();

    double coe0 = (2 * beginPt.y() - d1 - 2 * endPt.y() - d2) / (dx * dx * dx);
    double coe1 = (-3 * beginPt.y() + 2 * d1 + 3 * endPt.y() + d2) / (dx * dx);
    double coe2 = -d1 / dx;

    return -(3*T*T*coe0 + 2*T*coe1 + coe2);
}

//鼠标点击的点是否在曲线上有几像素的误差，通过计算得到准确点
double CurvePtCtrlLine::getY(const QPointF &point)
{
    QPointF beginPt = m_pBeginPt->getPos();
    QPointF endPt = m_pEndPt->getPos();
    double dx = endPt.x() - beginPt.x();
    double d1 = dx * m_pBeginPt->getTan();
    double d2 = dx * m_pEndPt->getTan();
    double T = point.x() - beginPt.x();

    double coe0 = (2 * beginPt.y() - d1 - 2 * endPt.y() - d2) / (dx * dx * dx);
    double coe1 = (-3 * beginPt.y() + 2 * d1 + 3 * endPt.y() + d2) / (dx * dx);
    double coe2 = -d1 / dx;
    double coe3 = beginPt.y();
    return T*(T*(T*coe0 + coe1)+ coe2) +coe3;
}

bool CurvePtCtrlLine::isHitByPoint(const QPointF &pt)
{
    double y = getY(pt);
    if (qAbs(y - pt.y()) < 7)
        return true;
    return false;
}
