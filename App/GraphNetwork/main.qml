import QtQuick 2.15
import Qt5Compat.GraphicalEffects
import QtQuick.Controls 2.2

Window
{
    width: 700
    height: 700
    visible: true
    title: qsTr("Graph Network")

    Repeater {
        model: 100

        Rectangle {
            x: Math.random() * parent.width
            y: Math.random() * parent.height
            width: 20
            height: 20
            radius: width/2
            color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
        }
    }
}
