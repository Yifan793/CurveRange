#ifndef CURVEMANAGER_H
#define CURVEMANAGER_H

#include <QQuickPaintedItem>

class CurveStateMachine;
class CurveViewer;
class CurveService;
class CurveModel;
class CurveManager : public QQuickPaintedItem
{
    Q_OBJECT
public:
    CurveManager(QQuickItem* parent = nullptr);
    Q_INVOKABLE void init();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paint(QPainter *painter) override;
    void doPaint(QPainter *painter);

protected:
    std::shared_ptr<CurveStateMachine> m_pStateMachine;
    std::shared_ptr<CurveViewer> m_pViewer;
    std::shared_ptr<CurveService> m_pService;
    std::shared_ptr<CurveModel> m_pModel;
};

#endif // CURVEMANAGER_H
