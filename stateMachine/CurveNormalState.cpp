#include "CurveNormalState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "Item/CurvePt.h"
#include "Item/CurveCtrlPt.h"
#include "CurveDefines.h"

#include <QDebug>

void CurveNormalState::keyPressEvent(EditorCtrlKeyInfo::ptr event)
{
    int ptCount = m_pService->getModel()->getSize(c_nModelTypePoint);
    for (int i = 0; i < ptCount; i++)
    {
        auto pPointItem = m_pService->getModel()->getTypicalItem<CurvePt>(c_nModelTypePoint, i);
        if (pPointItem->getSelected())
        {
            auto pDeleteCenterPtState = switchState(c_nStateDeleteCenterPt);
            pDeleteCenterPtState->keyPressEvent(event);
            return;
        }
    }
}

void CurveNormalState::keyReleaseEvent(EditorCtrlKeyInfo::ptr event)
{

}

void CurveNormalState::mousePressEvent(QMouseEvent *event)
{
    auto pPointItem = m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypePoint);
    if (pPointItem)
    {
        auto pMoveCenterPtState = switchState(c_nStateMoveCenterPt);
        pMoveCenterPtState->mousePressEvent(event);
        return;
    }

    auto pCtrlInItem = std::dynamic_pointer_cast<CurveCtrlInPt>(m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypeCtrlInPt));
    if (pCtrlInItem && pCtrlInItem->getSelected())
    {
        auto pMoveCenterPtState = switchState(c_nStateMoveCtrlInPt);
        pMoveCenterPtState->mousePressEvent(event);
        return;
    }

    auto pCtrlOutItem = std::dynamic_pointer_cast<CurveCtrlOutPt>(m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypeCtrlOutPt));
    if (pCtrlOutItem && pCtrlOutItem->getSelected())
    {
        auto pMoveCenterPtState = switchState(c_nStateMoveCtrlOutPt);
        pMoveCenterPtState->mousePressEvent(event);
        return;
    }
    clear();
}

void CurveNormalState::mouseMoveEvent(QMouseEvent *event)
{

}

void CurveNormalState::mouseReleaseEvent(QMouseEvent *event)
{

}

void CurveNormalState::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto pCtrlLineItem = m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypeCtrlLine);
    if (pCtrlLineItem)
    {
        auto pAddCenterPtState =  switchState(c_nStateAddCenterPt);
        pAddCenterPtState->mouseDoubleClickEvent(event);
        return;
    }
}

void CurveNormalState::clear()
{
    int size = m_pService->getModel()->getSize(c_nModelTypePoint);
    for (int i = 0; i < size; ++i)
    {
        auto pItem = m_pService->getModel()->getTypicalItem<CurvePt>(c_nModelTypePoint, i);
        pItem->setSelected(false);
    }
}
