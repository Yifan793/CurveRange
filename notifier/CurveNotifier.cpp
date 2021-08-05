#include "CurveNotifier.h"

#include "CurveDefines.h"

int CurveNotifyUnit::addNotifyFunc(std::function<void (std::shared_ptr<CurveNotifyData>)> pFunc)
{
    m_notifyFuncs[m_nNextFuncIndex] = pFunc;
    ++m_nNextFuncIndex;
    return m_nNextFuncIndex;
}

void CurveNotifyUnit::notify(std::shared_ptr<CurveNotifyData> pData)
{
    for (auto it = m_notifyFuncs.begin(), endIt = m_notifyFuncs.end(); it != endIt; ++it)
    {
        auto pFunc = it.value();
        pFunc(pData);
    }
}

void CurveNotifyUnit::eraseFunc(int nIndex)
{
    auto it = m_notifyFuncs.find(nIndex);
    if (it != m_notifyFuncs.end())
        m_notifyFuncs.erase(it);
}

CurveNotifier::CurveNotifier()
{
    addUnit(c_nPointChangedNotifyType);
}

void CurveNotifier::addUnit(int type)
{
    std::shared_ptr<CurveNotifyUnit> pUnit(new CurveNotifyUnit);
    m_notifyFuncUnits[type] = pUnit;
}

int CurveNotifier::addNotifyFunc(int type, std::function<void (std::shared_ptr<CurveNotifyData>)> pFunc)
{
    auto it = m_notifyFuncUnits.find(type);
    if (it == m_notifyFuncUnits.end())
        return -1;
    return it.value()->addNotifyFunc(pFunc);
}

void CurveNotifier::eraseFunc(int type, int nIndex)
{
    auto it = m_notifyFuncUnits.find(type);
    if (it == m_notifyFuncUnits.end())
        return;
    return it.value()->eraseFunc(nIndex);
}

void CurveNotifier::notify(int type, std::shared_ptr<CurveNotifyData> pData)
{
    auto it = m_notifyFuncUnits.find(type);
    if (it == m_notifyFuncUnits.end())
        return;
    return it.value()->notify(pData);
}
