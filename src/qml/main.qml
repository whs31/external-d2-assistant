import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground       | Qt.WindowTransparentForInput;
    title: qsTr("Hello World")
    Component.onCompleted: showMaximized();
    color: "#00000000"

    Rectangle {
        color: "#676700";
        width: 200;
        height: 50;
        anchors.centerIn: parent;
        Text {
            anchors.centerIn: parent;
            color: "white";
            text: "I'm center!";
            font.pixelSize: 25;
        }
    }
    Button
    {
        width: 300;
        height: 50;
        anchors.centerIn: parent;
        anchors.verticalCenterOffset: -200;
        text: "YAY!"
    }

    Rectangle {
        color: "#676700";
        width: 200;
        height: 50;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        Text {
            anchors.centerIn: parent;
            color: "white";
            text: "I'm bottom left!";
            font.pixelSize: 25;
        }
    }
    Rectangle {
        color: "#676700";
        width: 200;
        height: 50;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        Text {
            anchors.centerIn: parent;
            color: "white";
            text: "I'm bottom right!";
            font.pixelSize: 25;
        }
    }
    Rectangle {
        color: "#676700";
        width: 200;
        height: 50;
        anchors.right: parent.right;
        anchors.top: parent.top;
        Text {
            anchors.centerIn: parent;
            color: "white";
            text: "I'm top right!";
            font.pixelSize: 25;
        }
    }
    Rectangle {
        color: "#676700";
        width: 200;
        height: 50;
        anchors.left: parent.left;
        anchors.top: parent.top;
        Text {
            anchors.centerIn: parent;
            color: "white";
            text: "I'm top left!";
            font.pixelSize: 25;
        }
    }
}
