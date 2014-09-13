import QtQuick 2.0
import Sailfish.Silica 1.0
import MesswerkWidgets 1.0

import "../Constants.js" as Constants

Page {
    id: page

    function formatNumber(n) {
        return '<b>' + n.toFixed(3) + ' Lux</b>';
    }

    function updateBrightnessPlot() {
        bplot.addValue(lightsensor.brightness);
        bplot.update();
    }

    Component.onCompleted: {
        lightsensor.activate(Constants.PART_PAGE);
        lightsensor.brightnessChanged.connect(updateBrightnessPlot);

        proximitysensor.activate(Constants.PART_PAGE);
    }
    Component.onDestruction: {
        lightsensor.deactivate(Constants.PART_PAGE);
        lightsensor.brightnessChanged.disconnect(updateBrightnessPlot);

        proximitysensor.deactivate(Constants.PART_PAGE);
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                function toggleLightLogging() {
                    if(lightsensor.isLogging) {
                        lightsensor.stopLogging();
                    } else {
                        lightsensor.startLogging();
                    }
                }

                text: qsTr("Light sensor: ") + (lightsensor.isLogging ? qsTr("Stop") : qsTr("Start")) + qsTr(" logging")
                onClicked: toggleLightLogging()
            }
            MenuItem {
                function toggleProximityLogging() {
                    if(proximitysensor.isLogging) {
                        proximitysensor.stopLogging();
                    } else {
                        proximitysensor.startLogging();
                    }
                }

                text: qsTr("Proximity sensor: ") + (proximitysensor.isLogging ? qsTr("Stop") : qsTr("Start")) + qsTr(" logging")
                onClicked: toggleProximityLogging()
            }
        }

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Light & Proximity")
            }
            SectionHeader {
                text: qsTr("Brightness")
            }
            Column {
                width: parent.width
                spacing: Theme.paddingSmall

                Label {
                    id: blabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: 'Brightness: ' + page.formatNumber(lightsensor.brightness)
                }
                PlotWidget {
                    id: bplot
                    width: parent.width
                    height: 150
                    plotColor: Theme.highlightColor
                    scaleColor: Theme.secondaryHighlightColor
                }
            }
            SectionHeader {
                text: qsTr("Proximity")
            }
            Label {
                id: proximityLabel
                font.pixelSize: Theme.fontSizeLarge
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: proximitysensor.detected
                font.strikeout: !proximitysensor.detected
                color: {
                    if(proximitysensor.detected) {
                        return Theme.highlightColor;
                    } else {
                        return Theme.secondaryColor;
                    }
                }
                text: qsTr('Proximity detected')
            }
        }
    }
}


