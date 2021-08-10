#ifndef CURVENUMBER_H
#define CURVENUMBER_H

#include "CurveItem.h"
#include "CurveResInfoItem.h"

class CurveSceneData;
class CurveNumber : public CurvePaintItem
{
public:
    using CurvePaintItem::CurvePaintItem;
    CurveNumber(double dX, double dY, std::shared_ptr<CurveResInfoItem> pResInfo, std::shared_ptr<CurveSceneData> pSceneData);
    int getType() override;
    void paint(QPainter *painter) override;

protected:
    std::shared_ptr<CurveSceneData> m_pSceneData;
};

#endif // CURVENUMBER_H
