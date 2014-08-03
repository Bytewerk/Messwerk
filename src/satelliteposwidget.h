#ifndef SATELLITEPOSWIDGET_H
#define SATELLITEPOSWIDGET_H

#include <QQuickPaintedItem>
#include <QGeoSatelliteInfo>

class SatellitePosWidget : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QColor visibleColor READ visibleColor WRITE setvisibleColor)
    Q_PROPERTY(QColor usedColor READ usedColor WRITE setusedColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setscaleColor)

public:
    struct SatelliteData {
        qreal  azimuth;         // in Degrees
        qreal  elevation;       // in Degrees
        int    signalStrength;  // in dB
        bool   inUse;
        qint64 lastUpdated;     // in milliseconds
        QGeoSatelliteInfo::SatelliteSystem satelliteSystem;
    };

private:
    typedef QMap<int, SatelliteData> SatelliteMap;

    QColor m_usedColor;
    QColor m_visibleColor;
    QColor m_scaleColor;

    SatelliteMap m_satellites;

    qreal m_minSignal;
    qreal m_maxSignal;

    void updateMinMax(void);

public:
    explicit SatellitePosWidget(QQuickItem *parent = 0);

    void paint(QPainter *painter);

    void setvisibleColor(const QColor &color) { m_visibleColor = color; }
    void setusedColor(const QColor &color) { m_usedColor = color; }
    void setscaleColor(const QColor &color) { m_scaleColor = color; }

    const QColor& visibleColor() { return m_visibleColor; }
    const QColor& usedColor() { return m_usedColor; }
    const QColor& scaleColor() { return m_scaleColor; }

signals:

public slots:
    void setSatellitesInUse(const QList<QGeoSatelliteInfo> &satellites);
    void setSatellitesInView(const QList<QGeoSatelliteInfo> &satellites);

};

#endif // SATELLITEPOSWIDGET_H
