import QtQuick 2.15
import QtQuick.Controls 2.15
import DebugConsoleImpl 1.0

Rectangle { color: "#232323";
    Connections
    {
        target: Impl;
        onAppendSignal:
        {
            textArea.append(text);
        }
    }

    ScrollView { id: scrollView;
        anchors.fill: parent;
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
        TextArea { id: textArea;
            color: "white";
            text: "[GUI] Console initialized";
            selectByMouse: true;
            readOnly: true;
            selectedTextColor: "white";
            selectionColor: "#484869";
        }
    }
}
