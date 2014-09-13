import QtQuick 2.0
import Sailfish.Silica 1.0
import MesswerkWidgets 1.0

import "../Constants.js" as Constants

Page {
    id: page

    property bool useRad: false;

    function convertNumber(n) {
        if(useRad) {
            n *= 0.017453; // *pi/180
        }

        return n;
    }

    function formatNumber(n) {
        var unit;

        if(useRad) {
            unit = 'rad';
        } else {
            unit = '°'
        }

        return '<b>' + convertNumber(n).toFixed(3) + ' ' + unit + '</b>';
    }

    function updateXPlot() {
        xplot.addValue(convertNumber(rotationsensor.rx));
        xplot.update();
    }

    function updateYPlot() {
        yplot.addValue(convertNumber(rotationsensor.ry));
        yplot.update();
    }

    function updateZPlot() {
        zplot.addValue(convertNumber(rotationsensor.rz));
        zplot.update();
    }

    Component.onCompleted: {
        rotationsensor.activate(Constants.PART_PAGE)
        rotationsensor.rxChanged.connect(updateXPlot);
        rotationsensor.ryChanged.connect(updateYPlot);
        rotationsensor.rzChanged.connect(updateZPlot);
    }

    Component.onDestruction: {
        rotationsensor.rxChanged.disconnect(updateXPlot);
        rotationsensor.ryChanged.disconnect(updateYPlot);
        rotationsensor.rzChanged.disconnect(updateZPlot);
        rotationsensor.deactivate(Constants.PART_PAGE)
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                function toggleLogging() {
                    if(rotationsensor.isLogging) {
                        rotationsensor.stopLogging();
                    } else {
                        rotationsensor.startLogging();
                    }
                }

                text: (rotationsensor.isLogging ? qsTr("Stop") : qsTr("Start")) + qsTr(" logging")
                onClicked: toggleLogging()
            }
            MenuItem {
                function toggleUnit() {
                    useRad = !useRad;

                    xplot.reset();
                    yplot.reset();
                    zplot.reset();
                }

                text: qsTr("Change unit to " + (useRad ? '°' : 'rad'))
                onClicked: toggleUnit()
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
                title: qsTr("Rotation")
            }
            Column {
                width: parent.width
                spacing: Theme.paddingSmall

                Label {
                    id: xlabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: 'X: ' + page.formatNumber(rotationsensor.rx)
                }
                PlotWidget {
                    id: xplot
                    width: parent.width
                    height: 150
                    plotColor: Theme.highlightColor
                    scaleColor: Theme.secondaryHighlightColor
                }
            }
            Column {
                width: parent.width
                spacing: Theme.paddingSmall

                Label {
                    id: ylabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: 'Y: ' + page.formatNumber(rotationsensor.ry)
                }
                PlotWidget {
                    id: yplot
                    width: parent.width
                    height: 150
                    plotColor: Theme.highlightColor
                    scaleColor: Theme.secondaryHighlightColor
                }
            }
            Column {
                width: parent.width
                spacing: Theme.paddingSmall

                Label {
                    id: zlabel
                    font.pixelSize: Theme.fontSizeLarge
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingLarge
                    text: 'Z: ' + page.formatNumber(rotationsensor.rz)
                }
                PlotWidget {
                    id: zplot
                    width: parent.width
                    height: 150
                    plotColor: Theme.highlightColor
                    scaleColor: Theme.secondaryHighlightColor
                }
            }
        }
    }
}


