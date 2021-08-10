#ifndef CURVEMANAGER_H
#define CURVEMANAGER_H

#include <QQuickPaintedItem>
#include <QTimer>

#include "CurveMouseKeyInfo.h"

class CurveStateMachine;
class CurveViewer;
class CurveService;
class CurveModel;
class CurveBox2D;
class CurveNotifier;
class CurveNotifyData;
class CurveSceneData;
class CurvePaintItem;
class CurveManager : public QQuickPaintedItem
{
    Q_OBJECT
public:
    CurveManager(QQuickItem* parent = nullptr);

    Q_INVOKABLE void init();
    Q_INVOKABLE void keyPressed(QObject* event);
    Q_INVOKABLE void keyReleased(QObject* event);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void touchEvent(QTouchEvent *event) override;

    virtual void beforePaint(QPainter *painter);
    void paint(QPainter *painter) override;
    virtual void afterPaint(QPainter *painter);
    virtual double getDevicePixelRatio();
    void doPaint(QPainter *painter);

    void initBackGroundLine();
    void initBackGroundNum();
    void initKeyPoint();

    std::shared_ptr<CurveBaseMouseInfo> convertMouseEvent(QWheelEvent* event, bool isFirstWheel);
    std::shared_ptr<CurveBaseMouseInfo> convertMouseEvent(QMouseEvent* event);
    std::shared_ptr<CurveBaseHoverInfo> convertHoverEvent(QHoverEvent* event);
    std::shared_ptr<CurveBaseWheelInfo> convertWheelEvent(QWheelEvent* event);
    std::shared_ptr<CurveBaseKeyInfo> convertKeyEvent(QObject* obj);

    virtual void adjustSceneByWheelEvent(QWheelEvent *event);
    virtual void adjustSceneByKeyPress(std::shared_ptr<CurveBaseKeyInfo> pKeyInfo);

protected:
    void addPt(double dValueX, double dValueY, double dTan);
    void paintLine(QPainter *painter);
    void paintNumber(QPainter *painter);
    void checkOffsetValid(QPointF& offset);
    void adjustPositionWhenScale();

protected:
    std::shared_ptr<CurveStateMachine> m_pStateMachine;
    std::shared_ptr<CurveViewer> m_pViewer;
    std::shared_ptr<CurveService> m_pService;
    std::shared_ptr<CurveModel> m_pModel;
    std::shared_ptr<CurveBox2D> m_pBox2D;
    std::shared_ptr<CurveNotifier> m_pNotifier;
    std::shared_ptr<CurveSceneData> m_pSceneData;

signals:
    void sigForceFocus();

protected slots:
    void onTouchScaleTimerTrigger() { m_dLastScaleLength = -1; }

private:
    QVector<std::shared_ptr<CurvePaintItem>> m_LineItemVec;
    QVector<std::shared_ptr<CurvePaintItem>> m_NumberItemVec;

    std::once_flag m_touchOnceFlag;
    double m_dLastScaleLength = -1.0;
    QTimer m_scaleTimer;

    //触摸板双指移动
    bool m_isMoving = false;
    QPoint m_lastTrackpadMovePos;
    QPoint m_lastTrackpadMoveGlobalPos;
};

#endif // CURVEMANAGER_H
