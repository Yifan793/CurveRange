#ifndef CURVEMOVEPTSTATE_H
#define CURVEMOVEPTSTATE_H

#include "CurveState.h"

class CurveMovePtState : public CurveState
{
public:
    using CurveState::CurveState;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CURVEMOVEPTSTATE_H
