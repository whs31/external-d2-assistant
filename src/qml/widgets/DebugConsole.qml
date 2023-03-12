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
        color: "#2E3440";

        anchors.fill: parent;
        radius: 13;
        clip: true;
        Rectangle
        {
            radius: 7;
            color: "#3B4252";
            height: 23;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            Text
            {
                color: "#ECEFF4";
                text: "CONSOLE";
                font.bold: true;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: 5;
                font.pixelSize: 14;
                font.family: uiFont.name;
            }
        }

        Connections
        {
            target: Impl;
            function onAppendSignal(text)
            {
                let a = text + "\n" + textArea.text
                textArea.text = a;
//                textArea.append(text);
            }
            function onChangeVisibility(state)
            {
                control.visible = state;
            }
        }
        ScrollView { id: scrollView;
            anchors.fill: parent;
            anchors.topMargin: 23;
            anchors.bottomMargin: 23;
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
            TextArea { id: textArea;
                color: "#ECEFF4";
                background: Rectangle{
                    color:"#2e3440";
                }
                text: "[GUI] Console initialized";
                selectByMouse: true;
                readOnly: true;
                selectedTextColor: "#2E3440";
                selectionColor: "#B48EAD";
                textFormat: Text.RichText;
                font.family: monoFont.name;
                font.pixelSize: 13;
                wrapMode: Text.WordWrap;
                function append(strAdd)
                {
                    textArea.text = textArea.text + strAdd;
                    textArea.cursorPosition = textArea.length-1;
                }
            }
        }
        Rectangle
        {
            height: 23;
            radius: 7;
            anchors.bottom: parent.bottom;
            anchors.left: parent.left;
            anchors.right: parent.right;
            color: "#3B4252";
            TextInput
            {
                anchors.fill: parent;
                anchors.leftMargin: 3;
                color: "#ECEFF4";
                cursorVisible: true;
                text: "";
                verticalAlignment: Text.AlignVCenter;
                selectByMouse: true;
                selectedTextColor: "#2E3440";
                selectionColor: "#B48EAD";
                font.family: monoFont.name;
                font.pixelSize: 13;
                onAccepted:
                {
                    console.log("[CONSOLE] Command received: " + text);
                    text = "";
                }
            }
        }
    }
}

