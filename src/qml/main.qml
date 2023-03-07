import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "widgets" as Widgets

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
        width: overlayArea.width / 4;
        height: overlayArea.height - 150;
        x: 75;
        y: 75; // относительно верхнего левого
        visible: true;
        flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
               Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
               Qt.WA_NoBackground;
        color: "#00000000";
        Component.onCompleted: show();
        Widgets.DebugConsole { id: debugConsole;
            anchors.fill: parent;
            visible: true;
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
