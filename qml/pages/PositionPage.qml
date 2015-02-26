import QtQuick 2.0
import Sailfish.Silica 1.0
import MesswerkWidgets 1.0

import "../Constants.js" as Constants

Page {
    id: page

    function formatCoordinate(n) {
        return '<b>' + n.toFixed(6) + ' °</b>';
    }

    function formatAltitude(n) {
        if(n < 0) {
            return '<b>N/A</b>';
        } else {
            return '<b>' + n.toFixed(2) + ' m</b>';
        }
    }

    function formatAccuracy(n) {
        return '<b>' + n.toFixed(2) + ' m</b>';
    }

    function formatFix(n) {
        switch(n) {
            case Constants.COORD_2D:
                return '<b>2D</b>';

            case Constants.COORD_3D:
                return '<b>3D</b>';

            case Constants.COORD_INVALID:
                return '<b>None</b>';

            default:
                return '<b>Unknown</b>';
        };
    }

    Component.onCompleted: {
        positionsensor.activate(Constants.PART_PAGE);
    }
    Component.onDestruction: {
        positionsensor.deactivate(Constants.PART_PAGE);
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                function togglePositionLogging() {
                    if(positionsensor.isLogging) {
                        positionsensor.stopLogging();
                    } else {
                        positionsensor.startLogging();
                    }
                }

                text: qsTr("Position: ") + (positionsensor.isLogging ? qsTr("Stop") : qsTr("Start")) + qsTr(" logging")
                onClicked: togglePositionLogging()
            }
        }

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Position")
            }
            SectionHeader {
                text: qsTr("WGS84 Coordinates")
            }
            Column {
                width: parent.width
                spacing: Theme.paddingSmall

                Label {
                    id: fixlabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: qsTr('Fix: ') + page.formatFix(positionsensor.coordType)
                }
                Label {
                    id: latlabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: qsTr('Latitude: ') + page.formatCoordinate(positionsensor.latitude)
                }
                Label {
                    id: lonlabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: qsTr('Longitude: ') + page.formatCoordinate(positionsensor.longitude)
                }
                Label {
                    id: altlabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: qsTr('Altitude: ') + page.formatAltitude(positionsensor.altitude)
                }
            }
            SectionHeader {
                text: qsTr("Accuracy")
            }
            Column {
                width: parent.width
                spacing: Theme.paddingSmall

                Label {
                    id: horzAccLabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: qsTr('Horizontal: ') + page.formatAccuracy(positionsensor.horzAccuracy)
                }
                Label {
                    id: vertAccLabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: qsTr('Vertical: ') + page.formatAccuracy(positionsensor.vertAccuracy)
                }
            }
            SectionHeader {
                text: qsTr("Maidenhead Locator")
            }
            Column {
                width: parent.width
                spacing: Theme.paddingSmall

                Label {
                    id: locatorLabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: qsTr('Grid: ') + '<b>' + positionsensor.maidenhead + '</b>'
                }
            }
        }
    }
}


