#include "CurveCtrlPt.h"

#include <math.h>
#include <QDebug>

#include "CurveDefines.h"

CurveCtrlPt::CurveCtrlPt(std::shared_ptr<CurvePt> pCenterPt)
    : CurvePaintItem(), m_pCenterPt(pCenterPt)
{
}

bool CurveCtrlPt::isHitByPoint(const QPointF &pt)
{
    QRectF rect(m_posX - nRectLength / 2, m_posY - nRectLength / 2, nRectLength, nRectLength);
    QPolygonF polygon(rect);
    return polygon.containsPoint(pt, Qt::OddEvenFill);
}

void CurveCtrlPt::setTan(double dTan)
{
    m_pCenterPt->setTan(dTan);
}

/******************************/

CurveCtrlInPt::CurveCtrlInPt(std::shared_ptr<CurvePt> pCenterPt)
    : CurveCtrlPt(pCenterPt)
{
    if (!pCenterPt)
        assert(false);

    double posX = pCenterPt->getPos().x();
    double posY = pCenterPt->getPos().y();
    double tan = pCenterPt->getTan();
    double dWidth  = sqrt( nLineHalfLength * nLineHalfLength / ( 1 + tan * tan ));
    double dHeight = tan * dWidth;
    m_posX = posX - dWidth;
    m_posY = posY + dHeight;
}

int CurveCtrlInPt::getType()
{
    return c_nModelTypeCtrlInPt;
}

void CurveCtrlInPt::paint(QPainter *painter)
{
    if (!m_pCenterPt)
        return;

    if (!m_pCenterPt->getSelected())
    {
        m_bSelected = false;
        return;
    }

    m_bSelected = true;

    double posX = m_pCenterPt->getPos().x();
    double posY = m_pCenterPt->getPos().y();
    double tan = m_pCenterPt->getTan();
    double dWidth  = sqrt( nLineHalfLength * nLineHalfLength / ( 1 + tan * tan ));
    double dHeight = tan * dWidth;
    m_posX = posX - dWidth;
    m_posY = posY + dHeight;

    painter->setPen(QPen("#FFFFFF"));
    painter->setOpacity(1);
    QLineF line;
    line.setPoints(QPointF(m_posX, m_posY), QPointF(posX, posY));
    painter->drawLine(line);

    painter->setPen(QPen(QColor("#007AFF")));
    painter->setBrush(QBrush(QColor("#FFFFFF")));
    QRectF rectLeft(m_posX - nRectLength / 2, m_posY - nRectLength / 2, nRectLength, nRectLength);
    painter->drawEllipse(rectLeft);
}

/******************************/

CurveCtrlOutPt::CurveCtrlOutPt(std::shared_ptr<CurvePt> pCenterPt)
    : CurveCtrlPt(pCenterPt)
{
    if (!pCenterPt)
        assert(false);

    double posX = pCenterPt->getPos().x();
    double posY = pCenterPt->getPos().y();
    double tan = pCenterPt->getTan();
    double dWidth  = sqrt( nLineHalfLength * nLineHalfLength / ( 1 + tan * tan ));
    double dHeight = tan * dWidth;
    m_posX = posX + dWidth;
    m_posY = posY - dHeight;
}

int CurveCtrlOutPt::getType()
{
    return c_nModelTypeCtrlOutPt;
}

void CurveCtrlOutPt::paint(QPainter *painter)
{
    if (!m_pCenterPt)
        return;

    if (!m_pCenterPt->getSelected())
    {
        m_bSelected = false;
        return;
    }

    m_bSelected = true;

    double posX = m_pCenterPt->getPos().x();
    double posY = m_pCenterPt->getPos().y();
    double tan = m_pCenterPt->getTan();
    double dWidth  = sqrt( nLineHalfLength * nLineHalfLength / ( 1 + tan * tan ));
    double dHeight = tan * dWidth;
    m_posX = posX + dWidth;
    m_posY = posY - dHeight;

    painter->setPen(QPen("#FFFFFF"));
    painter->setOpacity(1);
    QLineF line;
    line.setPoints(QPointF(posX, posY), QPointF(m_posX, m_posY));
    painter->drawLine(line);

    painter->setPen(QPen(QColor("#007AFF")));
    painter->setBrush(QBrush(QColor("#FFFFFF")));
    QRectF rectRight(m_posX - nRectLength / 2, m_posY - nRectLength / 2, nRectLength, nRectLength);
    painter->drawEllipse(rectRight);
}
