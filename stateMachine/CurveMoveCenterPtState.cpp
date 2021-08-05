#include "CurveMoveCenterPtState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "CurveDefines.h"
#include "Item/CurvePt.h"

#include <QDebug>

void CurveMoveCenterPtState::mousePressEvent(QMouseEvent *event)
{
    m_pMoveItem = std::dynamic_pointer_cast<CurvePt>(m_pService->getBox2D()->getHitItemByType(event->pos(), c_nModelTypePoint));
    m_pMoveItem->setSelected(true);
    m_lastPt = event->pos();
}

void CurveMoveCenterPtState::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pMoveItem)
    {
        auto pState = switchState(c_nStateNormal);
        pState->mousePressEvent(event);
        return;
    }

    auto dir = event->pos() - m_lastPt;
    m_pMoveItem->setPos(m_pMoveItem->getPos() + dir);
    m_lastPt = event->pos();
}

void CurveMoveCenterPtState::mouseReleaseEvent(QMouseEvent *event)
{
    auto pState = switchState(c_nStateNormal);
    pState->mouseReleaseEvent(event);
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

QPointF CurveMoveCenterPtState::getValueByPos(QPointF pos)
{
    //songyifan TODO 计算简单一点，有必要时把边界去掉
    //给一个类似于模特图的范围，看一下整体的点位是怎么移动的
    auto pResInfoItem = m_pService->getModel()->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    double nWidth = pResInfoItem->getWindowWidth() - lineBorderLeft - lineBorderRight;
    double valueX = (pos.x() - lineBorderLeft) * (pResInfoItem->getMaxX() - pResInfoItem->getMinX()) / nWidth + pResInfoItem->getMinX();
    double nHeight = pResInfoItem->getWindowHeight() - lineBorderTop - lineBorderBottom;
    double valueY = (pResInfoItem->getWindowHeight() - lineBorderBottom - pos.y()) / nHeight * (pResInfoItem->getMaxY() - pResInfoItem->getMinY()) + pResInfoItem->getMinY();
    qDebug() << "test valueX " << valueX << " " <<  valueY;
    return QPointF(valueX, valueY);
}
