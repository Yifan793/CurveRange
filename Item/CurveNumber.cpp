#include "CurveNumber.h"

#include <QDebug>
#include "CurveSceneData.h"
#include "CurveDefines.h"

CurveNumber::CurveNumber(double dX, double dY, std::shared_ptr<CurveResInfoItem> pResInfo, std::shared_ptr<CurveSceneData> pSceneData) :
    CurvePaintItem(dX, dY, pResInfo), m_pSceneData(pSceneData)
{
}

int CurveNumber::getType()
{
    return c_nModelTypeNumber;
}

void CurveNumber::paint(QPainter *painter)
{
    painter->setPen(QPen(Qt::white));
    painter->setOpacity(0.3);
    painter->setFont(QFont("PingFangSC", 10));

    auto offset = m_pSceneData->offset;
    auto dScale =  m_pSceneData->dScale;

    QTransform numTransform;
    numTransform = numTransform.translate(m_nPixelRatio, m_nPixelRatio);
    numTransform = numTransform.scale(m_nPixelRatio, m_nPixelRatio);
    painter->setTransform(numTransform);

    if (m_dX == 0 && m_dY == 0)
    {
        double posX = getPositionX();
        double posY = getPositionY();
        QRectF frameRect((posX - 15 / 2) * dScale + offset.x() - 12, (posY - 7) * dScale + offset.y() + 10, 15, 14);
        painter->drawText(frameRect, Qt::AlignCenter, "0");
    }
    else if (m_dX == 0)
    {
        double posY = getPositionY();
        QString strNumber = QString::number(m_dY, 'f', 1);
        int nNumberWidth = painter->fontMetrics().horizontalAdvance(strNumber);
        QRectF frameRect(numBorderLeft, (posY - 7) * dScale + offset.y(), nNumberWidth, 14 * dScale);
        painter->drawText(frameRect, Qt::AlignCenter, strNumber);
    }
    else if (m_dY == 0)
    {
        double posX = getPositionX();
        QString strNumber = QString::number(m_dX, 'f', 1);
        int nNumberWidth = painter->fontMetrics().horizontalAdvance(strNumber);
        QRectF frameRect((posX - nNumberWidth / 2) * dScale + offset.x(), m_pResInfo->getWindowHeight() - numBorderBottom, nNumberWidth * dScale , 14);
        painter->drawText(frameRect, Qt::AlignCenter, strNumber);
    }
}
