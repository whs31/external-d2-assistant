import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "qrc:/qit/elements/buttons" as Buttons

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
    Rectangle {
        color: "#3B4252";
        anchors.fill: parent;
        anchors.bottomMargin: -7;
        radius: 7;

        Buttons.ToolButton { id: cCloseAppDebugButton;
            anchors.right: parent.right;
            anchors.rightMargin: 2;
            anchors.top: parent.top;
            anchors.topMargin: 2;
            fixedheight: 20;

            icon: "qrc:/qit/placeholder/sample_info_icon.png";
            basecolor: "#BF616A";
            highlightcolor: "#D08770";
            opaque: true;
            onClicked: Qt.quit();
        }

        Buttons.ToolButton { id: cToggleConsoleDebugButton;
            anchors.right: cCloseAppDebugButton.left;
            anchors.rightMargin: 2;
            anchors.top: parent.top;
            anchors.topMargin: 2;
            fixedheight: 20;

            icon: "qrc:/qit/placeholder/sample_info_icon.png";
            highlightcolor: "#5E81AC";
            opaque: false;
            onClicked: debugConsole.visible = !debugConsole.visible;
        }
    }
}
