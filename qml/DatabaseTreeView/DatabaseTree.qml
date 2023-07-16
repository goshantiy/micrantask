import QtQuick 2.0
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.15

Item {
    TreeView {

        SystemPalette {
            id: palette
            colorGroup: SystemPalette.Active
        }
        id: databaseTreeView
        anchors.fill: parent
        headerVisible: true
        backgroundVisible: false
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        rowDelegate: Item {
            Rectangle {
                width: parent.width
                height: parent.height
                color: (styleData.selected ? palette.highlight : model.deleted ? Qt.rgba(176 / 255, 68 / 255, 68 / 255, 0.5) : palette.window)
                Text {
                    anchors.centerIn: parent
                    color: palette.windowText
                }
            }
        }
        headerDelegate: Rectangle {
            height: 20
            color: palette.alternateBase
            border.color: palette.dark
            Text {
                text: styleData.value
                color: palette.windowText
                width: parent.width
                height: parent.height
                font.pointSize: 15
                minimumPointSize: 3
                fontSizeMode: Text.Fit
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        TableViewColumn {
            role: "value"
            title: "value"
            width: databaseTreeView.width / 2
        }

        //        TableViewColumn {
        //            role: "id"
        //            title: "id"
        //            width: databaseTreeView.width / 2
        //        }
        model: databaseModel

        function expandAllItems(item) {
            databaseTreeView.expand(item)
            for (var i = 0; i < databaseTreeView.model.rowCount(item); i++) {
                var childItem = databaseTreeView.model.index(i, 0, item)
                expandAllItems(childItem)
            }
        }
        function collapseAllItems(item) {
            databaseTreeView.collapse(item)
            for (var i = 0; i < databaseTreeView.model.rowCount(item); i++) {
                var childItem = databaseTreeView.model.index(i, 0, item)
                collapseAllItems(childItem)
            }
        }
    }
    Keys.onReleased: {
        if (event.key === Qt.Key_E && (event.modifiers & Qt.ControlModifier)) {
            databaseTreeView.expandAllItems(databaseTreeView.rootIndex)
        }
        if (event.key === Qt.Key_W && (event.modifiers & Qt.ControlModifier)) {
            databaseTreeView.collapseAllItems(databaseTreeView.rootIndex)
        }
        if (event.key === Qt.Key_C && (event.modifiers & Qt.ControlModifier)) {
            if (event.modifiers & Qt.ShiftModifier)
                databaseModel.moveSubtree(databaseTreeView.currentIndex)
            else
                databaseModel.moveNode(databaseTreeView.currentIndex)
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onReleased: {
            var contextMenuComponent = Qt.createComponent(
                        "DatabaseContextMenu.qml")
            if (contextMenuComponent.status === Component.Ready) {
                var index = databaseTreeView.indexAt(mouse.x, mouse.y)
                console.log(index)
                var contextMenu = contextMenuComponent.createObject(parent, {
                                                                        "clickedIndex": index
                                                                    })
                contextMenu.popup()
                contextMenu.closed.connect(function () {
                    contextMenu.destroy()
                })
            }
        }
    }
}
