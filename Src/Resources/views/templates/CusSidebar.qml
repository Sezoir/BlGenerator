import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: root
    // Public properties
    property string headerTitle: ""

    // Private properties
    QtObject {
        id: internal
        property bool hidden: false
    }

    anchors {
        left: parent.left
        top: parent.top
        bottom: parent.bottom
    }

    width: 100
    state: "closing"

    Page {
        id: sidebar
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        width: parent.width
        //visible: internal.hidden

        header: ToolBar {
            id: toolbar
            background: Rectangle {
                anchors {
                    left: toolbar.left
                    top: toolbar.top
                    right: toolbar.right
                    bottom: toolbar.bottom
                }
                color: "white"
            }

            RowLayout {
                anchors.fill: parent
                ToolButton {
                    text: qsTr("<")
                    onClicked: toggleHide()
                }
                Label {
                    text: headerTitle
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }
            }
        }
    }

    TabButton {
        id: open

        contentItem: Text {
            text: qsTr(">")
            color: "black"
        }

        anchors {
            top: parent.top
            left: parent.left
        }
        implicitWidth: 40
        implicitHeight: 40
        onClicked: toggleHide()
        background: Rectangle {
            color: "white"
            implicitHeight: open.implicitHeight
            implicitWidth: open.implicitWidth
            opacity: open.hovered ? 0.8 : 1
        }

        visible: !internal.hidden
    }

    function toggleHide()
    {
        //internal.hidden = !internal.hidden;
        if(internal.hidden)
        {
            internal.hidden = false;
            root.state = "closing"
        }
        else
        {
            internal.hidden = true
            root.state = "opening"
        }
    }

    states: [
        State {
            name: "closing"
            AnchorChanges { target: sidebar; anchors.right: root.left}
        },
        State {
            name: "opening"
            AnchorChanges { target: sidebar; anchors.right: root.right}
        }
    ]

    transitions: Transition {
        AnchorAnimation {duration: 200}
    }
}
