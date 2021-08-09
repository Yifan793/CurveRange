#ifndef CURVENORMALSTATE_H
#define CURVENORMALSTATE_H

#include "CurveState.h"

class CurveNormalState : public CurveState
{
public:
    using CurveState::CurveState;

    void keyPressEvent(EditorCtrlKeyInfo::ptr event) override;
    void keyReleaseEvent(EditorCtrlKeyInfo::ptr event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void clear();
};

#endif // CURVENORMALSTATE_H
