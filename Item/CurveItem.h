#ifndef CURVEITEM_H
#define CURVEITEM_H

#include <QPainter>

class CurveItem
{
public:
    CurveItem();

    virtual int getType() = 0;
    virtual void paint(QPainter* painter) = 0;
};

#endif // CURVEITEM_H
