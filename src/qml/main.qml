import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "widgets" as Widgets
import "qrc:/qonsole" as Qonsole;

Window { id: root;
    width: 640
    height: 480
    visible: true
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground       | Qt.WindowTransparentForInput;
    Component.onCompleted: showFullScreen();
    color: "#00000000"


    Qonsole.DebugConsole { id: debugConsole; }
    Widgets.ControlPanel { id: controlPanel; }

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
