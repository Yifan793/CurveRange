#ifndef CURVEMOVEPTSTATE_H
#define CURVEMOVEPTSTATE_H

#include "CurveState.h"

class CurvePt;
class CurveMoveCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void onStart() override;

    void mousePressEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseMoveEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseReleaseEvent(CurveBaseMouseInfo::ptr event) override;

protected:
    void checkIsOutOfRange(QPointF point);

protected:
    std::shared_ptr<CurvePt> m_pMoveItem;
    QPointF m_lastPt;
};

#endif // CURVEMOVEPTSTATE_H
