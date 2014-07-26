import QtQuick 2.0
import Sailfish.Silica 1.0
import MesswerkWidgets 1.0

Page {
    id: page

    property int step: 0;

    function updatePlot() {
        step += 1;

        plot.addValue(Math.sin(2*3.14159*step/100));
        plot.update();
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
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
                title: qsTr("Plot Test Page")
            }
            PlotWidget {
                id: plot
                width: 500
                height: 500
                rotation: 0
                plotColor: Theme.highlightColor
                scaleColor: Theme.secondaryHighlightColor
            }
            Button {
                text: "Replot"
                onClicked: updatePlot()
            }
        }
    }
}


