#include "CurveManager.h"
#include "stateMachine/CurveStateMachine.h"
#include "viewer/CurveViewer.h"
#include "service/CurveService.h"
#include "service/CurveBox2D.h"
#include "Item/CurveModel.h"
#include "CurveDefines.h"
#include "Item/CurveResInfoItem.h"
#include "Item/CurveLine.h"
#include "Item/CurveBackGround.h"
#include "Item/CurveNumber.h"
#include "Item/CurvePt.h"
#include "Item/CurveCtrlPt.h"
#include "Item/CurvePtCtrlLine.h"

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

    m_pNotifier = std::make_shared<CurveNotifier>();
    m_pService->setNotifier(m_pNotifier);

    m_pViewer = std::make_shared<CurveViewer>();
    m_pService->setViewer(m_pViewer);

    m_pStateMachine = std::make_shared<CurveStateMachine>(m_pService);
    m_pStateMachine->init();

    m_pBox2D = std::make_shared<CurveBox2D>();
    m_pService->setBox2D(m_pBox2D);

    m_pModel = std::make_shared<CurveModel>(m_pViewer, m_pBox2D);
    m_pService->setModel(m_pModel);

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

void CurveManager::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "test mouseDoubleClickEvent CurveManager 2222222222 ";
    if (!m_pStateMachine)
        return;
    m_pStateMachine->mouseDoubleClickEvent(event);
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
        m_pModel->addItem(c_nModelTypeNumber, pLineXItem);
    }

    for (int j = 1; j < nCountY - 1; ++j)
    {
        auto pLineYItem = std::make_shared<CurveNumber>(0, j / 10.0, pResInfoItem);
        m_pModel->addItem(c_nModelTypeNumber, pLineYItem);
    }
}

void CurveManager::initKeyPoint()
{
    addPt(0, 0, 0.07);
    addPt(0.7, 0.3, 1.30);
//    addPt(1.0, 0.9, 2.52);

    int nPtSize = m_pModel->getSize(c_nModelTypePoint);
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    for (int i = 0; i < nPtSize - 1; ++i)
    {
        auto pCurveBeginPt = m_pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, i);
        auto pCurveEndPt = m_pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, i + 1);
        auto pCurveLeftCtrlPt = m_pModel->getTypicalItem<CurveCtrlOutPt>(c_nModelTypeCtrlOutPt, i);
        auto pCurveRightCtrlPt = m_pModel->getTypicalItem<CurveCtrlInPt>(c_nModelTypeCtrlInPt, i + 1);
        auto pCurveLine = std::make_shared<CurvePtCtrlLine>(pCurveBeginPt, pCurveEndPt, pCurveLeftCtrlPt, pCurveRightCtrlPt);
        pCurveLine->setResInfoItem(pResInfoItem);
        m_pModel->addItem(c_nModelTypeCtrlLine, pCurveLine);
    }
}

void CurveManager::addPt(double dValueX, double dValueY, double dTan)
{
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    auto pCurvePt = std::make_shared<CurvePt>(dValueX, dValueY, dTan, pResInfoItem);
    pCurvePt->setNotifier(m_pNotifier);
    m_pModel->addItem(c_nModelTypePoint, pCurvePt);
    auto pCtrlInPt = std::make_shared<CurveCtrlInPt>(pCurvePt);
    m_pModel->addItem(c_nModelTypeCtrlInPt, pCtrlInPt);
    auto pCtrloutPt = std::make_shared<CurveCtrlOutPt>(pCurvePt);
    m_pModel->addItem(c_nModelTypeCtrlOutPt, pCtrloutPt);
}



