#include <QPainter>
#include <QDateTime>
#include <qmath.h>

#include "satelliteposwidget.h"

void SatellitePosWidget::updateMinMax()
{
    m_minSignal =  1e20;
    m_maxSignal = -1e20;

    for(int id: m_satellites.keys()) {
        const SatelliteData &sd = m_satellites[id];

        if(sd.signalStrength < m_minSignal) {
            m_minSignal = sd.signalStrength;
        }

        if(sd.signalStrength > m_maxSignal) {
            m_maxSignal = sd.signalStrength;
        }
    }

    // prevent zero range
    if(m_maxSignal == m_minSignal) {
        m_minSignal -= 1;
    }

    qDebug() << "max: " << m_maxSignal << " min: " << m_minSignal;
}

SatellitePosWidget::SatellitePosWidget(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    SatelliteData sd;
    sd.azimuth = 45;
    sd.elevation = 30;
    sd.inUse = true;
    sd.lastUpdated = 0;
    sd.signalStrength = -30;

    m_satellites.insert(0, sd);

    sd.azimuth = 234;
    sd.elevation = 80;
    sd.signalStrength = -40;
    sd.inUse = false;

    m_satellites.insert(1, sd);

    sd.azimuth = 0;
    sd.elevation = 0;
    sd.signalStrength = -50;
    sd.inUse = false;

    m_satellites.insert(2, sd);

    updateMinMax();
}

void SatellitePosWidget::paint(QPainter *painter)
{
    int radius = 0;

    QPen scalePen(m_scaleColor);
    scalePen.setWidth(1);

    QPoint center(this->width()/2, this->height()/2);

    // determine radius
    if(this->width() > this->height()) {
        radius = this->height() * (0.95 * 0.5);
    } else {
        radius = this->width() * (0.95 * 0.5);
    }

    // minimum and maximum size of satellite points
    qreal minSize = radius * 0.02;
    qreal maxSize = radius * 0.05;

    // draw the background scale indicator
    painter->setPen(scalePen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawEllipse(center, radius, radius);
    painter->drawEllipse(center, (int)(0.6667 * radius), (int)(0.6667 * radius));
    painter->drawEllipse(center, (int)(0.3333 * radius), (int)(0.3333 * radius));

    QPoint offsetStart(0, -radius);
    QPoint offsetEnd(0,  radius);

    for(int angle = 0; angle < 180; angle += 45) {
        QTransform t;
        t.rotate(angle);

        QPoint mappedStart = t.map(offsetStart);
        QPoint mappedEnd = t.map(offsetEnd);

        painter->drawLine(center + mappedStart, center + mappedEnd);
    }

    QBrush usedBrush(m_usedColor);
    QBrush visibleBrush(m_visibleColor);

    painter->setPen(Qt::NoPen); // clear pen, no border

    for(int id: m_satellites.keys()) {
        const SatelliteData &sd = m_satellites[id];

        // determine where to render the satellite by rotating and scaling the "north" unit vector
        QTransform t;
        t.rotate(sd.azimuth);

        qreal scale = radius * (1.0 - sd.elevation / 90.0);
        t.scale(scale, scale);

        QPointF satPos = t.map(QPointF(0, -1));

        // set the brush to use
        if(sd.inUse) {
            painter->setBrush(usedBrush);
        } else {
            painter->setBrush(visibleBrush);
        }

        qreal sizeFactor = (sd.signalStrength - m_minSignal) / (m_maxSignal - m_minSignal);

        qreal satRadius = minSize + sizeFactor * (maxSize - minSize);

        painter->drawEllipse(center + satPos, satRadius, satRadius);

        qDebug() << "Drawing satellite #" << id << " at " << satPos << " with radius " << satRadius << " (signal: " << sd.signalStrength << ", size factor " << sizeFactor << ")";
    }
}

// FIXME: Manage InUse flag for internal satellite list

void SatellitePosWidget::setSatellitesInUse(const QList<QGeoSatelliteInfo> &satellites)
{
    for(const QGeoSatelliteInfo &sat: satellites) {
        SatelliteData sd;

        sd.inUse = true;
        sd.azimuth = sat.attribute(QGeoSatelliteInfo::Azimuth);
        sd.elevation = sat.attribute(QGeoSatelliteInfo::Elevation);
        sd.signalStrength = sat.signalStrength();
        sd.lastUpdated = QDateTime::currentMSecsSinceEpoch();
        sd.satelliteSystem = sat.satelliteSystem();

        SatelliteMap::Iterator iter = m_satellites.find(sat.satelliteIdentifier());

        if(iter != m_satellites.end()) {
            // entry already exists
            *iter = sd;
        } else {
            m_satellites.insert(sat.satelliteIdentifier(), sd);
        }
    }

    updateMinMax();
}

void SatellitePosWidget::setSatellitesInView(const QList<QGeoSatelliteInfo> &satellites)
{
    for(const QGeoSatelliteInfo &sat: satellites) {
        SatelliteData sd;

        sd.inUse = false;
        sd.azimuth = sat.attribute(QGeoSatelliteInfo::Azimuth);
        sd.elevation = sat.attribute(QGeoSatelliteInfo::Elevation);
        sd.signalStrength = sat.signalStrength();
        sd.lastUpdated = QDateTime::currentMSecsSinceEpoch();
        sd.satelliteSystem = sat.satelliteSystem();

        SatelliteMap::Iterator iter = m_satellites.find(sat.satelliteIdentifier());

        if(iter != m_satellites.end()) {
            // entry already exists
            *iter = sd;
        } else {
            m_satellites.insert(sat.satelliteIdentifier(), sd);
        }
    }

    updateMinMax();
}
