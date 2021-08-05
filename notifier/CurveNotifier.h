#ifndef CURVENOTIFIER_H
#define CURVENOTIFIER_H

#include <memory>
#include <functional>
#include <QMap>
#include <QPointF>

class CurvePaintItem;
class CurveNotifyData
{
public:
    QPointF m_pos;
};

class CurveNotifyUnit
{
public:
    int addNotifyFunc(std::function<void(std::shared_ptr<CurveNotifyData>)> pFunc);
    void notify(std::shared_ptr<CurveNotifyData> pData);
    void eraseFunc(int nIndex);

protected:
    QMap<int, std::function<void(std::shared_ptr<CurveNotifyData>)>> m_notifyFuncs;
    int m_nNextFuncIndex = 0;
};

class CurveNotifier
{
public:
    CurveNotifier();
    virtual ~CurveNotifier() {};

    int addNotifyFunc(int type, std::function<void(std::shared_ptr<CurveNotifyData>)> pFunc);
    void notify(int type, std::shared_ptr<CurveNotifyData> pData);
    void eraseFunc(int type, int nIndex);
    void blockNotifier(bool bFlag)
    {
        if (bFlag)
            m_nBlocked++;
        else
            m_nBlocked--;
    }

    bool isBlocked() { return m_nBlocked != 0; }

protected:
    virtual void addUnit(int type);

protected:
    QMap<int, std::shared_ptr<CurveNotifyUnit>> m_notifyFuncUnits;
    int m_nBlocked = 0;
};

#endif // CURVENOTIFIER_H
