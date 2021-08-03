#ifndef CURVEMODEL_H
#define CURVEMODEL_H

#include "CurveItem.h"
#include <QMap>

class ModelUnit
{
public:
    QVector<std::shared_ptr<CurveItem>> m_ItemVec;
};

class CurveViewer;
class CurveModel
{
public:
    CurveModel(std::shared_ptr<CurveViewer> pViewer);
    void addItem(int type, std::shared_ptr<CurveItem> pItem);
    void clearUnit(int nType);
    std::shared_ptr<CurveItem> getItem(int type, int index) const;

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

};

#endif // CURVEMODEL_H
