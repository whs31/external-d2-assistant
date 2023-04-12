import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import ConsoleWidget 1.0

Window { id: control;
    // можно динамически менять размер области для клика, так что 0 проблем с оверлеем/меню
    width: 1000;
    height: 600;
    x: 75;
    y: 75; // относительно верхнего левого
    visible: true;
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground;
    color: "#00000000";
Rectangle { id: controlOverlay;
    anchors.fill: parent;
    color: "#232323";
    border.width: 0.5;
    border.color: "#343434";
    z: 100;
    clip: true;

    FontLoader { id: monoFont; source: "qrc:/fonts/UbuntuMono.ttf"; }
    Connections
    {
        target: Impl;
        function onAppendSignal(text)
        {
            textArea.append(text);
        }
    }
    Rectangle { id: header;
        height: 20;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        color: "#343434";

        Image { id: title;
            source: "qrc:/icons/header.png";
            anchors.left: parent.left;
            anchors.leftMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;
        }

        MouseArea { // move window mouse area
            anchors.fill: parent;
            anchors.rightMargin: 20;
            property point offset: Qt.point(0, 0);
            onPressed: {
                parent.color = "#444444";
                offset = Qt.point(mouseX, mouseY);
            }
            onReleased: {
                parent.color = "#343434";
            }
            onPositionChanged: {
                if(pressed) {
                    let global_pos = mapToGlobal(mouseX, mouseY);
                    control.x = global_pos.x - offset.x;
                    control.y = global_pos.y - offset.y;
                }
            }
        }

        Rectangle { id: closeButton;
            anchors.right: parent.right;
            anchors.top: parent.top;
            width: 20;
            height: 20;
            color: "#343434";

            MouseArea { // close window mouse area
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: parent.color = "#563A3D";
                onExited: parent.color = "#343434";
                onClicked: {
                    control.visible = false;
                }
            }

            Image {
                source: "qrc:/icons/cross.png";
                anchors.centerIn: parent;
            }
        }
    }

    ScrollView { id: scrollView;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: inputArea.top;
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn;

        TextArea { id: textArea;
            color: "#ECEFF4";
            background: Rectangle{
                color:"#232323";
            }
            text: "[GUI] Console initialized";
            selectByMouse: true;
            readOnly: true;
            selectedTextColor: "#2E3440";
            selectionColor: "#B48EAD";
            textFormat: Text.RichText;
            font.family: monoFont.name;
            font.pixelSize: 13;
            wrapMode: Text.NoWrap;
            function append(strAdd)
            {
                textArea.text = textArea.text + strAdd;
                textArea.cursorPosition = textArea.length - 1;
            }
        }
    }

    Rectangle { id: inputArea;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        height: 28;
        color: "#000000";
        border.width: 0.5;
        border.color: "#343434";

        TextInput {
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
                Impl.sendCommand(text);
                text = "";
            }
        }

        Rectangle { id: resizeButton;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            width: 16;
            height: 16;
            color: "#000000";

            MouseArea { // resize window mouse area
                property point offset: Qt.point(0, 0);
                anchors.fill: parent;
                hoverEnabled: true;
                onPressed: {
                    parent.color = "#343434";
                    offset = Qt.point(mouseX, mouseY);
                }
                onReleased: {
                    parent.color = "#000000";
                }
                onPositionChanged: {
                    if(pressed) {
                        let global_pos = mapToGlobal(mouseX, mouseY);
                        control.width = global_pos.x - offset.x;
                        control.height = global_pos.y - offset.y;
                        if(control.width <= 60)
                            control.width = 60;
                        if(control.height <= 50)
                            control.height = 50;
                    }
                }
            }

            Image {
                source: "qrc:/icons/handle.png";
                anchors.centerIn: parent;
            }
        }
    }
}
}
