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
    visible: true;
    flags: Qt.WA_NoSystemBackground | Qt.WA_TranslucentBackground |
           Qt.FramelessWindowHint   | Qt.WindowStaysOnTopHint     |
           Qt.WA_NoBackground;
    color: "#00000000";

}
