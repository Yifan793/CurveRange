#include "CurvePt.h"

#include "CurveDefines.h"
#include "Item/CurveCtrlPt.h"

#include <QDebug>

CurvePt::CurvePt(double dX, double dY, double dTan, std::shared_ptr<CurveResInfoItem> pResInfo)
    : CurvePaintItem(dX, dY, pResInfo), m_tangent(dTan)
{
    m_posX = getPositionX();
    m_posY = getPositionY();
}

int CurvePt::getType()
{
    return c_nModelTypePoint;
}

void CurvePt::paint(QPainter *painter)
{
    painter->setPen(QPen("#007AFF"));
    painter->setOpacity(1);

    QRectF rectCenter(m_posX - nRectLength / 2, m_posY - nRectLength / 2, nRectLength, nRectLength);
    painter->fillRect(rectCenter, "#FFFFFF");
    painter->drawRect(rectCenter);

    if (m_bSelected)
    {
        painter->fillRect(rectCenter, "#007AFF");
    }
}

bool CurvePt::isHitByPoint(const QPointF &pt)
{
    QRectF rect(m_posX - nRectLength / 2, m_posY - nRectLength / 2, nRectLength, nRectLength);
    QPolygonF polygon(rect);

    qDebug() << "test CurvePt isHitByPoint " << pt << " rect " << rect << " polygon " << polygon;
    return polygon.containsPoint(pt, Qt::OddEvenFill);
}

void CurvePt::setPos(QPointF pos)
{
     m_posX = pos.x();
     m_posY = pos.y();
     auto pNotifyData = std::make_shared<CurveNotifyData>();
     pNotifyData->m_pos = QPointF(m_posX, m_posY);
     if (m_pNotifier)
     {
         m_pNotifier->notify(c_nPointChangedNotifyType, pNotifyData);
     }
}

QPointF CurvePt::getPos() const
{
    qDebug() << "test posX " << m_posX << " " << m_posY;
    return QPointF(m_posX, m_posY);
}
