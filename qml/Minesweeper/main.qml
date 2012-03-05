import QtQuick 1.0
import "Core"
import "fireworksCreation.js" as FireworksManagment

Item {
    id: field
    property int clickx: 0
    property int clicky: 0

    /*Rectangle {
        color: "#777777"
        anchors.fill: parent
    }*/
    Image {
        source: "qrc:/res/background"
        anchors.fill: parent
        fillMode: Image.Tile
    }

    width: 1024
    height: 600

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        columns: 9
        spacing: 1

        Repeater {
            id: repeater
            model: tiles
            delegate: Tile {}
        }
    }

    Row {
        id: gamedata
        x: 20
        spacing: 20
        anchors.bottom: field.bottom
        anchors.bottomMargin: 15

        Column {
            spacing: 2
            Image {
                source: "qrc:/res/mine"
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                text: numMines
            }
        }

        Column {
            spacing: 2
            Image {
                source: "qrc:/res/flag"
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                text: numFlags
            }
        }
    }

    Item {
        id: fireworks
    }

    Image {
        anchors.bottom: field.bottom
        anchors.bottomMargin: 15
        anchors.right: field.right
        anchors.rightMargin: 20
        source: isPlaying ? 'qrc:res/smile' : hasWon ? 'qrc:/res/smile-big' : 'qrc:/res/sad'

        MouseArea {
            anchors.fill: parent
            onPressed: reset()
        }
    }

    Connections {
        target: core
        onHasWonChanged: if (hasWon)
                             FireworksManagment.createFireworks();
    }
}
