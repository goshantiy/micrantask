import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.2

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
            console.log("index", clickedIndex)
            cacheTreeView.expandAllItems(cacheTreeView.rootIndex)
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
            cacheTreeView.collapseAllItems(cacheTreeView.rootIndex)
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
        id: createItem
        onTriggered: {
            console.log("index", clickedIndex)
            cacheModel.createNode(clickedIndex)
        }

        contentItem: Text {
            text: "Create child (Ctrl + C)"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: createItem.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }

    MenuItem {
        id: deleteItem
        onTriggered: {
            console.log("delete call")
            console.log(clickedIndex)
            cacheModel.markDeleted(clickedIndex)
        }

        contentItem: Text {
            text: "Delete item (Ctrl + D)"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: deleteItem.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
    MenuItem {
        id: moveChangesFromCache
        onTriggered: {
            console.log("Move cache changes call")
            cacheModel.moveChangesToDatabase()
        }

        contentItem: Text {
            text: "Move all changes (Ctrl + M)"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: moveChangesFromCache.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
    MenuItem {
        id: deleteFromCache
        onTriggered: {
            console.log("Delete from Cache")
            cacheModel.deleteFromCache(clickedIndex)
        }

        contentItem: Text {
            text: "Delete from Cache"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: deleteFromCache.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
    MenuItem {
        id: clearCache
        onTriggered: {
            console.log("Clear Cache")
            cacheModel.clear()
        }

        contentItem: Text {
            text: "Clear Cache"
            color: palette.windowText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 20
            color: clearCache.hovered ? palette.highlight : palette.window
            border.color: "black"
        }
    }
}
