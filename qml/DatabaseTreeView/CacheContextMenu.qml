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
        text: "Expand tree"
        onTriggered: {
            console.log("index", clickedIndex)
            cacheTreeView.expandAllItems(cacheTreeView.rootIndex)
        }

        contentItem: Text {
            text: expandAllItem.text
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
        text: "Collapse tree"
        onTriggered: {
            console.log("index", clickedIndex)
            cacheTreeView.collapseAllItems(cacheTreeView.rootIndex)
        }

        contentItem: Text {
            text: collapseAllItem.text
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
        text: "Create child"
        onTriggered: {
            console.log("index", clickedIndex)
            cacheModel.createNode(clickedIndex)
        }

        contentItem: Text {
            text: createItem.text
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
        text: "Delete item"
        onTriggered: {
            console.log("delete call")
            console.log(clickedIndex)
            cacheModel.deleteData(clickedIndex)
        }

        contentItem: Text {
            text: deleteItem.text
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
}
