#ifndef CURVESTATE_H
#define CURVESTATE_H

#include <QMouseEvent>
#include "CurveDefines.h"
#include "CurveMouseKeyInfo.h"

class CurveService;
class CurvePt;
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

    virtual void keyPressEvent(CurveBaseKeyInfo::ptr event) { Q_UNUSED(event) }
    virtual void keyReleaseEvent(CurveBaseKeyInfo::ptr event) { Q_UNUSED(event) }
    virtual void mousePressEvent(CurveBaseMouseInfo::ptr event) { Q_UNUSED(event) }
    virtual void mouseMoveEvent(CurveBaseMouseInfo::ptr event) { Q_UNUSED(event) }
    virtual void mouseReleaseEvent(CurveBaseMouseInfo::ptr event) { Q_UNUSED(event) }
    virtual void mouseDoubleClickEvent(CurveBaseMouseInfo::ptr event) { Q_UNUSED(event) }
    virtual void wheelEvent(CurveBaseWheelInfo::ptr event) { Q_UNUSED(event) }

protected:
    std::shared_ptr<CurveState> switchState(int nType) { return m_pSwitchFunc(nType); }
    void insertPt(int index, double dValueX, double dValueY, double dTan);
    void deletePt(std::shared_ptr<CurvePt> pItem);
    double getValueX(double posX) const;
    double getValueY(double posY) const;
    double getPosX(double valueX) const;
    double getPosY(double valueY) const;

protected:
    int m_nType;
    std::shared_ptr<CurveService> m_pService;
    std::function<std::shared_ptr<CurveState>(int)> m_pSwitchFunc;
};

#endif // CURVESTATE_H
