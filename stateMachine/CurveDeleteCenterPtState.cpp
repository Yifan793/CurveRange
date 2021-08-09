#include "CurveDeleteCenterPtState.h"

#include "service/CurveService.h"
#include "Item/CurveModel.h"
#include "Item/CurvePt.h"
#include "Item/CurveCtrlPt.h"
#include "Item/CurvePtCtrlLine.h"

void CurveDeleteCenterPtState::keyPressEvent(EditorCtrlKeyInfo::ptr event)
{
    QVector<std::shared_ptr<CurvePt>> deletePtVec;
    int ptCount = m_pService->getModel()->getSize(c_nModelTypePoint);
    for (int i = 0; i < ptCount; i++)
    {
        auto pPointItem = m_pService->getModel()->getTypicalItem<CurvePt>(c_nModelTypePoint, i);
        if (pPointItem->getSelected())
        {
            deletePtVec.push_back(pPointItem);
        }
    }
    for (auto pDeleteItem : deletePtVec)
    {
        deletePt(pDeleteItem);
    }
}

void CurveDeleteCenterPtState::keyReleaseEvent(EditorCtrlKeyInfo::ptr event)
{
    auto pState = switchState(c_nStateNormal);
    pState->keyReleaseEvent(event);
}
