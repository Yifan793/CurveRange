#ifndef CURVERESINFOITEM_H
#define CURVERESINFOITEM_H

#include "CurveItem.h"
#include "CurveDefines.h"

class CurveResInfoItem : public CurveItem
{
public:

    struct CurveKeyPoint
    {
        double m_dPosX;
        double m_dPosY;
        double m_dInTan;
        double m_dOutTan;
    };

    using CurveItem::CurveItem;
    int getType() override;
    void paint(QPainter *painter) override { Q_UNUSED(painter) };

    void setAxisX(double num) { m_dAxisX = num; }
    double getAxisX() { return m_dAxisX; }
    void setAxisY(double num) { m_dAxisY = num; }
    double getAxisY() { return m_dAxisY; }

    void setWindowWidth(double dWindowWidth) { m_dWindowWidth = dWindowWidth; }
    double getWindowWidth() { return m_dWindowWidth; }
    void setWindowHeight(double dWindowHeight) { m_dWindowHeight = dWindowHeight; }
    double getWindowHeight() { return m_dWindowHeight; }

    void setMinX(double dMinX) { m_dMinX = dMinX; }
    double getMinX() { return m_dMinX; }
    void setMaxX(double dMaxX) { m_dMaxX = dMaxX; }
    double getMaxX() { return m_dMaxX; }

    void setMinY(double dMinY) { m_dMinY = dMinY; }
    double getMinY() { return m_dMinY; }
    void setMaxY(double dMaxY) { m_dMaxY = dMaxY; }
    double getMaxY() { return m_dMaxY; }

    void setLineCountX(int nLineCountX) { m_nLineCountX = nLineCountX; }
    int getLineCountX() { return m_nLineCountX; }
    void setLineCountY(int nLineCountY) { m_nLineCountY = nLineCountY; }
    int getLineCountY() { return m_nLineCountY; }

    void setNumCountX(int nCountX) { m_nNumCountX = nCountX; }
    int getNumCountX() { return m_nNumCountX; }
    void setNumCountY(int nCountY) { m_nNumCountY = nCountY; }
    int getNumCountY() { return m_nNumCountY; }

    void addKeyPoint(double x, double y, double inTan, double outTan);
    void removeKeyPoint(int index);

private:
    double m_dAxisX = 1.0;
    double m_dAxisY = 1.0;
    double m_dWindowWidth = c_nFixedCurveWidth;
    double m_dWindowHeight = c_nFixedCurveHeight;

    double m_dMinX = 0;
    double m_dMaxX = 1;
    double m_dMinY = 0;
    double m_dMaxY = 1;

    int m_nLineCountX = 11;
    int m_nLineCountY = 11;
    int m_nNumCountX = 11;
    int m_nNumCountY = 11;

    QVector<CurveKeyPoint> m_CurveKeyPoints;
};

#endif // CURVERESINFOITEM_H
