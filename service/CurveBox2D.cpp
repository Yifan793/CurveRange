#include "CurveBox2D.h"

#include "Item/CurveItem.h"

CurveBox2D::CurveBox2D()
{

}

void CurveBox2D::addItem(std::shared_ptr<CurveItem> pItem)
{
    assert(pItem);
    if (!pItem)
        return;
    m_itemVec.append(pItem);
}

void CurveBox2D::insertItem(int index, std::shared_ptr<CurveItem> pItem)
{
    if (!pItem)
        return;
    int count = 0;
    for(auto& item : m_itemVec)
    {
        if (item->getType() == pItem->getType())
        {
            if (count == index)
            {
                int insertIndex = m_itemVec.indexOf(item) - 1;
                if (insertIndex < 0)
                    insertIndex = 0;
                m_itemVec.insert(insertIndex, pItem);
                break;
            }
            count++;
        }
    }
}

void CurveBox2D::removeItem(std::shared_ptr<CurveItem> pItem)
{
    m_itemVec.removeAll(pItem);
}

std::shared_ptr<CurveItem> CurveBox2D::getHitItem(const QPointF &pt) const
{
    for (auto& pItem : m_itemVec)
    {
        if (pItem->isHitByPoint(pt))
            return pItem;
    }
    return nullptr;
}

std::shared_ptr<CurveItem> CurveBox2D::getHitItemByType(const QPointF &pt, int nType) const
{
    for (auto& pItem : m_itemVec)
    {
        if (pItem->getType() != nType)
            continue;
        if (!pItem->isHitByPoint(pt))
            continue;
        return pItem;
    }
    return nullptr;
}

QVector<std::shared_ptr<CurveItem>> CurveBox2D::getHitItems(const QPointF& pt) const
{
    QVector<std::shared_ptr<CurveItem>> hitItems;
    for (auto& pItem : m_itemVec)
    {
        if (!pItem->isHitByPoint(pt))
            continue;
        hitItems.push_back(pItem);
    }
    return hitItems;
}
