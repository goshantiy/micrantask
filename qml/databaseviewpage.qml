import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15
import "DatabaseTreeView"

ApplicationWindow {
    id: window
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: "micrantask"
    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }
    color: palette.alternateBase
    SplitView {
        anchors.fill: parent
        CacheTree {
            Layout.minimumWidth: 300
            Layout.maximumWidth: parent.width - 200
            Layout.fillHeight: true
        }
        DatabaseTree {
            Layout.minimumWidth: 300
            Layout.maximumWidth: parent.width - 200
            Layout.fillHeight: true
        }
        handleDelegate: Rectangle {
            width: 2
            color: palette.alternateBase
        }
    }
}
