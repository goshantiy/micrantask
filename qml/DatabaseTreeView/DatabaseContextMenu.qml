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
        text: "Expand tree"
        onTriggered: {
            console.log("Expand index", clickedIndex)
            databaseTreeView.expandAllItems(databaseTreeView.rootIndex)
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
            databaseTreeView.collapseAllItems(databaseTreeView.rootIndex)
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
        id: copyToCacheTree
        text: "Load subtree"
        onTriggered: {
            console.log("copy subtree to cache call")
            console.log(clickedIndex)
            cacheModel.copySubtree(clickedIndex)
        }

        contentItem: Text {
            text: copyToCacheTree.text
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
        id:copyToCacheItem
        text: "Load item"
        onTriggered: {
            console.log("copy node to cache call")
            console.log(clickedIndex)
            cacheModel.copyNode(clickedIndex)
        }

        contentItem: Text {
            text: copyToCacheItem.text
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
}
