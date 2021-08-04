#include "CurveNumber.h"
#include <QDebug>

static int numBorderLeft = 0;
static int numBorderBottom = 14;

int CurveNumber::getType()
{
    return c_nModelTypeNumber;
}

void CurveNumber::paint(QPainter *painter)
{
    painter->setPen(QPen(Qt::white));
    painter->setOpacity(0.3);
    painter->setFont(QFont("PingFangSC", 10));

    if (m_dX == 0 && m_dY == 0)
    {
        QRectF frameRect(numBorderLeft, m_pResInfo->getWindowHeight() - numBorderBottom, 15, 14);
        painter->drawText(frameRect, Qt::AlignCenter, "0");
    }
    else if (m_dX == 0)
    {
        double posY = getPositionY();
        QString strNumber = QString::number(m_dY, 'f', 1);
        int nNumberWidth = painter->fontMetrics().horizontalAdvance(strNumber);
        QRectF frameRect(numBorderLeft, posY - 7, nNumberWidth, 14);
        painter->drawText(frameRect, Qt::AlignCenter, strNumber);
    }
    else if (m_dY == 0)
    {
        double posX = getPositionX();
        QString strNumber = QString::number(m_dX, 'f', 1);
        int nNumberWidth = painter->fontMetrics().horizontalAdvance(strNumber);
        QRectF frameRect(posX - nNumberWidth / 2, m_pResInfo->getWindowHeight() - numBorderBottom, nNumberWidth, 14);
        painter->drawText(frameRect, Qt::AlignCenter, strNumber);
    }
}
