import QtQuick 2.0
import Sailfish.Silica 1.0
import MesswerkWidgets 1.0

import "../Constants.js" as Constants

Page {
    id: page

    property bool useGs: false;

    function formatNumber(n) {
        var unit;

        if(useGs) {
            n /= 9.81;
            unit = 'g';
        } else {
            unit = 'm/s²'
        }

        return '<b>' + n.toFixed(3) + ' ' + unit + '</b>';
    }

    function updateAbsPlot() {
        absplot.addValue(accelerometer.abs);
        absplot.update();
    }

    Component.onCompleted: {
        accelerometer.activate(Constants.PART_PAGE);
        accelerometer.absChanged.connect(updateAbsPlot);
    }

    Component.onDestruction: accelerometer.deactivate(Constants.PART_PAGE)

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                function toggleUnit() {
                    useGs = !useGs;
                }

                text: qsTr("Change unit to " + (useGs ? 'm/s²' : 'g'))
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
                title: qsTr("Accelerometer")
            }
            Label {
                id: xlabel
                font.pixelSize: Theme.fontSizeLarge
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                text: 'X: ' + page.formatNumber(accelerometer.ax)
            }
            Label {
                id: ylabel
                font.pixelSize: Theme.fontSizeLarge
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                text: 'Y: ' + page.formatNumber(accelerometer.ay)
            }
            Label {
                id: zlabel
                font.pixelSize: Theme.fontSizeLarge
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                text: 'Z: ' + page.formatNumber(accelerometer.az)
            }
            Label {
                id: abslabel
                font.pixelSize: Theme.fontSizeLarge
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                text: 'Absolute: ' + page.formatNumber(accelerometer.abs)
            }
            PlotWidget {
                id: absplot
                width: parent.width
                height: 200
                plotColor: Theme.highlightColor
                scaleColor: Theme.secondaryHighlightColor
            }
            Label {
                id: absnogravlabel
                font.pixelSize: Theme.fontSizeLarge
                anchors.right: parent.right
                anchors.rightMargin: Theme.paddingLarge
                text: 'Without gravity: ' + page.formatNumber(accelerometer.abs - 9.81)
            }
        }
    }
}


