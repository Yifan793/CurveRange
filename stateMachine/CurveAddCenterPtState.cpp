#include "CurveAddCenterPtState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "Item/CurvePt.h"
#include "Item/CurveCtrlPt.h"
#include "Item/CurvePtCtrlLine.h"
#include "notifier/CurveNotifier.h"

#include <QDebug>

void CurveAddCenterPtState::mousePressEvent(CurveBaseMouseInfo::ptr event)
{

}

void CurveAddCenterPtState::mouseMoveEvent(CurveBaseMouseInfo::ptr event)
{

}

void CurveAddCenterPtState::mouseReleaseEvent(CurveBaseMouseInfo::ptr event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
}

void CurveAddCenterPtState::mouseDoubleClickEvent(CurveBaseMouseInfo::ptr event)
{
    auto pItem = m_pService->getBox2D()->getHitItemByType(event->scenePos, c_nModelTypeCtrlLine);
    if (!pItem)
        return;
    auto pCtrlLineItem = std::dynamic_pointer_cast<CurvePtCtrlLine>(pItem);
    auto pModel = m_pService->getModel();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    double dX = getValueX(event->scenePos.x());
    double posY = pCtrlLineItem->getY(event->scenePos); //y值通过计算得到
    double dY = getValueY(posY);
    int index = m_pService->getModel()->getIndex(c_nModelTypeCtrlLine, pCtrlLineItem) + 1;
    insertPt(index, dX, dY, pCtrlLineItem->getTan(event->scenePos));
}
