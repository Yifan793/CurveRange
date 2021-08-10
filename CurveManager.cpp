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
#include "util/CurveUtil.h"
#include "util/MathUtil.h"
#include "CurveSceneData.h"

#include <QPainter>
#include <QQuickWindow>

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

    m_pSceneData = std::make_shared<CurveSceneData>();

    auto pResInfoItem = std::make_shared<CurveResInfoItem>();
    m_pModel->addItem(c_nModelTypeResInfo, pResInfoItem);

    initBackGroundLine();
    initBackGroundNum();
    initKeyPoint();
}

void CurveManager::keyPressed(QObject *event)
{
    auto pKeyInfo = convertKeyEvent(event);
    adjustSceneByKeyPress(pKeyInfo);
    if (!m_pStateMachine)
        return;
    auto pInfo = convertKeyEvent(event);
    m_pStateMachine->keyPressEvent(pInfo);
    update();
}

void CurveManager::keyReleased(QObject *event)
{
    if (!m_pStateMachine)
        return;
    auto pInfo = convertKeyEvent(event);
    m_pStateMachine->keyReleaseEvent(pInfo);
    update();
}

void CurveManager::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!m_pStateMachine)
            return;
        m_pStateMachine->mousePressEvent(convertMouseEvent(event));
    }
    update();
}

void CurveManager::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_pStateMachine)
        return;
    m_pStateMachine->mouseMoveEvent(convertMouseEvent(event));
    update();
}

void CurveManager::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_pStateMachine)
        return;
    m_pStateMachine->mouseReleaseEvent(convertMouseEvent(event));
    update();
}

void CurveManager::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (!m_pStateMachine)
        return;
    m_pStateMachine->mouseDoubleClickEvent(convertMouseEvent(event));
    update();
}

void CurveManager::wheelEvent(QWheelEvent* event)
{
    if (event->source() == Qt::MouseEventSynthesizedBySystem)
    {
        // mac触摸板双指滑动
        static QTimer s_moveTimer;
        static std::once_flag s_onceFlag;
        std::call_once(s_onceFlag, [this] { //解决误触发双指轻触移动后，双指张合无效
            connect(&s_moveTimer, &QTimer::timeout, [this] { m_isMoving = false; });
        });

        if (!m_pStateMachine)
            return;

        switch(event->phase())
        {
        case Qt::ScrollUpdate:
            if (m_isMoving)
            {
                s_moveTimer.start(300);

                m_pStateMachine->mouseMoveEvent(convertMouseEvent(event, false));
                update();
            }
            break;
        case Qt::ScrollEnd:
            m_isMoving = false;
            s_moveTimer.stop();

            m_pStateMachine->mouseReleaseEvent(convertMouseEvent(event, false));
            update();
            break;
        default:
            if (!m_isMoving)
            {
                m_isMoving = true;
                s_moveTimer.start(300);

                emit sigForceFocus();
                m_pStateMachine->mousePressEvent(convertMouseEvent(event, true));
                update();
            }
            break;
        }
    }
    else
    {
        // 鼠标滚轮
        adjustSceneByWheelEvent(event);
        if (!m_pStateMachine)
            return;
        m_pStateMachine->wheelEvent(convertWheelEvent(event));
        update();
    }
}

//双指缩放
void CurveManager::touchEvent(QTouchEvent *event)
{
    std::call_once(m_touchOnceFlag, [&] {
        m_scaleTimer.setInterval(100);
        m_scaleTimer.setSingleShot(true);
        connect(&m_scaleTimer, &QTimer::timeout, this, &CurveManager::onTouchScaleTimerTrigger);
    });


    auto mousePos = QCursor::pos();
    auto mapPos = mapFromGlobal(mousePos);

    if (mapPos.x() > 0 && mapPos.x() < width() && mapPos.y() > 0 && mapPos.y() < height())
    {
        auto oriScenePt = CurveUtil::mapToScene(mapPos, m_pSceneData->offset, m_pSceneData->dScale);
        QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

        if (!m_isMoving && touchPoints.size() == 2) //双指操作进行缩放
        {
            m_scaleTimer.start();
            const auto& firstPt = touchPoints.first();
            const auto& secondPt = touchPoints.last();
            QLineF line(firstPt.pos(), secondPt.pos());
            double length = line.length();
            if (MathUtil::compare(m_dLastScaleLength, -1) == 0)
            {
                m_dLastScaleLength = length;
            }
            else
            {
                double dOriScale = m_pSceneData->dScale;
                float s = length / m_dLastScaleLength;
                if (MathUtil::compare(s, 1.0 , 0.05) == 0)
                {
                    return;
                }
                m_dLastScaleLength = length;
                double dCurScale = m_pSceneData->dScale * s;
                dCurScale = std::max(m_pSceneData->dMinScale, dCurScale);
                dCurScale = std::min(m_pSceneData->dMaxScale, dCurScale);
                if (MathUtil::compare(dCurScale, dOriScale) != 0)
                {
                    m_pSceneData->dScale = dCurScale;
                    auto afterMapPt = CurveUtil::sceneToMap(oriScenePt, m_pSceneData->offset, m_pSceneData->dScale);
                    m_pSceneData->offset -= (afterMapPt - mapPos);
                    update();
                }
            }
        }
    }
}

void CurveManager::beforePaint(QPainter *painter)
{
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    pResInfoItem->setWindowWidth(static_cast<int>(width()));
    pResInfoItem->setWindowHeight(static_cast<int>(height()));

    //由于曲线比关键点先绘制，所以先更新曲线关键点位置
    for (int i = 0; i < m_pModel->getSize(c_nModelTypePoint); i++)
    {
        auto pPointItem = m_pModel->getTypicalItem<CurvePt>(c_nModelTypePoint, i);
        pPointItem->setPos(QPointF(pPointItem->getPositionX(), pPointItem->getPositionY()));
    }

    //背景直线
    paintLine(painter);
}

void CurveManager::afterPaint(QPainter *painter)
{
    //背景数字
    paintNumber(painter);
}

void CurveManager::paint(QPainter *painter)
{
    if (!painter)
        return;

    painter->setRenderHint(QPainter::Antialiasing);
    beforePaint(painter);

    auto& offset = m_pSceneData->offset;
    auto nPixelRatio = getDevicePixelRatio();
    auto dScale = m_pSceneData->dScale;

    QTransform transform;
    transform = transform.translate(offset.x() * nPixelRatio, offset.y() * nPixelRatio);
    transform = transform.scale(dScale * nPixelRatio, dScale * nPixelRatio);
    painter->setTransform(transform);

    auto& sceneRect = m_pSceneData->sceneRect;
    QRectF windowRect(0, 0, m_pSceneData->nWindowWidth * nPixelRatio, m_pSceneData->nWindowHeight * nPixelRatio);
    sceneRect = CurveUtil::mapToScene(windowRect, offset, dScale);

    m_pSceneData->nWindowWidth = static_cast<int>(width());
    m_pSceneData->nWindowHeight = static_cast<int>(height());

    doPaint(painter);
    afterPaint(painter);
}

double CurveManager::getDevicePixelRatio()
{
    return this->window()->devicePixelRatio();
    //return FCTransfer::instance()->pWindow->topLevelWidget()->windowHandle()->devicePixelRatio(); 双屏下有这个公式
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
        auto pLineXItem = std::make_shared<CurveLineX>(i / 10.0, 0, pResInfoItem, m_pSceneData);
        m_LineItemVec.append(pLineXItem);
    }

    for (int j = 0; j < nLineCountY; ++j)
    {
        auto pLineYItem = std::make_shared<CurveLineY>(0, j / 10.0, pResInfoItem, m_pSceneData);
        m_LineItemVec.append(pLineYItem);
    }
}

void CurveManager::initBackGroundNum()
{
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);
    int nCountX = pResInfoItem->getNumCountX();
    int nCountY = pResInfoItem->getNumCountY();
    for (int i = 0; i < nCountX; ++i)
    {
        auto pLineXItem = std::make_shared<CurveNumber>(i / 10.0, 0, pResInfoItem, m_pSceneData);
        m_NumberItemVec.append(pLineXItem);
    }

    for (int j = 1; j < nCountY - 1; ++j)
    {
        auto pLineYItem = std::make_shared<CurveNumber>(0, j / 10.0, pResInfoItem, m_pSceneData);
        m_NumberItemVec.append(pLineYItem);
    }
}

void CurveManager::initKeyPoint()
{
    addPt(0, 0, 0.07);
    addPt(0.7, 0.3, 1.30);
    addPt(1.0, 0.9, 2.52);

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

void CurveManager::paintLine(QPainter *painter)
{
    auto nPixelRatio = getDevicePixelRatio();
    for (auto &item : m_LineItemVec)
    {
        item->setPixelRatio(nPixelRatio);
        item->paint(painter);
    }
}

void CurveManager::paintNumber(QPainter *painter)
{
    auto nPixelRatio = getDevicePixelRatio();
    for (auto &item : m_NumberItemVec)
    {
        item->setPixelRatio(nPixelRatio);
        item->paint(painter);
    }
}

void CurveManager::checkOffsetValid(QPointF& offset)
{
    double dScale = m_pSceneData->dScale;
    auto pResInfoItem = m_pModel->getTypicalItem<CurveResInfoItem>(c_nModelTypeResInfo, 0);

    //左边界不能大于lineBorderLeft x是0
    if ((lineBorderLeft * dScale + offset.x()) > lineBorderLeft)
    {
        offset.setX(lineBorderLeft * (1 - dScale));
    }
    //右边界不能小于pResInfoItem->getWindowWidth() - lineBorderRight x是1
    if (((pResInfoItem->getWindowWidth() - lineBorderRight) * (dScale - 1) + offset.x()) < 0)
    {
        offset.setX((pResInfoItem->getWindowWidth() - lineBorderRight) * (1 - dScale));
    }

    //下边界不能小于pResInfoItem->getWindowHeight() - lineBorderBottom y是0
    if (((pResInfoItem->getWindowHeight() - lineBorderBottom) * (dScale - 1) + offset.y()) < 0)
    {
        offset.setY((pResInfoItem->getWindowHeight() - lineBorderBottom) * (1 - dScale));
    }
    //上边界不能大于lineBorderTop y是1
    if ((lineBorderTop * dScale + offset.y()) > lineBorderTop)
    {
        offset.setY(lineBorderTop * (1 - dScale));
    }
}

//限定显示范围
void CurveManager::adjustPositionWhenScale()
{
    QPointF offset = m_pSceneData->offset;
    checkOffsetValid(offset);
    m_pSceneData->offset.setX(offset.x());
    m_pSceneData->offset.setY(offset.y());
}

std::shared_ptr<CurveBaseMouseInfo> CurveManager::convertMouseEvent(QWheelEvent* event, bool isFirstWheel)
{
    if (isFirstWheel)
    {
        m_lastTrackpadMovePos = event->pos();
        m_lastTrackpadMoveGlobalPos = event->globalPos();
    }
    else
    {
        m_lastTrackpadMovePos += event->pixelDelta();
        m_lastTrackpadMoveGlobalPos += event->pixelDelta();
    }
    auto pInfo = std::make_shared<CurveBaseMouseInfo>();
    pInfo->globalPos = m_lastTrackpadMoveGlobalPos;
    pInfo->mapPos = m_lastTrackpadMovePos;
    pInfo->scenePos = CurveUtil::mapToScene(pInfo->mapPos, m_pSceneData->offset, m_pSceneData->dScale);
    return pInfo;
}
std::shared_ptr<CurveBaseMouseInfo> CurveManager::convertMouseEvent(QMouseEvent* event)
{
    auto pInfo = std::make_shared<CurveBaseMouseInfo>();
    pInfo->globalPos = event->globalPos();
    pInfo->mapPos = event->pos();
    pInfo->scenePos = CurveUtil::mapToScene(pInfo->mapPos, m_pSceneData->offset, m_pSceneData->dScale);
    return pInfo;
}
std::shared_ptr<CurveBaseHoverInfo> CurveManager::convertHoverEvent(QHoverEvent* event)
{
    auto pInfo = std::make_shared<CurveBaseHoverInfo>();
    pInfo->mapPos = event->pos();
    pInfo->oriMapPos = event->oldPos();
    pInfo->scenePos = CurveUtil::mapToScene(pInfo->mapPos, m_pSceneData->offset, m_pSceneData->dScale);
    pInfo->oriScenePos = CurveUtil::mapToScene(pInfo->oriMapPos, m_pSceneData->offset, m_pSceneData->dScale);
    return pInfo;
}
std::shared_ptr<CurveBaseWheelInfo> CurveManager::convertWheelEvent(QWheelEvent* event)
{
    auto pInfo = std::make_shared<CurveBaseWheelInfo>();
    QPointF mapPt(event->x(), event->y());
    pInfo->mMapPt = mapPt;
    pInfo->mScenePt = CurveUtil::mapToScene(mapPt, m_pSceneData->offset, m_pSceneData->dScale);
    pInfo->mModifiers = event->modifiers();
    pInfo->mAngleDelta = event->angleDelta();
    return pInfo;
}
std::shared_ptr<CurveBaseKeyInfo> CurveManager::convertKeyEvent(QObject* obj)
{
    auto pInfo = std::make_shared<CurveBaseKeyInfo>();
    pInfo->key = (Qt::Key)obj->property("key").toInt();
    pInfo->modifiers = obj->property("modifiers").toInt();
    m_pStateMachine->keyReleaseEvent(pInfo);
    return pInfo;
}

void CurveManager::adjustSceneByWheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();
    if (std::abs(delta.x()) < 100 && std::abs(delta.y()) < 100)
    {
        return;
    }

    auto pSceneData = m_pSceneData;
    auto globalPos = QCursor::pos();
    auto mapPt = mapFromGlobal(globalPos);
    double dCurScale = pSceneData->dScale;
    auto oriScenePt = CurveUtil::mapToScene(mapPt, m_pSceneData->offset, m_pSceneData->dScale);

    if (event->modifiers() == Qt::AltModifier)
    {
        //缩放
        auto dCurScale = m_pSceneData->dScale;
        if (delta.x() > 0 || delta.y() > 0)
        {
            if (dCurScale >= m_pSceneData->dMaxScale)
                return;
            pSceneData->dScale = std::min(pSceneData->dMaxScale, pSceneData->dScale * 1.05);
        }
        else
        {
            if (dCurScale <= m_pSceneData->dMinScale)
                return;
            pSceneData->dScale = std::max(pSceneData->dMinScale, pSceneData->dScale * 0.95);
        }
    }
    else
    {
        //移动
        int nBaseLen = pSceneData->nWindowWidth > pSceneData->nWindowHeight ? pSceneData->nWindowWidth : pSceneData->nWindowHeight;
        double dBaseRatio = 0.02;
        auto offset = nBaseLen * (delta.y() > 0 ? dBaseRatio : -dBaseRatio);
        if (event->modifiers() == Qt::ControlModifier)
        {
            QPointF setOffset = QPointF(pSceneData->offset.x() + offset, pSceneData->offset.y());
            checkOffsetValid(setOffset);
            pSceneData->offset.setX(setOffset.x());
        }
        else
        {
            QPointF setOffset = QPointF(pSceneData->offset.x(), pSceneData->offset.y() + offset);
            checkOffsetValid(setOffset);
            pSceneData->offset.setY(setOffset.y());
        }
    }

    if (MathUtil::compare(dCurScale, pSceneData->dScale) != 0)
    {
        auto afterMapPt = CurveUtil::sceneToMap(oriScenePt, m_pSceneData->offset, m_pSceneData->dScale);
        pSceneData->offset -= (afterMapPt - mapPt);
    }
    adjustPositionWhenScale();
}

void CurveManager::adjustSceneByKeyPress(std::shared_ptr<CurveBaseKeyInfo> pKeyInfo)
{
    auto pSceneData = m_pSceneData;
    if (pKeyInfo->modifiers & Qt::ControlModifier)
    {
        if (pKeyInfo->key == Qt::Key_Equal || pKeyInfo->key == Qt::Key_Plus)
        {
            if (pSceneData->dScale >= m_pSceneData->dMaxScale)
                return;
            pSceneData->dScale = std::min(m_pSceneData->dMaxScale, pSceneData->dScale * 1.05);
        }
        else if (pKeyInfo->key == Qt::Key_Minus)
        {
            if (pSceneData->dScale <= m_pSceneData->dMinScale)
                return;
            pSceneData->dScale = std::max(m_pSceneData->dMinScale, pSceneData->dScale * 0.95);
        }
    }
    adjustPositionWhenScale();
}
