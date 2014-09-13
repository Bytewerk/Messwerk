import QtQuick 2.0
import Sailfish.Silica 1.0


Dialog {
    id: dialog

    onAccepted: {
        settings.loggingPath = loggingPath.text;
    }


    Column {
        id: column

        width: dialog.width
        spacing: Theme.paddingLarge

        DialogHeader {
            acceptText: qsTr("Save")
        }

        SectionHeader {
            text: qsTr("Logging")
        }

        TextField {
            id: loggingPath
            width: parent.width
            inputMethodHints: Qt.ImhNoAutoUppercase
            text: settings.loggingPath
            label: qsTr("Path for sensor logs")
        }
    }
}





