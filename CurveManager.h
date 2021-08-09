#ifndef CURVEMANAGER_H
#define CURVEMANAGER_H

#include <QQuickPaintedItem>

class CurveStateMachine;
class CurveViewer;
class CurveService;
class CurveModel;
class CurveBox2D;
class CurveNotifier;
class CurveNotifyData;
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
    void paint(QPainter *painter) override;
    void doPaint(QPainter *painter);

    void initBackGroundLine();
    void initBackGroundNum();
    void initKeyPoint();

protected:
    void addPt(double dValueX, double dValueY, double dTan);

protected:
    std::shared_ptr<CurveStateMachine> m_pStateMachine;
    std::shared_ptr<CurveViewer> m_pViewer;
    std::shared_ptr<CurveService> m_pService;
    std::shared_ptr<CurveModel> m_pModel;
    std::shared_ptr<CurveBox2D> m_pBox2D;
    std::shared_ptr<CurveNotifier> m_pNotifier;
};

#endif // CURVEMANAGER_H
