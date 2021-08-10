import QtQuick 2.0
import CurveManager 1.0

Rectangle {
    id: bgRect;
    color: "#222222";

    focus: true;
    Keys.enabled: true;
    Keys.onPressed: {
        curveManager.keyPressed(event);
    }
    Keys.onReleased: {
        curveManager.keyReleased(event);
    }

    CurveManager {
        id: curveManager;
        anchors.top: parent.top;
        anchors.left: parent.left; anchors.right: parent.right;
        anchors.bottom: parent.bottom; anchors.bottomMargin: 68;

        Component.onCompleted: {
            curveManager.init();
        }
    }

    Rectangle{
        id: textInput;
        anchors.top: parent.top; anchors.topMargin: 42;
        anchors.left: parent.left; anchors.leftMargin: 12;
        width: 52; height: 22
        border.color: "#535353";
        color: "#444444";
        radius: 4;

        TextInput{
            anchors.fill: parent;
            color: "white";
        }
    }

    Rectangle{
        id: button;
        width: 54; height: 22;
        anchors.top: parent.top; anchors.topMargin: 16;
        anchors.right: parent.right; anchors.rightMargin: 24;
        border.color: "#535353";
        color: "#444444";
        radius: 4;
        Text{
            anchors.centerIn: parent;
            text: qsTr("重置");
            color: "white";
            font.pixelSize: 10;
        }
    }

}
