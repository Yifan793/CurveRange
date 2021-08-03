#include "MyWidget3.h"

MyWidget3::MyWidget3()
{
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
    this->setSource(QUrl(getQmlUrl()));
}

QString MyWidget3::getQmlUrl()
{
    return "qrc:/CurveRangePage.qml";
}
