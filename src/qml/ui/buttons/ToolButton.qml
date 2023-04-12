/*
   Qit QML/Js/C++ Library
   https://github.com/whs31/qit

 * Made by @whs31
 * Free to use by anyone

 */

import QtQuick 2.15
import QtQuick.Controls 2.12
//import QtGraphicalEffects 1.15

Rectangle { id: control;
    // icon
    property int iconsize: height - 6;
    required property string icon; // throw error if empty
    property color iconcolor: "#D8DEE9";
    property color iconhighlightcolor: iconcolor;

    // button
    property bool opaque: true;
    property real fixedheight: 24;
    property real fixedwidth: fixedheight; // auto-scaling, if not stated otherwise
    property color basecolor: opaque ? "#434C5E" : "transparent";
    property color highlightcolor: "#EBCB8B";
    property color clickcolor: Qt.darker(basecolor, 1.2);
    property real roundingradius: height / 3.2;

    // tooltip
    property color tooltiptextcolor: iconcolor;
    property string tooltiptextfamily: "Arial";
    property string tooltiptext: ""; // no tooltip if empty

    // control signals
    signal clicked();
    opacity: enabled ? 1 : 0.5;






    // implementation
    color: basecolor;
    radius: roundingradius;
    width: fixedwidth;
    height: fixedheight;
    ColorAnimation { id: animation_hoverOn;
        target: control;
        property: "color";
        to: control.highlightcolor;
        duration: 100;
    }
    ColorAnimation { id: animation_hoverOff;
        target: control;
        property: "color";
        to: control.basecolor;
        duration: 100;
    }

    function animateClick()
    {
        animation_click.start();
        animation_clickColorChange.start();
        forceActiveFocus();
    }

    SequentialAnimation { id: animation_clickColorChange;
        ColorAnimation {
            target: control;
            property: "color";
            to: control.clickcolor;
            duration: 100;
        }
        ColorAnimation {
            target: control;
            property: "color";
            to: control.highlightcolor;
            duration: 100;
        }
    }
    SequentialAnimation { id: animation_click;
        PropertyAnimation {
            target: control;
            property: "scale";
            to: 0.9;
            duration: 50;
            easing.type: Easing.InOutQuad;
        }
        PropertyAnimation {
            target: control;
            property: "scale";
            to: 1.0;
            duration: 50;
            easing.type: Easing.InOutQuad;
        }
    }

    Item { id: container;
        width: childrenRect.width;
        height: control.height;
        anchors.centerIn: parent;
        Image { id: ico;
            width: control.icon.length !== 0 ? control.iconsize : 0;
            height: width;
            source: control.icon;
            smooth: true;
            antialiasing: true;
            anchors.verticalCenter: parent.verticalCenter;
        }
    }
    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: {
            animation_hoverOn.start();
        }
        onExited: {
            animation_hoverOff.start();
        }
        onClicked: {
            control.animateClick();
        }
    }

    ToolTip { id: m_tooltip;
        delay: 500;
        timeout: 5000;
        visible: control.tooltiptext.length !== 0 ? controlMouseArea.containsMouse : false;
        font.pixelSize: 12;
        contentItem: Text {
            text: control.tooltiptext;
            font: control.tooltiptextfamily;
            color: control.primary ? control.basecolor : "#434C5E";
        }
        background: Rectangle {
            color: control.tooltiptextcolor;
            radius: 20;
            opacity: 0.75;
        }
    }

    Component.onCompleted: controlMouseArea.clicked.connect(clicked);
}
