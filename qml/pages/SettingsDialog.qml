import QtQuick 2.0
import Sailfish.Silica 1.0


Dialog {
    id: dialog

    onAccepted: {
        settings.loggingPath = loggingPath.text;
        settings.preventDisplayBlanking = preventDisplayBlanking.checked;
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

        TextSwitch {
            id: preventDisplayBlanking
            text: qsTr("Prevent display blanking")
            description: qsTr("Prevents display blanking on sensor plotting pages")
            checked: settings.preventDisplayBlanking
        }
    }
}
