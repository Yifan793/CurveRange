#include "CurvePt.h"

#include "CurveDefines.h"
#include <QDebug>

static int nLength = 6;

int CurvePt::getType()
{
    return c_nModelTypePoint;
}

void CurvePt::paint(QPainter *painter)
{
    painter->setPen(QPen("#007AFF"));
    painter->setOpacity(1);
    double posX = getPositionX();
    double posY = getPositionY();

    QRect rect(posX - nLength / 2, posY - nLength / 2, nLength, nLength);
    painter->fillRect(rect, "#FFFFFF");
    painter->drawRect(rect);
}
