#ifndef CURVEDELETECENTERPTSTATE_H
#define CURVEDELETECENTERPTSTATE_H

#include "CurveState.h"

class CurvePt;
class CurveDeleteCenterPtState : public CurveState
{
public:
    using CurveState::CurveState;

    void keyPressEvent(EditorCtrlKeyInfo::ptr event) override;
    void keyReleaseEvent(EditorCtrlKeyInfo::ptr event) override;
};

#endif // CURVEDELETECENTERPTSTATE_H
