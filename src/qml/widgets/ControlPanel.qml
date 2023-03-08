import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import DebugConsoleImpl 1.0

Window { id: control;
    // можно динамически менять размер области для клика, так что 0 проблем с оверлеем/меню
    width: root.width * 0.12;
    height: root.height * 0.02;
    x: root.width * 0.732;
    y: root.height - height; // относительно верхнего левого
    visible: true;
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground;
    color: "#00000000";
    Component.onCompleted: show();
    property bool console_state: false;
    Rectangle {
        color: "#232323";
        anchors.fill: parent;
        anchors.bottomMargin: -7;
        radius: 7;
        Button
        {
            text: "console";
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.margins: 7;
            width: 70;
            height: 16;
            onClicked:
            {
                if(console_state)
                {
                    Impl.hide();
                    console_state = false;
                } else
                {
                    Impl.show();
                    console_state = true;
                }
            }
        }
        Button
        {
            text: "quit";
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.margins: 7;
            width: 70;
            height: 16;
            onClicked:
            {
                Qt.quit(0);
            }
        }
    }
}
