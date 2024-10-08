#include "shapefilerenderer.h"
#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>
#include <QFile>
#include <QDataStream>
#include <QDir>
#include <QDebug>
#include <random>

ShapefileRenderer::ShapefileRenderer()
    : m_minX(std::numeric_limits<double>::max()), m_minY(std::numeric_limits<double>::max()),
      m_maxX(std::numeric_limits<double>::lowest()), m_maxY(std::numeric_limits<double>::lowest()),
      m_zoom(1.0), m_center(0.5, 0.5), m_lndareVisible(true)
{
    setFlag(QQuickItem::ItemHasContents, true);
    loadShapefiles("C:/Zosh Aerospace/Projects/one/rendering-maps/basemap_shp");
    loadLndareShapefile("C:/Zosh Aerospace/Projects/one/rendering-maps/basemap_shp");
    loadMyGeoDataShapefiles("C:/Zosh Aerospace/Projects/one/rendering-maps/mygeodata");
    qDebug() << "Constructor finished. MyGeoData layers:" << m_myGeoDataPolygons.size();
}

void ShapefileRenderer::setZoom(qreal zoom)
{
    if (qFuzzyCompare(m_zoom, zoom))
        return;

    // Increase the maximum zoom level (e.g., from 10.0 to 50.0)
    m_zoom = qBound(0.1, zoom, 50.0);
    emit zoomChanged();
    update();
}

void ShapefileRenderer::setCenter(const QPointF &center)
{
    if (m_center == center)
        return;

    m_center = center;
    emit centerChanged();
    update();
}

void ShapefileRenderer::setLndareVisible(bool visible)
{
    if (m_lndareVisible == visible)
        return;

    m_lndareVisible = visible;
    emit lndareVisibleChanged();
    update();
}

QSGNode *ShapefileRenderer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGNode *parentNode = oldNode;
    if (!parentNode) {
        parentNode = new QSGNode;
    }

    // Clear existing child nodes
    while (parentNode->childCount() > 0) {
        parentNode->removeChildNode(parentNode->childAtIndex(0));
    }

    // Render base map
    QSGGeometryNode *baseMapNode = createGeometryNode(m_polygons, QColor(200, 200, 255));
    parentNode->appendChildNode(baseMapNode);

    // Render LNDARE layer if visible
    if (m_lndareVisible) {
        QSGGeometryNode *lndareNode = createGeometryNode(m_lndarePolygons, QColor(139, 69, 19));
        parentNode->appendChildNode(lndareNode);
    }

    // Render selected layers
    for (const QString &layerName : m_selectedLayers) {
        if (m_layerPolygons.contains(layerName)) {
            QSGGeometryNode *polygonNode = createGeometryNode(m_layerPolygons[layerName], m_layerColors[layerName]);
            parentNode->appendChildNode(polygonNode);
        }
        if (m_layerPoints.contains(layerName)) {
            QSGGeometryNode *pointNode = createPointGeometryNode(m_layerPoints[layerName], m_layerColors[layerName]);
            parentNode->appendChildNode(pointNode);
        }
    }

    return parentNode;
}

void ShapefileRenderer::loadShapefiles(const QString &folderPath)
{
    QDir dir(folderPath);
    QStringList shapefiles = dir.entryList(QStringList() << "*.shp", QDir::Files);
    qDebug() << "Found" << shapefiles.size() << "shapefiles in" << folderPath;

    for (const QString &shapefile : shapefiles) {
        if (shapefile.toLower() != "lndare.shp") {
            loadShapefile(dir.filePath(shapefile), m_polygons);
        }
    }

    qDebug() << "Loaded" << m_polygons.size() << "polygons from base shapefiles";
}

void ShapefileRenderer::loadShapefile(const QString &path, QVector<QVector<QVector2D>> &polygons)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open shapefile:" << path;
        return;
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);

    // Skip header
    stream.skipRawData(100);

    while (!stream.atEnd()) {
        qint32 recordNumber, contentLength;
        stream >> recordNumber >> contentLength;

        qint32 shapeType;
        stream >> shapeType;

        if (shapeType == 5) { // Polygon
            double xMin, yMin, xMax, yMax;
            stream >> xMin >> yMin >> xMax >> yMax;

            qint32 numParts, numPoints;
            stream >> numParts >> numPoints;

            QVector<qint32> parts(numParts);
            for (int i = 0; i < numParts; ++i) {
                stream >> parts[i];
            }

            QVector<QVector2D> polygon;
            for (int i = 0; i < numPoints; ++i) {
                double x, y;
                stream >> x >> y;
                polygon.append(QVector2D(x, y));

                m_minX = qMin(m_minX, x);
                m_minY = qMin(m_minY, y);
                m_maxX = qMax(m_maxX, x);
                m_maxY = qMax(m_maxY, y);
            }

            polygons.append(polygon);
        } else {
            // Skip unsupported shape types
            stream.skipRawData(contentLength * 2 - 4);
        }
    }

    qDebug() << "Loaded" << polygons.size() << "polygons from" << path;
}

void ShapefileRenderer::loadLndareShapefile(const QString &folderPath)
{
    QString lndarePath = QDir(folderPath).filePath("LNDARE.shp");
    loadShapefile(lndarePath, m_lndarePolygons);
    qDebug() << "Loaded" << m_lndarePolygons.size() << "LNDARE polygons";
}

void ShapefileRenderer::loadMyGeoDataShapefiles(const QString &folderPath)
{
    QDir dir(folderPath);
    QStringList shapefiles = dir.entryList(QStringList() << "*.shp", QDir::Files);
    qDebug() << "Found" << shapefiles.size() << "shapefiles in" << folderPath;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    for (const QString &shapefile : shapefiles) {
        QString layerName = QFileInfo(shapefile).baseName();
        m_availableLayers.append(layerName);

        QVector<QVector<QVector2D>> polygons;
        QVector<QVector2D> points;
        loadShapefile(dir.filePath(shapefile), polygons);
        loadPointShapefile(dir.filePath(shapefile), points);

        if (!polygons.isEmpty() || !points.isEmpty()) {
            m_layerPolygons[layerName] = polygons;
            m_layerPoints[layerName] = points;
            QColor color(distrib(gen), distrib(gen), distrib(gen));
            m_layerColors[layerName] = color;
        }
    }

    emit availableLayersChanged();
}

void ShapefileRenderer::loadPointShapefile(const QString &path, QVector<QVector2D> &points)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open shapefile:" << path;
        return;
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);

    // Skip header
    stream.skipRawData(100);

    while (!stream.atEnd()) {
        qint32 recordNumber, contentLength;
        stream >> recordNumber >> contentLength;

        qint32 shapeType;
        stream >> shapeType;

        if (shapeType == 1) { // Point
            double x, y;
            stream >> x >> y;
            points.append(QVector2D(x, y));

            m_minX = qMin(m_minX, x);
            m_minY = qMin(m_minY, y);
            m_maxX = qMax(m_maxX, x);
            m_maxY = qMax(m_maxY, y);
        } else {
            // Skip unsupported shape types
            stream.skipRawData(contentLength * 2 - 4);
        }
    }

    qDebug() << "Loaded" << points.size() << "points from" << path;
}

QSGGeometryNode *ShapefileRenderer::createGeometryNode(const QVector<QVector<QVector2D>> &polygons, const QColor &color)
{
    QSGGeometryNode *node = new QSGGeometryNode;
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    int totalPoints = 0;
    for (const auto &polygon : polygons) {
        totalPoints += polygon.size() * 2;  // Each line segment needs 2 points
    }

    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), totalPoints);
    geometry->setDrawingMode(QSGGeometry::DrawLines);
    geometry->setLineWidth(1);
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    int index = 0;
    qreal mapWidth = m_maxX - m_minX;
    qreal mapHeight = m_maxY - m_minY;

    for (const auto &polygon : polygons) {
        for (int i = 0; i < polygon.size(); ++i) {
            QVector2D point = polygon[i];
            qreal x = (point.x() - m_minX) / mapWidth;
            qreal y = (point.y() - m_minY) / mapHeight;
            
            // Apply zoom and center
            x = (x - m_center.x()) * m_zoom + 0.5;
            y = (y - m_center.y()) * m_zoom + 0.5;
            
            // Clamp the coordinates to prevent rendering outside the visible area
            x = qBound(0.0, x, 1.0);
            y = qBound(0.0, y, 1.0);
            
            vertices[index].set(x * width(), (1 - y) * height());
            index++;

            QVector2D nextPoint = polygon[(i + 1) % polygon.size()];
            qreal nextX = (nextPoint.x() - m_minX) / mapWidth;
            qreal nextY = (nextPoint.y() - m_minY) / mapHeight;
            
            // Apply zoom and center
            nextX = (nextX - m_center.x()) * m_zoom + 0.5;
            nextY = (nextY - m_center.y()) * m_zoom + 0.5;
            
            // Clamp the coordinates to prevent rendering outside the visible area
            nextX = qBound(0.0, nextX, 1.0);
            nextY = qBound(0.0, nextY, 1.0);
            
            vertices[index].set(nextX * width(), (1 - nextY) * height());
            index++;
        }
    }

    qDebug() << "Created geometry node with" << totalPoints << "points for color" << color.name();

    return node;
}

QSGGeometryNode *ShapefileRenderer::createPointGeometryNode(const QVector<QVector2D> &points, const QColor &color)
{
    QSGGeometryNode *node = new QSGGeometryNode;
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), points.size());
    geometry->setDrawingMode(QSGGeometry::DrawPoints);
    geometry->setLineWidth(5); // Adjust point size as needed
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    qreal mapWidth = m_maxX - m_minX;
    qreal mapHeight = m_maxY - m_minY;

    for (int i = 0; i < points.size(); ++i) {
        QVector2D point = points[i];
        qreal x = (point.x() - m_minX) / mapWidth;
        qreal y = (point.y() - m_minY) / mapHeight;
        
        // Apply zoom and center
        x = (x - m_center.x()) * m_zoom + 0.5;
        y = (y - m_center.y()) * m_zoom + 0.5;
        
        // Clamp the coordinates to prevent rendering outside the visible area
        x = qBound(0.0, x, 1.0);
        y = qBound(0.0, y, 1.0);
        
        vertices[i].set(x * width(), (1 - y) * height());
    }

    qDebug() << "Created point geometry node with" << points.size() << "points for color" << color.name();

    return node;
}

void ShapefileRenderer::setSelectedLayers(const QStringList &layers)
{
    if (m_selectedLayers != layers) {
        m_selectedLayers = layers;
        emit selectedLayersChanged();
        update();
    }
}

void ShapefileRenderer::toggleLayer(const QString &layerName)
{
    if (m_selectedLayers.contains(layerName)) {
        m_selectedLayers.removeAll(layerName);
    } else {
        m_selectedLayers.append(layerName);
    }
    emit selectedLayersChanged();
    update();
}