import QtQuick 1.1
import "Core"
//import "fireworksCreation.js" as FireworksManagment

Item {
    id: field
    property int clickx: 0
    property int clicky: 0

    Image {
        source: "qrc:/res/background"
        anchors.fill: parent
        fillMode: Image.Stretch
    }

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        columns: 9
        spacing: 10

        Repeater {
            id: repeater
            model: tiles
            delegate: Tile {}
        }
    }

    Row {
        id: gamedata
        x: 25
        spacing: 25
        anchors.bottom: field.bottom
        anchors.bottomMargin: 15

        Column {
            width: 50

            spacing: 4
            Image {
                width: 50
                height: 50
                source: "qrc:/res/mine"
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                text: numMines
            }
        }

        Column {
            spacing: 4
            Image {
                width: 50
                height: 50
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
        width: 100
        height: 100

        MouseArea {
            anchors.fill: parent
            onPressed: reset()
        }
    }

    /*Connections {
        target: core
        onHasWonChanged: if (hasWon)
                             FireworksManagment.createFireworks();
    }*/
}
