#ifndef CURVESTATEMACHINE_H
#define CURVESTATEMACHINE_H

#include <memory>
#include <QMouseEvent>

#include "CurveState.h"
#include "CurveMouseKeyInfo.h"

class CurveService;
class CurveState;
class CurveStateMachine
{
public:
    CurveStateMachine(std::shared_ptr<CurveService> pService);
    void init();

    std::shared_ptr<CurveState> switchState(int nType);

    virtual void keyPressEvent(CurveBaseKeyInfo::ptr event);
    virtual void keyReleaseEvent(CurveBaseKeyInfo::ptr event);
    virtual void mousePressEvent(CurveBaseMouseInfo::ptr event);
    virtual void mouseMoveEvent(CurveBaseMouseInfo::ptr event);
    virtual void mouseReleaseEvent(CurveBaseMouseInfo::ptr event);
    virtual void mouseDoubleClickEvent(CurveBaseMouseInfo::ptr event);
    virtual void wheelEvent(CurveBaseWheelInfo::ptr event);

protected:
    void registState(int nStateKey, std::shared_ptr<CurveState> pState);

protected:
    std::shared_ptr<CurveState> m_pCurState;
    std::shared_ptr<CurveService> m_pService;
    QMap<int, std::shared_ptr<CurveState>> m_stateMap;
};

#endif // CURVESTATEMACHINE_H
