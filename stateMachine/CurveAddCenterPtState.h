#ifndef CURVEADDCENTERPTSTATE_H
#define CURVEADDCENTERPTSTATE_H

#include "CurveState.h"

class CurveAddCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // CURVEADDCENTERPTSTATE_H
