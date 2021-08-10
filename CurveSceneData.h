#ifndef CURVESCENEDATA_H
#define CURVESCENEDATA_H

#include <QRectF>

class CurveSceneData
{
public:
    int nWindowWidth;
    int nWindowHeight;
    QRectF sceneRect;
    double dMinScale = 1.0;
    double dMaxScale = 3.0;
    double dScale = 1.0;
    QPointF offset;
};

#endif // CURVESCENEDATA_H
