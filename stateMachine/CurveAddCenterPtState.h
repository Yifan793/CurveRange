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

protected:
    void addPt(int index, double dValueX, double dValueY, double dTan);
};

#endif // CURVEADDCENTERPTSTATE_H
