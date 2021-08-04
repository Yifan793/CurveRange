#include "CurveResInfoItem.h"

#include "CurveDefines.h"

int CurveResInfoItem::getType()
{
    return c_nModelTypeResInfo;
}

void CurveResInfoItem::addKeyPoint(double x, double y, double inTan, double outTan)
{
    CurveKeyPoint keyPoint = { x, y, inTan, outTan };
    m_CurveKeyPoints.append(keyPoint);
}

void CurveResInfoItem::removeKeyPoint(int index)
{
    m_CurveKeyPoints.remove(index);
}
