#ifndef CURVEBACKGROUND_H
#define CURVEBACKGROUND_H

#include "CurveItem.h"

class CurveBackGround : public CurveItem
{
public:
    using CurveItem::CurveItem;
    int getType() override;
    void paint(QPainter *painter) override;
};

#endif // CURVEBACKGROUND_H
