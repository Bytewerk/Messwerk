#include <QPainter>
#include <QDateTime>
#include <qmath.h>

#include "satelliteposwidget.h"

SatellitePosWidget::SatellitePosWidget(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void SatellitePosWidget::paint(QPainter *painter)
{
    int radius = 0;

    QPen scalePen(m_scaleColor);
    scalePen.setWidth(1);

    QPen northPen(scalePen);
    northPen.setColor(m_northColor);
    northPen.setWidth(3);

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

    QPoint offsetEnd(0,  radius);

    for(int angle = 0; angle < 360; angle += 45) {
        QTransform t;
        t.rotate(angle + m_northDirection);

        QPoint mappedEnd = t.map(offsetEnd);

        // draw first (north) line in northColor
        if(angle == 0) {
            painter->setPen(northPen);
        } else {
            painter->setPen(scalePen);
        }

        painter->drawLine(center, center + mappedEnd);
    }

    if(!m_satelliteInfo) {
        return;
    }

    QBrush usedBrush(m_usedColor);
    QBrush visibleBrush(m_visibleColor);

    QPen usedPen(m_usedColor);
    QPen visiblePen(m_visibleColor);

    usedPen.setColor(m_usedColor);
    visiblePen.setColor(m_visibleColor);

    for(int id: m_satelliteInfo->allSatellites()) {
        const SatelliteInfo::SatelliteData &sd = (*m_satelliteInfo)[id];

        // determine where to render the satellite by rotating and scaling the "north" unit vector
        QTransform t;
        t.rotate(sd.azimuth + m_northDirection);

        qreal scale = radius * (1.0 - sd.elevation / 90.0);
        t.scale(scale, scale);

        QPointF satPos = t.map(QPointF(0, -1));

        // set the brush to use
        if(sd.inUse) {
            painter->setBrush(usedBrush);
        } else {
            painter->setBrush(visibleBrush);
        }

        painter->setPen(Qt::NoPen); // clear pen, no border

        qreal minSignal = m_satelliteInfo->minSignal();
        qreal maxSignal = m_satelliteInfo->maxSignal();

        qreal sizeFactor = (sd.signalStrength - minSignal) / (maxSignal - minSignal);

        qreal satRadius = minSize + sizeFactor * (maxSize - minSize);
        QPointF satCenter = center + satPos;

        painter->drawEllipse(satCenter, satRadius, satRadius);

        // draw label of the satellite
        if(sd.inUse) {
            painter->setPen(usedPen);
        } else {
            painter->setPen(visiblePen);
        }

        QString text = QLocale::system().toString(id);
        painter->drawText(QRect(satCenter.x() + satRadius + 2, satCenter.y(), 0, 0), Qt::AlignVCenter | Qt::AlignLeft | Qt::TextDontClip, text);
    }
}

void SatellitePosWidget::setnorthDirection(qreal arg)
{
    if (m_northDirection != arg) {
        m_northDirection = arg;
        emit northDirectionChanged(arg);
    }
}
