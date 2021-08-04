#include "CurveBackGround.h"

#include "CurveDefines.h"

int CurveBackGround::getType()
{
    return c_nModelTypeBackGround;
}

void CurveBackGround::paint(QPainter *painter)
{
    QColor bgColor("#222222");
    QRect rect(0, 0, c_nFixedCurveWidth, c_nFixedCurveHeight);
    painter->fillRect(rect, bgColor);
}
