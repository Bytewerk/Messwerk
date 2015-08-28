import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.messwerk.MesswerkWidgets 1.0

import "../Constants.js" as Constants

Page {
    id: page

    function updateSkyPlot() {
        skyPlot.northDirection = rotationsensor.rz;
        skyPlot.update();
    }

    Component.onCompleted: {
        skyPlot.setSatelliteInfo(satelliteinfo);
        strengthPlot.setSatelliteInfo(satelliteinfo);
        satelliteinfo.newDataAvailable.connect(skyPlot.update)
        satelliteinfo.newDataAvailable.connect(strengthPlot.update)
        satelliteinfo.activate(Constants.PART_PAGE);
        rotationsensor.activate(Constants.PART_PAGE)
        rotationsensor.rzChanged.connect(updateSkyPlot);
    }

    Component.onDestruction: {
        rotationsensor.rzChanged.disconnect(updateSkyPlot);
        satelliteinfo.deactivate(Constants.PART_PAGE);
        rotationsensor.deactivate(Constants.PART_PAGE);
        satelliteinfo.newDataAvailable.disconnect(skyPlot.update)
        satelliteinfo.newDataAvailable.disconnect(strengthPlot.update)
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                function toggleLogging() {
                    if(satelliteinfo.isLogging) {
                        satelliteinfo.stopLogging();
                    } else {
                        satelliteinfo.startLogging();
                    }
                }

                text: (satelliteinfo.isLogging ? qsTr("Stop") : qsTr("Start")) + qsTr(" logging")
                onClicked: toggleLogging()
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
            SatellitePosWidget {
                id: skyPlot
                width: parent.width
                height: parent.width
                visibleColor: Theme.primaryColor
                usedColor: Theme.highlightColor
                scaleColor: Theme.secondaryColor
                northColor: Theme.secondaryHighlightColor
            }
            SatelliteStrengthWidget {
                id: strengthPlot
                width: parent.width
                height: 200
                visibleColor: Theme.primaryColor
                usedColor: Theme.highlightColor
                scaleColor: Theme.secondaryColor
            }
        }
    }
}


