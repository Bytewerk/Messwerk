import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsDialog.qml"))
            }
            MenuItem {
                text: qsTr("Info")
                onClicked: pageStack.push(Qt.resolvedUrl("InfoPage.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge


            PageHeader {
                title: qsTr("Select Sensor")
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Position")
                onClicked: pageStack.push(Qt.resolvedUrl("PositionPage.qml"))
                color: (satelliteinfo.isLogging ? Theme.highlightColor : Theme.primaryColor)
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("GNSS Satellites")
                onClicked: pageStack.push(Qt.resolvedUrl("SatellitePage.qml"))
                color: (satelliteinfo.isLogging ? Theme.highlightColor : Theme.primaryColor)
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Rotation")
                onClicked: pageStack.push(Qt.resolvedUrl("RotationPage.qml"))
                color: (rotationsensor.isLogging ? Theme.highlightColor : Theme.primaryColor)
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Accelerometer")
                onClicked: pageStack.push(Qt.resolvedUrl("AccelPage.qml"))
                color: (accelerometer.isLogging ? Theme.highlightColor : Theme.primaryColor)
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Gyroscope")
                onClicked: pageStack.push(Qt.resolvedUrl("GyroPage.qml"))
                color: (gyroscope.isLogging ? Theme.highlightColor : Theme.primaryColor)
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Magnetometer")
                onClicked: pageStack.push(Qt.resolvedUrl("MagnetPage.qml"))
                color: (magnetometer.isLogging ? Theme.highlightColor : Theme.primaryColor)
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Light & Proximity")
                onClicked: pageStack.push(Qt.resolvedUrl("LightPage.qml"))
                color: ((lightsensor.isLogging || proximitysensor.isLogging) ? Theme.highlightColor : Theme.primaryColor)
            }
        }
    }
}


