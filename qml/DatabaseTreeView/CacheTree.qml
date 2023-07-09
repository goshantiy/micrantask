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
                font.pointSize: 18
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
                color: (styleData.selected ? palette.highlight : model.deleted ? Qt.rgba(176 / 255, 68 / 255, 68 / 255, 0.5) : palette.window)
            }
        }
        TableViewColumn {
            role: "id"
            title: "uuid"
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
            }
        }
    }
}
