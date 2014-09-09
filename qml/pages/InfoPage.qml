import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

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
                color: Theme.highlightColor
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Send beer, pizza and Club Mate to")
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "http://www.bytewerk.org"
                onClicked: Qt.openUrlExternally("http://www.bytewerk.org")
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("source code")
                onClicked: Qt.openUrlExternally("https://github.com/Bytewerk/Messwerk")
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
