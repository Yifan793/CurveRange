#ifndef CURVEMOVECTRLPT_H
#define CURVEMOVECTRLPT_H

#include "CurveState.h"

class CurveCtrlInPt;
class CurveCtrlOutPt;
class CurveMoveCtrlInPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void mousePressEvent(CurveBaseMouseInfo::ptr) override;
    void mouseMoveEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseReleaseEvent(CurveBaseMouseInfo::ptr event) override;

protected:
    std::shared_ptr<CurveCtrlInPt> m_pMoveItem;
};

class CurveMoveCtrlOutPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void mousePressEvent(CurveBaseMouseInfo::ptr) override;
    void mouseMoveEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseReleaseEvent(CurveBaseMouseInfo::ptr event) override;

protected:
    std::shared_ptr<CurveCtrlOutPt> m_pMoveItem;
};


#endif // CURVEMOVECTRLPT_H
