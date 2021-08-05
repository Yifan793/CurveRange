#ifndef CURVESELECTCENTERPTSTATE_H
#define CURVESELECTCENTERPTSTATE_H

#include "CurveState.h"

class CurveSelectCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CURVESELECTCENTERPTSTATE_H
