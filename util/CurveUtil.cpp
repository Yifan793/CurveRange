#include "CurveUtil.h"

static const double c_dZeroRange = 1e-6;

QRectF CurveUtil::mapToScene(const QRectF& ori, const QPointF& offset, double dScale)
{
    if (dScale < c_dZeroRange && dScale > -c_dZeroRange)
    {
        assert(false);
    }

    QRectF sceneRect = ori;
    sceneRect.translate(-offset);
    sceneRect.setTopLeft(sceneRect.topLeft() / dScale);
    sceneRect.setBottomRight(sceneRect.bottomRight() / dScale);
    return sceneRect;
}

QPointF CurveUtil::mapToScene(const QPointF& ori, const QPointF& offset, double dScale)
{
    if (dScale < c_dZeroRange && dScale > -c_dZeroRange)
    {
        assert(false);
    }

    QPointF scenePt = ori;
    scenePt -= offset;
    scenePt = scenePt / dScale;
    return scenePt;
}

QPointF CurveUtil::sceneToMap(const QPointF &scenePt, const QPointF &offset, double dScale)
{
    if (dScale < c_dZeroRange && dScale > -c_dZeroRange)
    {
        assert(false);
    }
    QPointF mapPt = scenePt;
    mapPt *= dScale;
    mapPt += offset;
    return mapPt;
}
