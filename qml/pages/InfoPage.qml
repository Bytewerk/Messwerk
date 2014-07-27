import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Info")
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Created by bytewerk™ Software Inc.")
            }
            Label {
                color: Theme.highlightColor
                font.underline: true
                wrapMode: Text.NoWrap
                anchors.horizontalCenter: parent.horizontalCenter
                text: "<a href=\"http://www.bytewerk.org\">http://www.bytewerk.org</a>"
            }
            SectionHeader {
                text: "Credits"
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Coding: cfr34k")
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Quality assurance: sqozz")
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Art & Design: sqozz, cfr34k")
            }
        }
    }
}
