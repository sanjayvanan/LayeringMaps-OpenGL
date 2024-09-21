#pragma once

#include <QQuickItem>
#include <QVector2D>
#include <QPointF>
#include <QColor>

class QSGGeometryNode;

class ShapefileRenderer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(QPointF center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(bool lndareVisible READ lndareVisible WRITE setLndareVisible NOTIFY lndareVisibleChanged)
    Q_PROPERTY(QStringList availableLayers READ availableLayers NOTIFY availableLayersChanged)
    Q_PROPERTY(QStringList selectedLayers READ selectedLayers WRITE setSelectedLayers NOTIFY selectedLayersChanged)

public:
    ShapefileRenderer();

    qreal zoom() const { return m_zoom; }
    void setZoom(qreal zoom);

    QPointF center() const { return m_center; }
    void setCenter(const QPointF &center);

    bool lndareVisible() const { return m_lndareVisible; }
    void setLndareVisible(bool visible);

    QStringList availableLayers() const { return m_availableLayers; }
    QStringList selectedLayers() const { return m_selectedLayers; }
    void setSelectedLayers(const QStringList &layers);

    Q_INVOKABLE void toggleLayer(const QString &layerName);

signals:
    void zoomChanged();
    void centerChanged();
    void lndareVisibleChanged();
    void availableLayersChanged();
    void selectedLayersChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

private:
    void loadShapefiles(const QString &folderPath);
    void loadShapefile(const QString &path, QVector<QVector<QVector2D>> &polygons);
    void loadLndareShapefile(const QString &folderPath);
    void loadMyGeoDataShapefiles(const QString &folderPath);
    QSGGeometryNode *createGeometryNode(const QVector<QVector<QVector2D>> &polygons, const QColor &color);
    void loadPointShapefile(const QString &path, QVector<QVector2D> &points);
    QSGGeometryNode *createPointGeometryNode(const QVector<QVector2D> &points, const QColor &color);

    QVector<QVector<QVector2D>> m_polygons;
    QVector<QVector<QVector2D>> m_lndarePolygons;
    QVector<QVector<QVector<QVector2D>>> m_myGeoDataPolygons;
    QVector<QColor> m_myGeoDataColors;
    double m_minX, m_minY, m_maxX, m_maxY;
    qreal m_zoom;
    QPointF m_center;
    bool m_lndareVisible;
    QVector<QVector<QVector2D>> m_myGeoDataPoints;
    QStringList m_availableLayers;
    QStringList m_selectedLayers;

    QMap<QString, QVector<QVector<QVector2D>>> m_layerPolygons;
    QMap<QString, QVector<QVector2D>> m_layerPoints;
    QMap<QString, QColor> m_layerColors;
};