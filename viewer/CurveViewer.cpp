#include "CurveViewer.h"

#include "Item/CurveItem.h"
#include "CurveDefines.h"

#include <QDebug>

CurveViewer::CurveViewer()
{
    initPainterOrder();
}

void CurveViewer::initPainterOrder()
{
    m_paintOrder = { c_nModelTypeLine,
                     c_nModelTypeNumber,
                     c_nModelTypeCtrlLine,
                     c_nModelTypeCtrlInPt,
                     c_nModelTypeCtrlOutPt,
                     c_nModelTypePoint
                   };
}

void CurveViewer::addItem(std::shared_ptr<CurveItem> pItem)
{
    m_itemVec.push_back(pItem);
}

void CurveViewer::insertItem(int index, std::shared_ptr<CurveItem> pItem)
{
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

void CurveViewer::removeItem(std::shared_ptr<CurveItem> pItem)
{
    m_itemVec.removeAll(pItem);
}

void CurveViewer::paint(QPainter *painter)
{
    auto paintOrder = getPainterOrder();
    for (int itemType : paintOrder)
    {
        for (auto& pItem : m_itemVec)
        {
            if (pItem->getType() == itemType)
            {
                pItem->paint(painter);
            }
        }
    }
}
