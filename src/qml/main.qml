import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window { id: overlayArea;
    width: 640
    height: 480
    visible: true
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground       | Qt.WindowTransparentForInput;
    Component.onCompleted: showFullScreen();
    color: "#00000000"


    Window { id: inputArea;
        // по сути ширина и высота этой херни определяет размер области, на которую нельзя кликнуть мышкой.
        // можно динамически менять размер области для клика, так что 0 проблем с оверлеем/меню
        width: 25;
        height: 16;
        x: 16;
        y: 16; // относительно верхнего левого
        visible: true;
        flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
               Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
               Qt.WA_NoBackground;
        color: "#10FF0000";
        Component.onCompleted: show();
        Button
        {
            width: 25;
            height: 16;
            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
            text: "X"
            onClicked: Qt.quit();
        }
    }

    Rectangle {
        color: "#DEDEDE";
        width: 3;
        height: 20;
        anchors.centerIn: parent;
        Rectangle {
            color: "#DEDEDE";
            width: 20;
            height: 3;
            anchors.centerIn: parent;
        }
    }


    Rectangle {
        color: "#DEDEDE";
        width: 3;
        height: 20;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        Rectangle {
            color: "#DEDEDE";
            width: 20;
            height: 3;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
        }
    }
    Rectangle {
        color: "#DEDEDE";
        width: 3;
        height: 20;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        Rectangle {
            color: "#DEDEDE";
            width: 20;
            height: 3;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
        }
    }
    Rectangle {
        color: "#DEDEDE";
        width: 3;
        height: 20;
        anchors.right: parent.right;
        anchors.top: parent.top;
        Rectangle {
            color: "#DEDEDE";
            width: 20;
            height: 3;
            anchors.right: parent.right;
            anchors.top: parent.top;
        }
    }
    Rectangle {
        color: "#DEDEDE";
        width: 3;
        height: 20;
        anchors.left: parent.left;
        anchors.top: parent.top;
        Rectangle {
            color: "#DEDEDE";
            width: 20;
            height: 3;
            anchors.left: parent.left;
            anchors.top: parent.top;
        }
    }
}
