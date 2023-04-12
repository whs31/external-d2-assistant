import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.15

Item { id: control;
    // icon
    property int iconsize: height - 6;
    property string icon: ""; // no icon if empty
    property color iconcolor: "#D8DEE9";
    property color iconhighlightcolor: iconcolor;

    // button
    property real fixedwidth: container.width + 30; // auto-scaling, if not stated otherwise
    property real fixedheight: 24;
    property color basecolor: "#434C5E";
    property color blankcolor: "#24272E";
    property color highlightcolor: "#5E81AC";
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

    // control properties
    property bool checked: false;
    property int checkedstate: 0;
    property bool tristate: false;

    // implementation
    width: fixedwidth;
    height: fixedheight;
    opacity: enabled ? 1 : .5;

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
            visible: false;
        }
        ColorOverlay { id: ico_color_overlay;
            source: ico;
            anchors.fill: ico;
            color: control.iconcolor;
            opacity: enabled ? 1 : .5;
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
}
