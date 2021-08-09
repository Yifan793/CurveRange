#ifndef CURVEADDCENTERPTSTATE_H
#define CURVEADDCENTERPTSTATE_H

#include "CurveState.h"

class CurveAddCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void mouseMoveEvent(CurveBaseMouseInfo::ptr event) override;
    void mousePressEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseReleaseEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseDoubleClickEvent(CurveBaseMouseInfo::ptr event) override;
};

#endif // CURVEADDCENTERPTSTATE_H
