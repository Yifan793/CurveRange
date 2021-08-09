#ifndef CURVEMOVEPTSTATE_H
#define CURVEMOVEPTSTATE_H

#include "CurveState.h"

class CurvePt;
class CurveMoveCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void onStart() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void checkIsOutOfRange(QPointF point);

protected:
    std::shared_ptr<CurvePt> m_pMoveItem;
    QPointF m_lastPt;
};

#endif // CURVEMOVEPTSTATE_H
