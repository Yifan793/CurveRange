#ifndef CURVESTATE_H
#define CURVESTATE_H

#include <QMouseEvent>

class CurveService;
class CurveState
{
public:
    CurveState();
    void setStateType(int nType) { m_nType = nType; }
    int getStateType() { return m_nType; }
    void setService(std::shared_ptr<CurveService> pService) { m_pService = pService; }
    void setSwitchFunc(std::function<std::shared_ptr<CurveState>(int)> pFunc) { m_pSwitchFunc = pFunc; }

    virtual void onStart() {}
    virtual void onStop() {}

    virtual void mousePressEvent(QMouseEvent* event) { Q_UNUSED(event) }
    virtual void mouseMoveEvent(QMouseEvent* event) { Q_UNUSED(event) }
    virtual void mouseReleaseEvent(QMouseEvent* event) { Q_UNUSED(event) }


private:
    int m_nType;
    std::shared_ptr<CurveService> m_pService;
    std::function<std::shared_ptr<CurveState>(int)> m_pSwitchFunc;
};

#endif // CURVESTATE_H
