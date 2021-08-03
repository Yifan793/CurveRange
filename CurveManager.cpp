#include "CurveManager.h"
#include "stateMachine/CurveStateMachine.h"
#include "viewer/CurveViewer.h"
#include "service/CurveService.h"
#include "Item/CurveModel.h"

#include <QPainter>

CurveManager::CurveManager(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAcceptedMouseButtons((Qt::LeftButton | Qt::RightButton));
    setAcceptTouchEvents(true);
}

void CurveManager::init()
{
    setAcceptHoverEvents(true);
    m_pService = std::make_shared<CurveService>();

    m_pViewer = std::make_shared<CurveViewer>();
    m_pService->setViewer(m_pViewer);

    m_pStateMachine = std::make_shared<CurveStateMachine>(m_pService);
    m_pStateMachine->init();

    m_pModel = std::make_shared<CurveModel>(m_pViewer);
//    m_pModel->addItem()
}

void CurveManager::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!m_pStateMachine)
            return;
        m_pStateMachine->mousePressEvent(event);
    }
    update();
}

void CurveManager::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pStateMachine)
        return;
    m_pStateMachine->mouseMoveEvent(event);
    update();
}

void CurveManager::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_pStateMachine)
        return;
    m_pStateMachine->mouseReleaseEvent(event);
    update();
}

void CurveManager::paint(QPainter *painter)
{
    if (!painter)
        return;

    painter->setRenderHint(QPainter::Antialiasing);
    doPaint(painter);
}

void CurveManager::doPaint(QPainter *painter)
{
    m_pViewer->paint(painter);
}




