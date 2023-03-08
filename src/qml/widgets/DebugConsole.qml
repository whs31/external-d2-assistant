import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import DebugConsoleImpl 1.0

Window { id: control;
    // можно динамически менять размер области для клика, так что 0 проблем с оверлеем/меню
    width: root.width / 4;
    height: root.height - 150;
    x: 75;
    y: 75; // относительно верхнего левого
    visible: false;
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground;
    color: "#00000000";
    Component.onCompleted: show();
    Rectangle {
        color: "#232323";
        anchors.fill: parent;
        Rectangle
        {
            color: "#363636";
            height: 23;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            Text
            {
                color: "white";
                text: "CONSOLE";
                font.bold: true;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: 5;
                font.pixelSize: 13;
            }
        }

        Connections
        {
            target: Impl;
            onAppendSignal:
            {
                textArea.append(text);
            }
            onChangeVisibility:
            {
                control.visible = state;
            }
        }
        ScrollView { id: scrollView;
            anchors.fill: parent;
            anchors.topMargin: 23;
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
            TextArea { id: textArea;
                color: "white";
                text: "[GUI] Console initialized";
                selectByMouse: true;
                readOnly: true;
                selectedTextColor: "white";
                selectionColor: "#484869";
                textFormat: Text.RichText;
            }
        }
    }
}

