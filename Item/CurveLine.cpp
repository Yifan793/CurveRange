#include "CurveLine.h"

#include "CurveDefines.h"
#include "CurveSceneData.h"

#include <QDebug>

CurveLine::CurveLine(double dX, double dY, std::shared_ptr<CurveResInfoItem> pResInfo, std::shared_ptr<CurveSceneData> pSceneData) :
    CurvePaintItem(dX, dY, pResInfo), m_pSceneData(pSceneData)
{

}

int CurveLine::getType()
{
    return c_nModelTypeLine;
}

/****************************/

void CurveLineX::paint(QPainter *painter)
{
    auto offset = m_pSceneData->offset;
    auto dScale =  m_pSceneData->dScale;

    painter->setPen(QPen("#131415"));

    QLineF line;
    double nX = getPositionX() * dScale + offset.x();
    double nBeginY = lineBorderTop * dScale + offset.y();
    double nEndY = (m_pResInfo->getWindowHeight() - lineBorderBottom) * dScale + offset.y();
    line.setPoints(QPointF(nX, nBeginY), QPointF(nX, nEndY));
    painter->drawLine(line);

}

/****************************/

void CurveLineY::paint(QPainter *painter)
{
    auto offset = m_pSceneData->offset;
    auto dScale =  m_pSceneData->dScale;

    painter->setPen(QPen("#131415"));

    QLineF line;
    double nBeginX = lineBorderLeft * dScale + offset.x();
    double nY = getPositionY() * dScale + offset.y();
    double nEndX = (m_pResInfo->getWindowWidth() - lineBorderRight) * dScale + offset.x();
    line.setPoints(QPointF(nBeginX, nY), QPointF(nEndX, nY));
    painter->drawLine(line);
}
