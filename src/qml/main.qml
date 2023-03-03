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
    Component.onCompleted: showMaximized();
    color: "#00000000"


    Window { id: inputArea;
        // по сути ширина и высота этой херни определяет размер области, на которую нельзя кликнуть мышкой.
        // мб ее можно динамически менять)
        width: 400
        height: 100
        x: 0;
        y: 0; // это относительно верхнего левого
        visible: true
        flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
               Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
               Qt.WA_NoBackground;
        color: "#10FF0000"
        Component.onCompleted: show();
        Button
        {
            width: 150;
            height: 50;
            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
            text: "выйти!"
            onClicked: Qt.quit();
        }
        Button
        {
            width: 150;
            height: 50;
            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter;
            text: "изменить размер!"
            onClicked: inputArea.width = 250; // можно динамически менять размер области для клика, так что 0 проблем с оверлеем/меню
        }
    }

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
