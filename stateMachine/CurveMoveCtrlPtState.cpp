#include "CurveMoveCtrlPtState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "CurveDefines.h"
#include "Item/CurveCtrlPt.h"

void CurveMoveCtrlInPtState::mousePressEvent(CurveBaseMouseInfo::ptr event)
{
    m_pMoveItem = std::dynamic_pointer_cast<CurveCtrlInPt>(m_pService->getBox2D()->getHitItemByType(event->scenePos, c_nModelTypeCtrlInPt));
}

void CurveMoveCtrlInPtState::mouseMoveEvent(CurveBaseMouseInfo::ptr event)
{
    if (!m_pMoveItem)
    {
        auto pState = switchState(c_nStateNormal);
        pState->mousePressEvent(event);
        return;
    }

    QPointF centerPos = m_pMoveItem->getCenterPoint()->getPos();
    double dTan = (event->scenePos.y() -  centerPos.y()) / (centerPos.x() - event->scenePos.x());
    m_pMoveItem->setTan(dTan);
}

void CurveMoveCtrlInPtState::mouseReleaseEvent(CurveBaseMouseInfo::ptr event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
}

/*******************************/

void CurveMoveCtrlOutPtState::mousePressEvent(CurveBaseMouseInfo::ptr event)
{
    m_pMoveItem = std::dynamic_pointer_cast<CurveCtrlOutPt>(m_pService->getBox2D()->getHitItemByType(event->scenePos, c_nModelTypeCtrlOutPt));
}

void CurveMoveCtrlOutPtState::mouseMoveEvent(CurveBaseMouseInfo::ptr event)
{
    if (!m_pMoveItem)
    {
        auto pState = switchState(c_nStateNormal);
        pState->mousePressEvent(event);
        return;
    }

    QPointF centerPos = m_pMoveItem->getCenterPoint()->getPos();
    double dTan = (centerPos.y() - event->scenePos.y()) / (event->scenePos.x() - centerPos.x());
    m_pMoveItem->setTan(dTan);

}

void CurveMoveCtrlOutPtState::mouseReleaseEvent(CurveBaseMouseInfo::ptr event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
}
