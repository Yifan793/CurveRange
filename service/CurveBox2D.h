#ifndef CURVEBOX2D_H
#define CURVEBOX2D_H

#include <memory>
#include <QPointF>
#include <QVector>

//songyifan TODO 加入notify程序
class CurveItem;
class CurveBox2D
{
public:
    CurveBox2D();

    virtual void addItem(std::shared_ptr<CurveItem> pItem);
    virtual void eraseItem(std::shared_ptr<CurveItem> pItem);
    virtual std::shared_ptr<CurveItem> getHitItem(const QPointF& pt) const;
    virtual std::shared_ptr<CurveItem> getHitItemByType(const QPointF& pt, int nType) const;
    virtual QVector<std::shared_ptr<CurveItem>> getHitItems(const QPointF& pt) const;

protected:
    QVector<std::shared_ptr<CurveItem>> m_items;
};

#endif // CURVEBOX2D_H
