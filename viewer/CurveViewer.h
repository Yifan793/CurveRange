#ifndef CURVEVIEWER_H
#define CURVEVIEWER_H

#include <memory>
#include <QVector>
#include <QPainter>

class CurveItem;
class CurveViewer
{
public:
    CurveViewer();
    void initPainterOrder();
    virtual void paint(QPainter* painter);

    virtual void addItem(std::shared_ptr<CurveItem> pItem);
    virtual void insertItem(int index, std::shared_ptr<CurveItem> pItem);
    virtual void removeItem(std::shared_ptr<CurveItem> pItem);
    QVector<int> getPainterOrder() { return m_paintOrder; }

protected:
    QVector<std::shared_ptr<CurveItem>> m_itemVec;
    QVector<int> m_paintOrder;
};

#endif
