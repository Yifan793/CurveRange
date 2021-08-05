#include "CurveMoveCtrlPtState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "CurveDefines.h"
#include "Item/CurveCtrlPt.h"

void CurveMoveCtrlInPtState::mousePressEvent(QMouseEvent *event)
{
    m_pMoveItem = std::dynamic_pointer_cast<CurveCtrlInPt>(m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypeCtrlInPt));
}

void CurveMoveCtrlInPtState::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pMoveItem)
    {
        auto pState = switchState(c_nStateNormal);
        pState->mousePressEvent(event);
        return;
    }

    QPointF centerPos = m_pMoveItem->getCenterPoint()->getPos();
    double dTan = (event->pos().y() -  centerPos.y()) / (centerPos.x() - event->pos().x());
    m_pMoveItem->setTan(dTan);
}

void CurveMoveCtrlInPtState::mouseReleaseEvent(QMouseEvent *event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
}

/*******************************/

void CurveMoveCtrlOutPtState::mousePressEvent(QMouseEvent *event)
{
    m_pMoveItem = std::dynamic_pointer_cast<CurveCtrlOutPt>(m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypeCtrlOutPt));
}

void CurveMoveCtrlOutPtState::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pMoveItem)
    {
        auto pState = switchState(c_nStateNormal);
        pState->mousePressEvent(event);
        return;
    }

    QPointF centerPos = m_pMoveItem->getCenterPoint()->getPos();
    double dTan = (centerPos.y() - event->pos().y()) / (event->pos().x() - centerPos.x());
    m_pMoveItem->setTan(dTan);

}

void CurveMoveCtrlOutPtState::mouseReleaseEvent(QMouseEvent *event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
}
