#ifndef CURVESTATEMACHINE_H
#define CURVESTATEMACHINE_H

#include <memory>
#include <QMouseEvent>

class CurveService;
class CurveState;
class CurveStateMachine
{
public:
    CurveStateMachine(std::shared_ptr<CurveService> pService);
    void init();

    std::shared_ptr<CurveState> switchState(int nType);

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

protected:
    void registState(int nStateKey, std::shared_ptr<CurveState> pState);

protected:
    std::shared_ptr<CurveState> m_pCurState;
    std::shared_ptr<CurveService> m_pService;
    QMap<int, std::shared_ptr<CurveState>> m_stateMap;
};

#endif // CURVESTATEMACHINE_H
