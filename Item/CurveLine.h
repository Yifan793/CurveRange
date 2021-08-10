#ifndef CURVELINE_H
#define CURVELINE_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"

#include <memory>

class CurveLine : public CurvePaintItem
{
public:
    using CurvePaintItem::CurvePaintItem;
    CurveLine(double dX, double dY, std::shared_ptr<CurveResInfoItem> pResInfo, std::shared_ptr<CurveSceneData> pSceneData);
    int getType() override;
    bool isHitByPoint(const QPointF& pt) override { return false; }

protected:
    std::shared_ptr<CurveSceneData> m_pSceneData;
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
