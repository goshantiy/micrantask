import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Menu {
    id: contextMenu
    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }
    property var clickedIndex
    MenuItem {
        id: expandAllItem
        onTriggered: {
            console.log("Expand index", clickedIndex)
            databaseTreeView.expandAllItems(databaseTreeView.rootIndex)
        }

        contentItem: Text {
            text: "Expand tree (Ctrl + E)"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: expandAllItem.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
    MenuItem {
        id: collapseAllItem
        onTriggered: {
            console.log("index", clickedIndex)
            databaseTreeView.collapseAllItems(databaseTreeView.rootIndex)
        }

        contentItem: Text {
            text: "Collapse tree (Ctrl + W)"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: collapseAllItem.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
    MenuItem {
        id: copyToCacheTree
        onTriggered: {
            console.log("copy subtree to cache call")
            console.log(clickedIndex)
            databaseModel.moveSubtree(clickedIndex)
        }

        contentItem: Text {
            text: "Load subtree (Ctrl + Shift + C)"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: copyToCacheTree.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
    MenuItem {
        id: copyToCacheItem
        onTriggered: {
            console.log("copy node to cache call")
            console.log(clickedIndex)
            databaseModel.moveNode(clickedIndex)
        }

        contentItem: Text {
            text: "Load item (Ctrl + C)"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: copyToCacheItem.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
    MenuItem {
        id: resetDb
        onTriggered: {
            console.log("resetDb")
            console.log(clickedIndex)
            databaseModel.resetDatabase()
        }

        contentItem: Text {
            text: "Reset database"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: resetDb.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
}
