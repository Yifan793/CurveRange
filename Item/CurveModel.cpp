#include "CurveModel.h"

#include "viewer/CurveViewer.h"
#include "service/CurveBox2D.h"

CurveModel::CurveModel(std::shared_ptr<CurveViewer> pViewer, std::shared_ptr<CurveBox2D> pBox2D)
    : m_pViewer(pViewer), m_pBox2D(pBox2D)
{

}

void CurveModel::addItem(int type, std::shared_ptr<CurveItem> pItem)
{
    ensureValid(type);
    auto pUnit = m_modelUnitMap[type];
    pUnit->m_ItemVec.append(pItem);
    m_pViewer->addItem(pItem);
    m_pBox2D->addItem(pItem);
}

std::shared_ptr<CurveItem> CurveModel::getItem(int type, int index) const
{
    auto it = m_modelUnitMap.find(type);
    if (it == m_modelUnitMap.end())
        return nullptr;
    auto pUnit = it.value();
    int nSize = pUnit->m_ItemVec.size();
    if (index < 0 || index >= nSize)
        return nullptr;
    return pUnit->m_ItemVec[index];
}

int CurveModel::getSize(int type)
{
    auto it = m_modelUnitMap.find(type);
    if (it == m_modelUnitMap.end())
        return -1;
    auto pUnit = it.value();
    return pUnit->m_ItemVec.size();
}

void CurveModel::clearUnit(int nType)
{
    auto it = m_modelUnitMap.find(nType);
    if (it == m_modelUnitMap.end())
        return;
    auto pRemoveItems = it.value()->m_ItemVec;
    for( auto pItem : pRemoveItems)
    {
        m_pViewer->removeItem(pItem);
        m_pBox2D->eraseItem(pItem);
    }
    it.value()->m_ItemVec.clear();
}

void CurveModel::ensureValid(int type)
{
    auto it = m_modelUnitMap.find(type);
    if (it == m_modelUnitMap.end())
    {
        auto pNewUnit = std::shared_ptr<ModelUnit>(new ModelUnit);
        m_modelUnitMap[type] = pNewUnit;
    }
}
