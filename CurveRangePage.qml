import QtQuick 2.0
import QtCharts 2.3

Rectangle {
    id: curRangePage;

    ChartView{
        id: chartView;
        anchors.fill: parent;
        antialiasing: true;

        ValueAxis{
            id: axisX;
            min: 0.0
            max: 1.0
            tickCount: 11
        }

        ValueAxis{
            id: axisY;
            min:0.0
            max:500.0
            tickCount: 11
        }

        LineSeries{
            id: curve;
            axisX: axisX;
            axisY: axisY;
            useOpenGL: true;
            color: "red"
            width: 3
        }

        function initSeries()
        {
            curveRangeEditSample();

        }

        function curveRangeEditSample()
        {
            var sampleCount = 500;
            curve.clear();
            for (var i = 0; i <= sampleCount; ++i)
            {
                var time = i / sampleCount;
                var value = i;
                curve.append(time, value);
            }

        }

        Component.onCompleted: {
            initSeries();
        }
    }

    Canvas {
        id: ctrlLine;
        anchors.fill: parent;

//        onPaint: {
//            var ctx = getContext("2d");
//            ctx.clearRect(0, 0, width, height);
//            ctx.lineWidth = 2;
//            ctx.strokeStyle = "red";
//            ctx.beginPath();

//            for (var i = 0; i < allKeyFrames.count; ++i)
//            {
//                var curveFrame = allKeyFrames.itemAt(i);
//                for (var j = 0; j < curveFrame.count; ++j)
//                {
//                }
//            }
//        }
    }

    Repeater{
        id: allKeyFrames;
        model: ListModel {}

        Item {
            id: keyFrame;
//            property var itemIndex: modelData;

            function initData()
            {

            }

            Rectangle {
                id: keyPt;
                width: 10;
                height: 10;
                radius: 5;
                color: "blue"

                property var cenX: x + width / 2;
                property var cenY: y + height / 2;

                MouseArea {
                    anchors.fill: parent;
                    drag.target: parent;
                    drag.threshold: 10;

                    onPositionChanged: {
                        updateCtrlPts();
                        updateTimeValue();
                        updateKeyFrame();
                    }

                    onDoubleClicked: {

                    }
                }
            }

            Rectangle {
                id: inPt;
                width: 6;
                height: 6;
                color: "blue"
                x: keyPt.x + 50;
                y: keyPt.y;

                property var cenX: x + width / 2;
                property var cenY: y + height / 2;

                MouseArea {
                    anchors.fill: parent;
                    drag.threshold: 1;
                    drag.target: dragObj;

                    onPressed: {
                        dragObj.x = inPt.cenX;
                        dragObj.y = inPt.cenY;
                        dragObj.target = "inPt";
                    }

                    onReleased: {
                        dragObj.target = ""
                    }

                }

            }

            Rectangle {
                id: outPt;
                width: 6;
                height: 6;
                color: "blue"
                x: keyPt.x + 50;
                y: keyPt.y;

                property var cenX: x + width / 2;
                property var cenY: y + height / 2;

                MouseArea {
                    anchors.fill: parent;
                    drag.threshold: 1;
                    drag.target: dragObj;

                    onPressed: {
                        dragObj.x = outPt.cenX;
                        dragObj.y = outPt.cenY;
                        dragObj.target = "outPt";
                    }

                    onReleased: {
                        dragObj.target = ""
                    }

                }

            }

            Item {
                id: dragObj;
                x: 50; y : 50;

                property var target: ""
                readonly property real dragRadius: Math.sqrt(Math.pow(x - keyPt.cenX, 2) + Math.pow(y - keyPt.cenY, 2))

                onDragRadiusChanged: {
                    if (target == "outPt" || target == "inPt")
                    {
                        var sign = target == "outPt" ? 1 : -1;
                        var targetX = keyPt.cenX + sign * ((dragObj.x + outPt.width / 2 - keyPt.cenX) * (50 / dragObj.dragRadius));
                        var targetY = keyPt.cenY + sign * ((dragObj.y + outPt.height / 2 - keyPt.cenY) * (50 / dragObj.dragRadius));

                        outPt.x = targetX - outPt.width / 2;
                        outPt.y = targetY - outPt.height / 2;

                        inPt.x = keyPt.cenX * 2 - targetX - inPt.width / 2;
                        inPt.y = keyPt.cenY * 2 - targetY - inPt.height / 2;

                        updateTanValue();
                        updateKeyFrame();
                    }
                }
            }
        }
    }
    function updateCtrlPts()
    {

    }

    function updateTimeValue()
    {

    }

    function updateKeyFrame()
    {

    }

    function updateTanValue()
    {

    }
}
