#ifndef CURVEMODEL_H
#define CURVEMODEL_H

#include "CurveItem.h"
#include <QMap>

class ModelUnit
{
public:
    QVector<std::shared_ptr<CurveItem>> m_ItemVec;
};

//songyifan TODO 把viewer和box2d换成notify构造
class CurveViewer;
class CurveBox2D;
class CurveModel
{
public:
    CurveModel(std::shared_ptr<CurveViewer> pViewer, std::shared_ptr<CurveBox2D> pBox2D);

    void addItem(int type, std::shared_ptr<CurveItem> pItem);
    void insertItem(int index, int type, std::shared_ptr<CurveItem> pItem);
    void removeItem(int type, std::shared_ptr<CurveItem> pItem);
    int getIndex(int type, std::shared_ptr<CurveItem> pItem);

    void clearUnit(int nType);
    std::shared_ptr<CurveItem> getItem(int type, int index) const;
    int getSize(int type);

    template <class T>
    std::shared_ptr<T> getTypicalItem(int type, int index) const
    {
        auto pItem = getItem(type, index);
        return std::static_pointer_cast<T>(pItem);
    }

private:
    void ensureValid(int type);

private:
    QMap<int, std::shared_ptr<ModelUnit>> m_modelUnitMap;
    std::shared_ptr<CurveViewer> m_pViewer;
    std::shared_ptr<CurveBox2D> m_pBox2D;
};

#endif // CURVEMODEL_H
