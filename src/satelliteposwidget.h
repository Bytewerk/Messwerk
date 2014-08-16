#ifndef SATELLITEPOSWIDGET_H
#define SATELLITEPOSWIDGET_H

#include <QQuickPaintedItem>

#include "satelliteinfo.h"

class SatellitePosWidget : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QColor visibleColor READ visibleColor WRITE setvisibleColor)
    Q_PROPERTY(QColor usedColor READ usedColor WRITE setusedColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setscaleColor)
    Q_PROPERTY(QColor northColor READ northColor WRITE setnorthColor)
    Q_PROPERTY(qreal northDirection READ northDirection WRITE setnorthDirection NOTIFY northDirectionChanged)

private:
    QColor m_usedColor;
    QColor m_visibleColor;
    QColor m_scaleColor;
    QColor m_northColor;
    qreal m_northDirection;

    SatelliteInfo *m_satelliteInfo;

public:
    explicit SatellitePosWidget(QQuickItem *parent = 0);

    void paint(QPainter *painter);

    Q_INVOKABLE void setSatelliteInfo(SatelliteInfo *si) { m_satelliteInfo = si; }

    void setvisibleColor(const QColor &color) { m_visibleColor = color; }
    void setusedColor(const QColor &color) { m_usedColor = color; }
    void setscaleColor(const QColor &color) { m_scaleColor = color; }
    void setnorthColor(const QColor &color) { m_northColor = color; }

    const QColor& visibleColor() { return m_visibleColor; }
    const QColor& usedColor() { return m_usedColor; }
    const QColor& scaleColor() { return m_scaleColor; }
    const QColor& northColor() { return m_northColor; }

    qreal northDirection() const { return m_northDirection; }

public slots:
    void setnorthDirection(qreal arg);

signals:
    void northDirectionChanged(qreal arg);
};

#endif // SATELLITEPOSWIDGET_H
