#include "CurveLine.h"

#include "CurveDefines.h"

#include <QDebug>

int CurveLine::getType()
{
    return c_nModelTypeLine;
}

/****************************/

void CurveLineX::paint(QPainter *painter)
{
    painter->setPen(QPen("#131415"));

    QLineF line;
    double nX = getPositionX();
    double nY = lineBorderTop;
    QPointF point(nX, nY);
    line.setPoints(point, QPointF(nX, m_pResInfo->getWindowHeight() - lineBorderBottom));
    painter->drawLine(line);

}

/****************************/

void CurveLineY::paint(QPainter *painter)
{
    painter->setPen(QPen("#131415"));

    QLineF line;
    double nX = lineBorderLeft;
    double nY = getPositionY();
    QPointF point(nX, nY);
    line.setPoints(point, QPointF(m_pResInfo->getWindowWidth() - lineBorderRight, nY));
    painter->drawLine(line);
}
