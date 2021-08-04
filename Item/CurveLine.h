#ifndef CURVELINE_H
#define CURVELINE_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"

#include <memory>

class CurveLine : public CurvePaintItem
{
public:
    using CurvePaintItem::CurvePaintItem;
    int getType() override;
};

class CurveLineX : public CurveLine
{
public:
    using CurveLine::CurveLine;
    void paint(QPainter *painter) override;
};

class CurveLineY : public CurveLine
{
public:
    using CurveLine::CurveLine;
    void paint(QPainter *painter) override;
};

#endif // CURVELINE_H
