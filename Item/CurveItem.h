#ifndef CURVEITEM_H
#define CURVEITEM_H

#include <QPainter>
#include <memory>

class CurveItem
{
public:
    CurveItem() {};

    virtual int getType() = 0;
    virtual void paint(QPainter* painter) = 0;
};

class CurveResInfoItem;
class CurvePaintItem : public CurveItem
{
public:
    CurvePaintItem() {};
    CurvePaintItem(double dX, double dY, std::shared_ptr<CurveResInfoItem> pResInfo);

protected:
    virtual double getPositionX() const;
    virtual double getPositionY() const;

protected:
    std::shared_ptr<CurveResInfoItem> m_pResInfo;
    double m_dX;
    double m_dY;
};

#endif // CURVEITEM_H
