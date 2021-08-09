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

    qDebug() << "test CurveAddCenterPtState " << event->pos();
    auto pModel = m_pService->getModel();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    double dX = (event->pos().x() - lineBorderLeft) / (pResInfoItem->getWindowWidth() - lineBorderLeft - lineBorderRight);
    double posY = pCtrlLineItem->getY(event->pos()); //y值通过计算得到
    double dY = (pResInfoItem->getWindowHeight() - posY - lineBorderBottom) / (pResInfoItem->getWindowHeight() - lineBorderTop - lineBorderBottom);

    int index = m_pService->getModel()->getIndex(c_nModelTypeCtrlLine, pCtrlLineItem);
//    double dTan =
    qDebug() << "test dTan " << pCtrlLineItem->getTan(event->pos());
    qDebug() << "test dx dY " << dX << dY;
    addPt(index, dX, dY, pCtrlLineItem->getTan(event->pos()));
//    auto pState = switchState(c_nStateNormal);
//    pState->mouseReleaseEvent(event);
}

void CurveAddCenterPtState::addPt(int index, double dValueX, double dValueY, double dTan)
{
    auto pModel = m_pService->getModel();
    auto pNotifier = m_pService->getNotifier();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    auto pCurvePt = std::make_shared<CurvePt>(dValueX, dValueY, dTan, pResInfoItem);
    pCurvePt->setNotifier(pNotifier);
    pModel->insertItem(index, c_nModelTypePoint, pCurvePt);
    auto pCtrlInPt = std::make_shared<CurveCtrlInPt>(pCurvePt);
    pModel->insertItem(index, c_nModelTypeCtrlInPt, pCtrlInPt);
    auto pCtrloutPt = std::make_shared<CurveCtrlOutPt>(pCurvePt);
    pModel->insertItem(index, c_nModelTypeCtrlOutPt, pCtrloutPt);
}
