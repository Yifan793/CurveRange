#include "CurveAddCenterPtState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "Item/CurvePt.h"
#include "Item/CurveCtrlPt.h"
#include "Item/CurvePtCtrlLine.h"
#include "notifier/CurveNotifier.h"

#include <QDebug>

void CurveAddCenterPtState::mousePressEvent(QMouseEvent *event)
{

}

void CurveAddCenterPtState::mouseMoveEvent(QMouseEvent *event)
{

}

void CurveAddCenterPtState::mouseReleaseEvent(QMouseEvent *event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
}

void CurveAddCenterPtState::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto pItem = m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypeCtrlLine);
    if (!pItem)
        return;
    auto pCtrlLineItem = std::dynamic_pointer_cast<CurvePtCtrlLine>(pItem);
    auto pModel = m_pService->getModel();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    double dX = getValueX(event->pos().x());
    double posY = pCtrlLineItem->getY(event->pos()); //y值通过计算得到
    double dY = getValueY(posY);
    int index = m_pService->getModel()->getIndex(c_nModelTypeCtrlLine, pCtrlLineItem) + 1;
    insertPt(index, dX, dY, pCtrlLineItem->getTan(event->pos()));
}
