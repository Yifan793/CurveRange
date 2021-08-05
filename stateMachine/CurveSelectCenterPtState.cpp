#include "CurveSelectCenterPtState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "CurveDefines.h"

//delete
void CurveSelectCenterPtState::mousePressEvent(QMouseEvent *event)
{
    auto pPointItem = m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypePoint);
    if (pPointItem)
    {
        auto pMoveCenterPtState = switchState(c_nStateMoveCenterPt);
        pMoveCenterPtState->mousePressEvent(event);
        return;
    }
}

void CurveSelectCenterPtState::mouseMoveEvent(QMouseEvent *event)
{

}

void CurveSelectCenterPtState::mouseReleaseEvent(QMouseEvent *event)
{

}
