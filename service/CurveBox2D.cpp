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
    m_items.append(pItem);
}

void CurveBox2D::eraseItem(std::shared_ptr<CurveItem> pItem)
{
    m_items.removeAll(pItem);
}

std::shared_ptr<CurveItem> CurveBox2D::getHitItem(const QPointF &pt) const
{
    for (auto& pItem : m_items)
    {
        if (pItem->isHitByPoint(pt))
            return pItem;
    }
    return nullptr;
}

std::shared_ptr<CurveItem> CurveBox2D::getHitItemByType(const QPointF &pt, int nType) const
{
    for (auto& pItem : m_items)
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
    for (auto& pItem : m_items)
    {
        if (!pItem->isHitByPoint(pt))
            continue;
        hitItems.push_back(pItem);
    }
    return hitItems;
}
