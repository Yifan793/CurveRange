#ifndef CURVEUTIL_H
#define CURVEUTIL_H

#include <QRectF>

class CurveUtil
{
public:
    static QRectF mapToScene(const QRectF& ori, const QPointF& offset, double dScale);
    static QPointF mapToScene(const QPointF& ori, const QPointF& offset, double dScale);
    static QPointF sceneToMap(const QPointF& scenePt, const QPointF& offset, double dScale);
};

#endif // CURVEUTIL_H
