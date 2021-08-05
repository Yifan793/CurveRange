#ifndef CURVENORMALSTATE_H
#define CURVENORMALSTATE_H

#include "CurveState.h"

class CurveNormalState : public CurveState
{
public:
    using CurveState::CurveState;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void clear();
};

#endif // CURVENORMALSTATE_H
