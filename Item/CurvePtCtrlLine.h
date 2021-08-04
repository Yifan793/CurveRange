#ifndef CURVEPTCTRLLINE_H
#define CURVEPTCTRLLINE_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"

class CurvePtCtrlLine : public CurvePaintItem
{
public:
    using CurvePaintItem::CurvePaintItem;
    int getType() override;
    void paint(QPainter *painter) override;
};

#endif // CURVEPTCTRLLINE_H
