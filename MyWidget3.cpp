#include "MyWidget3.h"

#include "CurveDefines.h"

MyWidget3::MyWidget3()
{
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
    this->setSource(QUrl(getQmlUrl()));
    this->setMinimumSize(668, 550);
}

QString MyWidget3::getQmlUrl()
{
    return "qrc:/CurvePage.qml";
}
