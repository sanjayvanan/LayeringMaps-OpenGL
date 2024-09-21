import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import CustomComponents 1.0

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Shapefile Viewer")

    ShapefileRenderer {
        id: shapefileRenderer
        anchors.fill: parent

        Component.onCompleted: {
            console.log("ShapefileRenderer size:", width, "x", height)
        }

        PinchArea {
            anchors.fill: parent
            pinch.target: shapefileRenderer
            pinch.minimumScale: 0.1
            pinch.maximumScale: 50

            onPinchUpdated: {
                shapefileRenderer.zoom = pinch.scale
            }

            MouseArea {
                anchors.fill: parent
                property point lastPos

                onPressed: {
                    lastPos = Qt.point(mouseX, mouseY)
                }

                onPositionChanged: {
                    if (pressed) {
                        var delta = Qt.point(mouseX - lastPos.x, mouseY - lastPos.y)
                        shapefileRenderer.center = Qt.point(
                            shapefileRenderer.center.x - delta.x / (shapefileRenderer.width * shapefileRenderer.zoom),
                            shapefileRenderer.center.y - delta.y / (shapefileRenderer.height * shapefileRenderer.zoom)
                        )
                        lastPos = Qt.point(mouseX, mouseY)
                    }
                }

                onWheel: {
                    var zoomFactor = 1.2
                    if (wheel.angleDelta.y > 0) {
                        shapefileRenderer.zoom *= zoomFactor
                    } else {
                        shapefileRenderer.zoom /= zoomFactor
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        width: 200
        height: 300
        color: "white"
        border.color: "black"

        ListView {
            anchors.fill: parent
            model: shapefileRenderer.availableLayers
            delegate: CheckBox {
                text: modelData
                checked: shapefileRenderer.selectedLayers.indexOf(modelData) !== -1
                onCheckedChanged: shapefileRenderer.toggleLayer(modelData)
            }
        }
    }

    Component.onCompleted: {
        console.log("Window size:", width, "x", height)
    }
}