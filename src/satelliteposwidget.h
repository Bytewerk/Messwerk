#ifndef SATELLITEPOSWIDGET_H
#define SATELLITEPOSWIDGET_H

#include <QQuickPaintedItem>
#include <QSvgRenderer>

#include "satelliteinfo.h"

class SatellitePosWidget : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QColor visibleColor READ visibleColor WRITE setvisibleColor)
    Q_PROPERTY(QColor usedColor READ usedColor WRITE setusedColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setscaleColor)

private:
    QColor m_usedColor;
    QColor m_visibleColor;
    QColor m_scaleColor;

    QSvgRenderer *m_russiaSVG;
    QSvgRenderer *m_europeSVG;
    QSvgRenderer *m_usaSVG;

    SatelliteInfo *m_satelliteInfo;

public:
    explicit SatellitePosWidget(QQuickItem *parent = 0);
    ~SatellitePosWidget();

    void paint(QPainter *painter);

    Q_INVOKABLE void setSatelliteInfo(SatelliteInfo *si) { m_satelliteInfo = si; }

    void setvisibleColor(const QColor &color) { m_visibleColor = color; }
    void setusedColor(const QColor &color) { m_usedColor = color; }
    void setscaleColor(const QColor &color) { m_scaleColor = color; }

    const QColor& visibleColor() { return m_visibleColor; }
    const QColor& usedColor() { return m_usedColor; }
    const QColor& scaleColor() { return m_scaleColor; }

signals:
};

#endif // SATELLITEPOSWIDGET_H
