#ifndef CURVEPTCTRLPT_H
#define CURVEPTCTRLPT_H

#include "CurveItem.h"
#include "CurvePt.h"
#include "CurveResInfoItem.h"

class CurveCtrlPt : public CurvePaintItem
{
public:
    using CurvePaintItem::CurvePaintItem;
    CurveCtrlPt(std::shared_ptr<CurvePt> pCenterPt);

    bool isHitByPoint(const QPointF& pt) override;

    void setSelected(bool bSeleceted) { m_bSelected = bSeleceted; }
    bool getSelected() { return m_bSelected; }

    std::shared_ptr<CurvePt> getCenterPoint() { return m_pCenterPt; }

    QPointF getPos() { return QPointF(m_posX, m_posY); }

    void setTan(double dTan);

protected:
    double m_posX;
    double m_posY;
    bool m_bSelected = false;
    std::shared_ptr<CurvePt> m_pCenterPt;
};

class CurveCtrlInPt : public CurveCtrlPt
{
public:
    using CurveCtrlPt :: CurveCtrlPt;
    CurveCtrlInPt(std::shared_ptr<CurvePt> pCenterPt);

    int getType() override;
    void paint(QPainter *painter) override;
};

class CurveCtrlOutPt : public CurveCtrlPt
{
public:
    using CurveCtrlPt::CurveCtrlPt;
    CurveCtrlOutPt(std::shared_ptr<CurvePt> pCenterPt);

    int getType() override;
    void paint(QPainter *painter) override;
};

#endif // CURVEPTCTRLPT_H
