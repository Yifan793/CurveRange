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
    bool isHitByPoint(const QPointF &pt) override { return false; }

    void setBeginPt(std::shared_ptr<CurvePt> pBeginPt) { m_pBeginPt = pBeginPt; }
    void setEndPt(std::shared_ptr<CurvePt> pEndPt) { m_pEndPt = pEndPt; }
    void setLeftCtrlPt(std::shared_ptr<CurveCtrlOutPt> pCtrlPt) { m_pLeftCtrlPt = pCtrlPt; }
    void setRightCtrlPt(std::shared_ptr<CurveCtrlInPt> pCtrlPt) { m_pRightCtrlPt = pCtrlPt; }

private:
    std::shared_ptr<CurvePt> m_pBeginPt;
    std::shared_ptr<CurvePt> m_pEndPt;
    std::shared_ptr<CurveCtrlOutPt> m_pLeftCtrlPt;
    std::shared_ptr<CurveCtrlInPt> m_pRightCtrlPt;
};

#endif // CURVEPTCTRLLINE_H
