#ifndef CURVENUMBER_H
#define CURVENUMBER_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"

class CurveNumber : public CurvePaintItem
{
public:
    using CurvePaintItem::CurvePaintItem;
    int getType() override;
    void paint(QPainter *painter) override;
};

#endif // CURVENUMBER_H
