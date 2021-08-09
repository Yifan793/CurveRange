QT       += core gui quickwidgets qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CurveManager.cpp \
    CurveMouseKeyInfo.cpp \
    Item/CurveBackGround.cpp \
    Item/CurveCtrlPt.cpp \
    Item/CurveItem.cpp \
    Item/CurveLine.cpp \
    Item/CurveModel.cpp \
    Item/CurveNumber.cpp \
    Item/CurvePt.cpp \
    Item/CurvePtCtrlLine.cpp \
    Item/CurveResInfoItem.cpp \
    MyWidget.cpp \
    MyWidget2.cpp \
    MyWidget3.cpp \
    main.cpp \
    mainwindow.cpp \
    notifier/CurveNotifier.cpp \
    service/CurveBox2D.cpp \
    service/CurveService.cpp \
    stateMachine/CurveAddCenterPtState.cpp \
    stateMachine/CurveDeleteCenterPtState.cpp \
    stateMachine/CurveMoveCenterPtState.cpp \
    stateMachine/CurveMoveCtrlPtState.cpp \
    stateMachine/CurveNormalState.cpp \
    stateMachine/CurveSelectCenterPtState.cpp \
    stateMachine/CurveState.cpp \
    stateMachine/CurveStateMachine.cpp \
    viewer/CurveViewer.cpp

HEADERS += \
    CurveDefines.h \
    CurveManager.h \
    CurveMouseKeyInfo.h \
    Item/CurveBackGround.h \
    Item/CurveCtrlPt.h \
    Item/CurveItem.h \
    Item/CurveLine.h \
    Item/CurveModel.h \
    Item/CurveNumber.h \
    Item/CurvePt.h \
    Item/CurvePtCtrlLine.h \
    Item/CurveResInfoItem.h \
    MyWidget.h \
    MyWidget2.h \
    MyWidget3.h \
    mainwindow.h \
    notifier/CurveNotifier.h \
    service/CurveBox2D.h \
    service/CurveService.h \
    stateMachine/CurveAddCenterPtState.h \
    stateMachine/CurveDeleteCenterPtState.h \
    stateMachine/CurveMoveCenterPtState.h \
    stateMachine/CurveMoveCtrlPtState.h \
    stateMachine/CurveNormalState.h \
    stateMachine/CurveSelectCenterPtState.h \
    stateMachine/CurveState.h \
    stateMachine/CurveStateMachine.h \
    viewer/CurveViewer.h

FORMS += \
    mainwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    qml.qrc
