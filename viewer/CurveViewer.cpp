#include "CurveViewer.h"
#include "Item/CurveItem.h"

CurveViewer::CurveViewer()
{

}

void CurveViewer::addItem(std::shared_ptr<CurveItem> pItem)
{
    m_itemVec.push_back(pItem);
}

void CurveViewer::removeItem(std::shared_ptr<CurveItem> pItem)
{
    m_itemVec.removeAll(pItem);
}

void CurveViewer::paint(QPainter *painter)
{
    for (auto& pItem : m_itemVec)
    {
        pItem->paint(painter);
    }
}
