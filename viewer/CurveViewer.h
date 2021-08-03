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
    virtual void paint(QPainter* painter);
    virtual void addItem(std::shared_ptr<CurveItem> pItem);
    virtual void removeItem(std::shared_ptr<CurveItem> pItem);

protected:
    QVector<std::shared_ptr<CurveItem>> m_itemVec;
};

#endif
