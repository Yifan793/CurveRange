#include "CurveState.h"

#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "Item/CurvePt.h"
#include "Item/CurveCtrlPt.h"
#include "Item/CurvePtCtrlLine.h"

#include <QDebug>

CurveState::CurveState()
{

}

void CurveState::insertPt(int index, double dValueX, double dValueY, double dTan)
{
    auto pModel = m_pService->getModel();
    auto pNotifier = m_pService->getNotifier();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    int nPointSize = pModel->getSize(c_nModelTypePoint);

    //增加三个点
    auto pCurvePt = std::make_shared<CurvePt>(dValueX, dValueY, dTan, pResInfoItem);
    pCurvePt->setNotifier(pNotifier);
    pCurvePt->setSelected(true);
    pModel->insertItem(index, c_nModelTypePoint, pCurvePt);
    auto pCtrlInPt = std::make_shared<CurveCtrlInPt>(pCurvePt);
    pModel->insertItem(index, c_nModelTypeCtrlInPt, pCtrlInPt);
    auto pCtrloutPt = std::make_shared<CurveCtrlOutPt>(pCurvePt);
    pModel->insertItem(index, c_nModelTypeCtrlOutPt, pCtrloutPt);

    //增加两条曲线
    for (int i = 0; i < 2; i++)
    {
        if ((index + i - 1) < 0 || (index + i - 1) > nPointSize - 1) //起始点和终止点只需增加一条曲线
            continue;
        auto pCurveBeginPt = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, index + i - 1);
        auto pCurveEndPt = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, index + i);
        auto pCurveLeftCtrlPt = pModel->getTypicalItem<CurveCtrlOutPt>(c_nModelTypeCtrlOutPt, index + i - 1);
        auto pCurveRightCtrlPt = pModel->getTypicalItem<CurveCtrlInPt>(c_nModelTypeCtrlInPt, index + i);
        auto pCurveLine = std::make_shared<CurvePtCtrlLine>(pCurveBeginPt, pCurveEndPt, pCurveLeftCtrlPt, pCurveRightCtrlPt);
        pCurveLine->setResInfoItem(pResInfoItem);
        pModel->insertItem(index + i - 1, c_nModelTypeCtrlLine, pCurveLine);
    }

    //删除一条曲线
    if (index > 0 && index < nPointSize) //起始点和终止点无需删除曲线
    {
        auto pDeleteItem = pModel->getTypicalItem<CurvePtCtrlLine>(c_nModelTypeCtrlLine, index + 1);
        pModel->removeItem(c_nModelTypeCtrlLine, pDeleteItem);
    }
}

void CurveState::deletePt(std::shared_ptr<CurvePt> pItem)
{
    auto pModel = m_pService->getModel();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    int nPointSize = pModel->getSize(c_nModelTypePoint);
    int deleteIndex = pModel->getIndex(c_nModelTypePoint, pItem);

    //增加一条曲线
    if (deleteIndex > 0 && deleteIndex < nPointSize - 1) //起始和终止点无需增加曲线
    {
        auto pCurveBeginPt = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, deleteIndex - 1);
        auto pCurveEndPt = pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, deleteIndex + 1);
        auto pCurveLeftCtrlPt = pModel->getTypicalItem<CurveCtrlOutPt>(c_nModelTypeCtrlOutPt, deleteIndex - 1);
        auto pCurveRightCtrlPt = pModel->getTypicalItem<CurveCtrlInPt>(c_nModelTypeCtrlInPt, deleteIndex + 1);
        auto pCurveLine = std::make_shared<CurvePtCtrlLine>(pCurveBeginPt, pCurveEndPt, pCurveLeftCtrlPt, pCurveRightCtrlPt);
        pCurveLine->setResInfoItem(pResInfoItem);
        pModel->insertItem(deleteIndex, c_nModelTypeCtrlLine, pCurveLine);
    }

    //删除两条曲线
    if (deleteIndex > 0) //起始点无需删除左曲线
    {
        auto pCtrlLeftLine = pModel->getTypicalItem<CurvePtCtrlLine>(c_nModelTypeCtrlLine, deleteIndex - 1);
        pModel->removeItem(c_nModelTypeCtrlLine, pCtrlLeftLine);
    }
    if (deleteIndex < nPointSize - 1) //终止点无需删除右曲线
    {
        auto pCtrlRightLine = pModel->getTypicalItem<CurvePtCtrlLine>(c_nModelTypeCtrlLine, deleteIndex);
        pModel->removeItem(c_nModelTypeCtrlLine, pCtrlRightLine);
    }

    //删除三个点
    pModel->removeItem(c_nModelTypePoint, pItem);
    auto pCtrlInPt = pModel->getTypicalItem<CurveCtrlInPt>(c_nModelTypeCtrlInPt, deleteIndex);
    auto pCtrlOutPt = pModel->getTypicalItem<CurveCtrlOutPt>(c_nModelTypeCtrlOutPt, deleteIndex);
    pModel->removeItem(c_nModelTypeCtrlInPt, pCtrlInPt);
    pModel->removeItem(c_nModelTypeCtrlOutPt, pCtrlOutPt);
}

double CurveState::getValueX(double posX) const
{
    auto pModel = m_pService->getModel();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    double dWidth = pResInfoItem->getWindowWidth() - lineBorderLeft - lineBorderRight;
    return (posX - lineBorderLeft) / dWidth;
}

double CurveState::getValueY(double posY) const
{
    auto pModel = m_pService->getModel();
    auto pResInfoItem = pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    double dHeight = pResInfoItem->getWindowHeight() - lineBorderTop - lineBorderBottom;
    return (pResInfoItem->getWindowHeight() - posY - lineBorderBottom) / dHeight;
}
