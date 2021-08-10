#include "CurveMoveCenterPtState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "CurveDefines.h"
#include "Item/CurvePt.h"

#include <QDebug>

void CurveMoveCenterPtState::mousePressEvent(CurveBaseMouseInfo::ptr event)
{
    m_pMoveItem = std::dynamic_pointer_cast<CurvePt>(m_pService->getBox2D()->getHitItemByType(event->scenePos, c_nModelTypePoint));
    m_pMoveItem->setSelected(true);
    m_lastPt = event->scenePos;
}

void CurveMoveCenterPtState::mouseMoveEvent(CurveBaseMouseInfo::ptr event)
{
    if (!m_pMoveItem)
    {
        auto pState = switchState(c_nStateNormal);
        pState->mousePressEvent(event);
        return;
    }

    auto dir = event->scenePos - m_lastPt;
    QPointF setPos = m_pMoveItem->getPos() + dir;
    //0和1的极值问题
    double leftPosX = getPosX(0);
    double rightPosX = getPosX(1);
    if (setPos.x() < leftPosX || event->scenePos.x() < leftPosX)
        setPos.setX(leftPosX);
    if (setPos.x() > rightPosX || event->scenePos.x() > rightPosX)
        setPos.setX(rightPosX);

    m_pMoveItem->setPos(setPos);
    m_lastPt = setPos;
    checkIsOutOfRange(setPos);
}

void CurveMoveCenterPtState::mouseReleaseEvent(CurveBaseMouseInfo::ptr event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
}

void CurveMoveCenterPtState::checkIsOutOfRange(QPointF point)
{
    auto pModel = m_pService->getModel();
    int currentIndex = pModel->getIndex(c_nModelTypePoint, m_pMoveItem);
    int size = pModel->getSize(c_nModelTypePoint);

    //左边界
    if (currentIndex > 0)
    {
        auto pLeftPtItem = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, currentIndex - 1);
        double dLeftX = pLeftPtItem->getPos().x();
        if (point.x() < dLeftX)
        {
            double dTan = m_pMoveItem->getTan();
            insertPt(currentIndex - 1, getValueX(point.x()), getValueY(point.y()), dTan);
            m_pMoveItem = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, currentIndex - 1);
            auto pDeleteItem = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, currentIndex + 1);
            deletePt(pDeleteItem);
        }
    }
    //右边界
    if (currentIndex < size - 1)
    {
        auto pRightPtItem = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, currentIndex + 1);
        double dRightX = pRightPtItem->getPos().x();
        if (point.x() > dRightX)
        {
            double dTan = m_pMoveItem->getTan();
            insertPt(currentIndex + 2, getValueX(point.x()), getValueY(point.y()), dTan);
            m_pMoveItem = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, currentIndex + 2);
            auto pDeleteItem = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, currentIndex);
            deletePt(pDeleteItem);
        }
    }
}

void CurveMoveCenterPtState::onStart()
{
    int size = m_pService->getModel()->getSize(c_nModelTypePoint);
    for (int i = 0; i < size; ++i)
    {
        auto pItem = m_pService->getModel()->getTypicalItem<CurvePt>(c_nModelTypePoint, i);
        pItem->setSelected(false);
    }
}
