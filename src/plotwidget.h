#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QQuickPaintedItem>

class PlotWidget : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QColor plotColor READ plotColor WRITE setplotColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setscaleColor)

private:
    QColor m_plotColor;
    QColor m_scaleColor;

    QList<qreal> m_values;

    qreal m_minValue;
    qreal m_maxValue;

    typedef QList<qreal> ValueList;

public:
    static const unsigned SCROLL_STEP = 5; // scrolling in pixels per data point

    explicit PlotWidget(QQuickItem *parent = 0);

    void paint(QPainter *painter);

    void setplotColor(const QColor &color) { m_plotColor = color; }
    void setscaleColor(const QColor &color) { m_scaleColor = color; }

    const QColor& plotColor() { return m_plotColor; }
    const QColor& scaleColor() { return m_scaleColor; }

signals:

public slots:
    void addValue(qreal v);

};

#endif // PLOTWIDGET_H
