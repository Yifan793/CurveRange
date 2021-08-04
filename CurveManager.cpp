#include "CurveManager.h"
#include "stateMachine/CurveStateMachine.h"
#include "viewer/CurveViewer.h"
#include "service/CurveService.h"
#include "Item/CurveModel.h"
#include "CurveDefines.h"
#include "Item/CurveResInfoItem.h"
#include "Item/CurveLine.h"
#include "Item/CurveBackGround.h"
#include "Item/CurveNumber.h"
#include "Item/CurvePt.h"

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

    auto pResInfoItem = std::make_shared<CurveResInfoItem>();
    m_pModel->addItem(c_nModelTypeResInfo, pResInfoItem);

    initBackGroundLine();
    initBackGroundNum();
    initKeyPoint();
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

void CurveManager::initBackGroundLine()
{
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    int nLineCountX = pResInfoItem->getLineCountX();
    int nLineCountY = pResInfoItem->getLineCountY();
    for (int i = 0; i < nLineCountX; ++i)
    {
        auto pLineXItem = std::make_shared<CurveLineX>(i / 10.0, 0, pResInfoItem);
        m_pModel->addItem(c_nModelTypeLine, pLineXItem);
    }

    for (int j = 0; j < nLineCountY; ++j)
    {
        auto pLineYItem = std::make_shared<CurveLineY>(0, j / 10.0, pResInfoItem);
        m_pModel->addItem(c_nModelTypeLine, pLineYItem);
    }
}

void CurveManager::initBackGroundNum()
{
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    int nCountX = pResInfoItem->getNumCountX();
    int nCountY = pResInfoItem->getNumCountY();
    for (int i = 0; i < nCountX; ++i)
    {
        auto pLineXItem = std::make_shared<CurveNumber>(i / 10.0, 0, pResInfoItem);
        m_pModel->addItem(c_nModelTypeLine, pLineXItem);
    }

    for (int j = 1; j < nCountY - 1; ++j)
    {
        auto pLineYItem = std::make_shared<CurveNumber>(0, j / 10.0, pResInfoItem);
        m_pModel->addItem(c_nModelTypeLine, pLineYItem);
    }
}

void CurveManager::initKeyPoint()
{
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    auto pCurvePt1 = std::make_shared<CurvePt>(0, 0, pResInfoItem);
    m_pModel->addItem(c_nModelTypePoint, pCurvePt1);

    auto pCurvePt2 = std::make_shared<CurvePt>(0.7, 0.3, pResInfoItem);
    m_pModel->addItem(c_nModelTypePoint, pCurvePt2);

    auto pCurvePt3 = std::make_shared<CurvePt>(1.0, 0.9, pResInfoItem);
    m_pModel->addItem(c_nModelTypePoint, pCurvePt3);
}



