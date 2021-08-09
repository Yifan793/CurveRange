#ifndef CURVESELECTCENTERPTSTATE_H
#define CURVESELECTCENTERPTSTATE_H

#include "CurveState.h"

class CurveSelectCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void mouseMoveEvent(CurveBaseMouseInfo::ptr event) override;
    void mousePressEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseReleaseEvent(CurveBaseMouseInfo::ptr event) override;
};

#endif // CURVESELECTCENTERPTSTATE_H
