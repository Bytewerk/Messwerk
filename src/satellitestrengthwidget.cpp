#include <QPainter>
#include <QDateTime>
#include <qmath.h>

#include "satellitestrengthwidget.h"

SatelliteStrengthWidget::SatelliteStrengthWidget(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void SatelliteStrengthWidget::paint(QPainter *painter)
{
    if(!m_satelliteInfo) {
        return;
    }

    // init pens
    QPen scalePen(m_scaleColor);
    scalePen.setWidth(1);

    QPen usedPen(m_usedColor);
    QPen visiblePen(m_visibleColor);

    usedPen.setColor(m_usedColor);
    visiblePen.setColor(m_visibleColor);

    // init brushes
    QBrush usedBrush(m_usedColor);
    QBrush visibleBrush(m_visibleColor);

    // init font
    QFont font = painter->font();
    font.setPixelSize(font.pixelSize() * 0.7);
    //font.setBold(true);
    painter->setFont(font);

    QFontMetrics fontMetrics(font);

    // determine height of graph text
    int textheight = fontMetrics.height();

    // label texts
    int minSignal = m_satelliteInfo->minSignal();
    int maxSignal = m_satelliteInfo->maxSignal();

    QString minLabel(QLocale::system().toString(minSignal));
    QString maxLabel(QLocale::system().toString(maxSignal));

    // determine number of label lines to use
    int scaleLabelWidth = qMax(fontMetrics.width(minLabel), fontMetrics.width(maxLabel));

    int maxLabelWidth = fontMetrics.width("123");

    int numSatellites = m_satelliteInfo->allSatellites().size();
    int widthPerBar = (this->width() - scaleLabelWidth) / numSatellites;

    int lines = 1 + maxLabelWidth / widthPerBar;

    int maxY = this->height() - lines * textheight - PADDING;

    // draw scale
    painter->setPen(scalePen);

    painter->drawLine(0, 0, this->width(), 0);
    painter->drawLine(0, maxY, this->width(), maxY);

    painter->drawText(QRect(this->width(), PADDING, 0, 0), Qt::AlignTop | Qt::AlignRight | Qt::TextDontClip, maxLabel);
    painter->drawText(QRect(this->width(), maxY - PADDING, 0, 0), Qt::AlignBottom | Qt::AlignRight | Qt::TextDontClip, minLabel);

    // draw satellite bars
    int barCenter = widthPerBar / 2;
    int padding = widthPerBar * 1 / 10;

    int curLine = 0;

    for(int id: m_satelliteInfo->allSatellites()) {
        const SatelliteInfo::SatelliteData &sd = (*m_satelliteInfo)[id];

        // draw bar
        qreal barSize = (qreal)(sd.signalStrength - minSignal) / (maxSignal - minSignal);

        int left = barCenter - (widthPerBar - padding) / 2;
        int width = widthPerBar - padding;
        int top = maxY * (1 - barSize);
        int height = maxY * barSize;

        QRect barRect(left, top, width, height);

        painter->fillRect(barRect, sd.inUse ? usedBrush : visibleBrush);

        // draw label
        if(sd.inUse) {
            painter->setPen(usedPen);
        } else {
            painter->setPen(visiblePen);
        }

        QString satLabel = QLocale::system().toString(id);
        painter->drawText(QRect(barCenter, maxY + PADDING + curLine*textheight, 0, 0), Qt::AlignTop | Qt::AlignHCenter | Qt::TextDontClip, satLabel);

        barCenter += widthPerBar;

        curLine++;
        curLine %= lines;
    }
}

