#ifndef CURVEDELETECENTERPTSTATE_H
#define CURVEDELETECENTERPTSTATE_H

#include "CurveState.h"

class CurvePt;
class CurveDeleteCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void keyPressEvent(CurveBaseKeyInfo::ptr event) override;
    void keyReleaseEvent(CurveBaseKeyInfo::ptr event) override;
};

#endif // CURVEDELETECENTERPTSTATE_H
