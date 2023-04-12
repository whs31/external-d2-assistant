/*
   Qit QML/Js/C++ Library
   https://github.com/whs31/qit

 * Made by @whs31
 * Free to use by anyone

 */

import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle { id: control;
    // icon
    property int iconsize: height - 6;
    property string icon: ""; // no icon if empty
    property color iconcolor: "#D8DEE9";
    property color iconhighlightcolor: iconcolor;

    // button
    property bool primary: false;
    property real fixedwidth: container.width + 30; // auto-scaling, if not stated otherwise
    property real fixedheight: 24;
    property color basecolor: primary ? "#434C5E" : "transparent";
    property color highlightcolor: "#EBCB8B";
    property color clickcolor: primary ? Qt.darker(basecolor, 1.2) : "#2E3440";
    property real roundingradius: height / 3.2;

    // label
    property color textcolor: iconcolor;
    property color texthighlightcolor: iconhighlightcolor;
    property string text: "Sample text";
    property string textfamily: "Arial";
    property int textsize: height / 1.8;
    property int textweight: Font.Medium;

    // tooltip
    property string tooltiptext: ""; // no tooltip if empty

    // control signals
    signal clicked();
    opacity: enabled ? 1 : .5;






    // implementation
    color: basecolor;
    radius: roundingradius;
    width: fixedwidth;
    height: fixedheight;
    border.width: 1;
    border.color: primary ? "transparent" : textcolor;
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
        Text { id: txt;
            text: control.text;
            font.pixelSize: control.textsize;
            font.family: control.textfamily;
            font.weight: control.textweight;
            color: control.textcolor;
            opacity: enabled ? 1 : .5;
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: Text.AlignLeft;
            anchors.left: ico.right;
            anchors.leftMargin: 3;
            anchors.verticalCenter: parent.verticalCenter;
        }
    }

    MouseArea {
        id: controlMouseArea;
        hoverEnabled: true;
        anchors.fill: parent
        onEntered: {
            animation_hoverOn.start();
            txt.color = control.texthighlightcolor;
            ico_color_overlay.color = control.iconhighlightcolor;
        }
        onExited: {
            animation_hoverOff.start();
            txt.color = control.textcolor;
            ico_color_overlay.color = control.iconcolor;
        }
        onClicked: {
            control.animateClick();
        }
        onHoveredChanged:
        {
            if(!containsMouse)
            {
                animation_hoverOff.start();
                txt.color = control.textcolor;
                ico_color_overlay.color = control.iconcolor;
            }
        }
    }
    ToolTip { id: m_tooltip;
        delay: 500;
        timeout: 5000;
        visible: control.tooltiptext.length !== 0 ? controlMouseArea.containsMouse : false;
        font.pixelSize: 12;
        contentItem: Text {
            text: control.tooltiptext;
            font: control.textfamily;
            color: control.primary ? control.basecolor : "#434C5E";
        }
        background: Rectangle {
            color: control.textcolor;
            radius: 20;
            opacity: 0.75;
        }
    }

    Component.onCompleted: controlMouseArea.clicked.connect(clicked);
}
