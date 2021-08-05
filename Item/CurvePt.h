#ifndef CURVEPT_H
#define CURVEPT_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"

class CurvePt : public CurvePaintItem
{
public:
    enum PointType
    {
        NormalPt,
        LeftMostPt,
        RightMostPt
    };

    using CurvePaintItem::CurvePaintItem;
    CurvePt(double dX, double dY, double dTan, std::shared_ptr<CurveResInfoItem> pResInfo);
    int getType() override;
    void paint(QPainter *painter) override;
    bool isHitByPoint(const QPointF& pt) override;

    void setSelected(bool bSeleceted) { m_bSelected = bSeleceted; }
    bool getSelected() { return m_bSelected; }

    void setTan(double dTan) { m_tangent = dTan; }
    double getTan() { return m_tangent; }

    void setPos(QPointF pos);
    QPointF getPos() const;

protected:
    double m_tangent;
    double m_posX;
    double m_posY;
    bool m_bSelected = false;
};

#endif // CURVEPT_H
