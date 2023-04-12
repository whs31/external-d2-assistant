import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "../ui/buttons" as Buttons

Window { id: control;
    // можно динамически менять размер области для клика, так что 0 проблем с оверлеем/меню
    width: 100;
    height: root.height * 0.02;
    x: root.width * 0.732;
    y: root.height - height; // относительно верхн его левого
    visible: true;
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground;
    color: "#00000000";
    Rectangle {
        color: "#3B4252";
        anchors.fill: parent;
        anchors.bottomMargin: -7;
        radius: 7;

        Buttons.ToolButton { id: c_ToggleConsoleDebugButton;
            anchors.left: parent.left;
            anchors.leftMargin: 3;
            anchors.top: parent.top;
            anchors.topMargin: 2;
            fixedheight: 20;

            icon: "qrc:/icons/command-line.png";
            highlightcolor: "#5E81AC";
            tooltiptext: "Open Console"
            opaque: false;
            onClicked: debugConsole.visible = !debugConsole.visible;
        }
    }
}
