#ifndef CURVENORMALSTATE_H
#define CURVENORMALSTATE_H

#include "CurveState.h"

class CurveNormalState : public CurveState
{
public:
    using CurveState::CurveState;

    void keyPressEvent(CurveBaseKeyInfo::ptr event) override;
    void keyReleaseEvent(CurveBaseKeyInfo::ptr event) override;
    void mouseMoveEvent(CurveBaseMouseInfo::ptr event) override;
    void mousePressEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseReleaseEvent(CurveBaseMouseInfo::ptr event) override;
    void mouseDoubleClickEvent(CurveBaseMouseInfo::ptr event) override;

    void clear();
};

#endif // CURVENORMALSTATE_H
