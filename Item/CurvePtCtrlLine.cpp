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
    QPointF leftCtrlPt = m_pLeftCtrlPt->getPos();
    QPointF rightCtrlPt = m_pRightCtrlPt->getPos();
    path.moveTo(beginPt);
    path.cubicTo(leftCtrlPt, rightCtrlPt, endPt);
    painter->drawPath(path);
}
