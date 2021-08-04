#ifndef CURVEPT_H
#define CURVEPT_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"

class CurvePt : public CurvePaintItem
{
public:
    using CurvePaintItem::CurvePaintItem;
    int getType() override;
    void paint(QPainter *painter) override;
};

#endif // CURVEPT_H
