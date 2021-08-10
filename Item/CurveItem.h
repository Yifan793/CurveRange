#ifndef CURVEITEM_H
#define CURVEITEM_H

#include <QPainter>
#include <memory>

#include "notifier/CurveNotifier.h"

class CurveItem
{
public:
    CurveItem() {};

    virtual int getType() = 0;
    virtual void paint(QPainter* painter) = 0;
    virtual bool isHitByPoint(const QPointF& pt) = 0;
};

class CurveResInfoItem;
class CurveSceneData;
class CurvePaintItem : public CurveItem
{
public:
    CurvePaintItem() {};
    CurvePaintItem(double dX, double dY, std::shared_ptr<CurveResInfoItem> pResInfo);

    bool isHitByPoint(const QPointF& pt) override { return false; }

    void setValueX(double value);
    double getValueX() { return m_dX; }
    void setValueY(double value) { m_dY = value; }
    double getValueY() { return m_dY; }
    void setIndex(int index) { m_nIndex = index; }
    int getIndex() { return m_nIndex; }
    void setPixelRatio(double pixelRatio) { m_nPixelRatio = pixelRatio; }

    void setNotifier(std::shared_ptr<CurveNotifier> pNotifier) { m_pNotifier = pNotifier; }
    void setResInfoItem(std::shared_ptr<CurveResInfoItem> pResInfoItem) { m_pResInfo = pResInfoItem; }

    virtual double getPositionX() const;
    virtual double getPositionY() const;

protected:
    std::shared_ptr<CurveResInfoItem> m_pResInfo;
    std::shared_ptr<CurveNotifier> m_pNotifier;
    double m_dX;
    double m_dY;
    int m_nIndex;
    double m_nPixelRatio;
};

#endif // CURVEITEM_H
