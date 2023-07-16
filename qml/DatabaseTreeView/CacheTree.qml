import QtQuick 2.15
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4

Item {
    TreeView {
        model: cacheModel
        SystemPalette {
            id: palette
            colorGroup: SystemPalette.Active
        }
        id: cacheTreeView
        anchors.fill: parent
        headerVisible: true
        backgroundVisible: false
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
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
        rowDelegate: Item {
            Rectangle {
                width: parent.width
                height: parent.height
                color: (model.deleted ? Qt.rgba(
                                            176 / 255, 68 / 255, 68 / 255,
                                            0.5) : styleData.selected ? palette.highlight : palette.window)
            }
        }
        TableViewColumn {
            role: "id"
            title: "id"
            width: cacheTreeView.width / 2
        }

        TableViewColumn {
            role: "value"
            title: "value"
            width: cacheTreeView.width / 2
            delegate: TextInput {
                readOnly: model.deleted
                anchors.centerIn: parent
                text: styleData.value
                color: palette.text
                onEditingFinished: {
                    console.log(styleData.index)
                    cacheModel.setData(styleData.index, text)
                }
            }
        }

        function expandAllItems(item) {
            cacheTreeView.expand(item)
            for (var i = 0; i < cacheTreeView.model.rowCount(item); i++) {
                var childItem = cacheTreeView.model.index(i, 0, item)
                expandAllItems(childItem)
            }
        }
        function collapseAllItems(item) {
            cacheTreeView.collapse(item)
            for (var i = 0; i < cacheTreeView.model.rowCount(item); i++) {
                var childItem = cacheTreeView.model.index(i, 0, item)
                collapseAllItems(childItem)
            }
        }
    }
    Keys.onReleased: {
        if (event.key === Qt.Key_C && (event.modifiers & Qt.ControlModifier)) {
            cacheModel.createNode(cacheTreeView.currentIndex)
            cacheTreeView.expand(cacheTreeView.currentIndex)
        }
        if (event.key === Qt.Key_E && (event.modifiers & Qt.ControlModifier)) {
            cacheTreeView.expandAllItems(cacheTreeView.rootIndex)
        }
        if (event.key === Qt.Key_W && (event.modifiers & Qt.ControlModifier)) {
            cacheTreeView.collapseAllItems(cacheTreeView.rootIndex)
        }
        if (event.key === Qt.Key_M && (event.modifiers & Qt.ControlModifier)) {
            cacheModel.moveChangesToDatabase()
        }
        if (event.key === Qt.Key_D && (event.modifiers & Qt.ControlModifier)) {
            cacheModel.markDeleted(cacheTreeView.currentIndex)
        }
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onReleased: {
            var contextMenuComponent = Qt.createComponent(
                        "CacheContextMenu.qml")
            if (contextMenuComponent.status === Component.Ready) {
                var index = cacheTreeView.indexAt(mouse.x, mouse.y)
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
