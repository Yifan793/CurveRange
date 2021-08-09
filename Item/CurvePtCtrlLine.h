#ifndef CURVEPTCTRLLINE_H
#define CURVEPTCTRLLINE_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"
#include "CurvePt.h"
#include "CurveCtrlPt.h"

class CurvePtCtrlLine : public CurvePaintItem
{
public:

    //left是曲线的左控制点， right是曲线的右控制点
    //in是中点的左边点，out是中点的右边点
    using CurvePaintItem::CurvePaintItem;
    CurvePtCtrlLine(std::shared_ptr<CurvePt> pBeginPt,
                    std::shared_ptr<CurvePt> pEndPt,
                    std::shared_ptr<CurveCtrlOutPt> pLeftCtrlPt,
                    std::shared_ptr<CurveCtrlInPt> pRightCtrlPt);
    int getType() override;
    void paint(QPainter *painter) override;
    bool isHitByPoint(const QPointF &pt) override;

    double getTan(const QPointF& point);
    double getY(const QPointF& point);

    void setBeginPt(std::shared_ptr<CurvePt> pBeginPt) { m_pBeginPt = pBeginPt; }
    std::shared_ptr<CurvePt> getBeginPt() { return m_pBeginPt; }
    void setEndPt(std::shared_ptr<CurvePt> pEndPt) { m_pEndPt = pEndPt; }
    std::shared_ptr<CurvePt> getEndPt() { return m_pEndPt; }
    void setLeftCtrlPt(std::shared_ptr<CurveCtrlOutPt> pCtrlPt) { m_pLeftCtrlPt = pCtrlPt; }
    std::shared_ptr<CurveCtrlOutPt> getLeftCtrlPt() { return m_pLeftCtrlPt; }
    void setRightCtrlPt(std::shared_ptr<CurveCtrlInPt> pCtrlPt) { m_pRightCtrlPt = pCtrlPt; }
    std::shared_ptr<CurveCtrlInPt> getRightCtrlPt() { return m_pRightCtrlPt; }

private:
    std::shared_ptr<CurvePt> m_pBeginPt;
    std::shared_ptr<CurvePt> m_pEndPt;
    std::shared_ptr<CurveCtrlOutPt> m_pLeftCtrlPt;
    std::shared_ptr<CurveCtrlInPt> m_pRightCtrlPt;
};

#endif // CURVEPTCTRLLINE_H
