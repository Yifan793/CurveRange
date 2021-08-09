#ifndef CURVEMOUSEKEYINFO_H
#define CURVEMOUSEKEYINFO_H

#include <memory>
#include <QPointF>

struct CurveBaseMouseInfo
{
    typedef  std::shared_ptr<CurveBaseMouseInfo> ptr;
    QPointF globalPos;
    QPointF mapPos;
    QPointF scenePos;
};

struct CurveBaseHoverInfo
{
    typedef std::shared_ptr<CurveBaseHoverInfo> ptr;
    QPointF mapPos;
    QPointF oriMapPos;
    QPointF scenePos;
    QPointF oriScenePos;
};

struct CurveBaseKeyInfo
{
    typedef  std::shared_ptr<CurveBaseKeyInfo> ptr;
    Qt::Key key;
    int modifiers;
};

struct CurveBaseWheelInfo
{
    typedef  std::shared_ptr<CurveBaseWheelInfo> ptr;
    QPointF mAngleDelta;
    QPointF mMapPt;
    QPointF mScenePt;
    int mModifiers;
};

#endif // CURVEMOUSEKEYINFO_H
