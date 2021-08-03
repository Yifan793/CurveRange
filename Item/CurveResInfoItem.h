#ifndef CURVERESINFOITEM_H
#define CURVERESINFOITEM_H

#include "CurveItem.h"

class CurveResInfoItem : public CurveItem
{
public:
    using CurveItem::CurveItem;
    int getType() override;
    void paint(QPainter *painter) { Q_UNUSED(painter) };
};

#endif // CURVERESINFOITEM_H
