#include "CurveStateMachine.h"
#include "CurveState.h"
#include "stateMachine/CurveNormalState.h"
#include "stateMachine/CurveMoveCenterPtState.h"
#include "stateMachine/CurveMoveCtrlPtState.h"

#include "CurveDefines.h"

CurveStateMachine::CurveStateMachine(std::shared_ptr<CurveService> pService)
    : m_pService(pService)
{

}

void CurveStateMachine::init()
{
    registState(c_nStateNormal, std::make_shared<CurveNormalState>());
    registState(c_nStateMoveCenterPt, std::make_shared<CurveMoveCenterPtState>());
    registState(c_nStateMoveCtrlInPt, std::make_shared<CurveMoveCtrlInPtState>());
    registState(c_nStateMoveCtrlOutPt, std::make_shared<CurveMoveCtrlOutPtState>());

    switchState(c_nStateNormal);
}

std::shared_ptr<CurveState> CurveStateMachine::switchState(int nType)
{
    if (m_pCurState && m_pCurState->getStateType() == nType)
        return nullptr;
    auto it = m_stateMap.find(nType);
    if (it == m_stateMap.end())
        return nullptr;
    auto pState = it.value();
    if (m_pCurState)
        m_pCurState->onStop();
    m_pCurState = pState;
    m_pCurState->onStart();
    return m_pCurState;
}

void CurveStateMachine::mousePressEvent(QMouseEvent *event)
{
    m_pCurState->mousePressEvent(event);
}

void CurveStateMachine::mouseMoveEvent(QMouseEvent *event)
{
    m_pCurState->mouseMoveEvent(event);
}

void CurveStateMachine::mouseReleaseEvent(QMouseEvent *event)
{
    m_pCurState->mouseReleaseEvent(event);
}

void CurveStateMachine::registState(int nStateKey, std::shared_ptr<CurveState> pState)
{
    pState->setStateType(nStateKey);
    pState->setService(m_pService);
    pState->setSwitchFunc(std::bind(&CurveStateMachine::switchState, this, std::placeholders::_1));
    m_stateMap[nStateKey] = pState;
}
