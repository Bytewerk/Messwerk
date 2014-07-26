#include <QPainter>

#include "plotwidget.h"

PlotWidget::PlotWidget(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

void PlotWidget::paint(QPainter *painter)
{
    QPen p(m_plotColor);
    p.setWidth(3);
    painter->setPen(p);

    QPoint prevPoint, curPoint(this->width(), 0);

    bool firstPoint = true;
    ValueList::Iterator iter = m_values.end() - 1;

    while((iter != m_values.begin()) && (curPoint.x() > 0)) {
        qreal v = *iter;

        // normalized value between 0 and 1
        qreal vnorm = (v - m_minValue) / (m_maxValue - m_minValue);

        prevPoint = curPoint;

        curPoint.setX(curPoint.x() - SCROLL_STEP);
        curPoint.setY(this->height() * (1 - vnorm));

        if(!firstPoint) {
            painter->drawLine(prevPoint, curPoint);
            qDebug() << "Drawing line from " << prevPoint << " to " << curPoint;
        } else {
            qDebug() << "Ignoring first point while drawing";
        }

        firstPoint = false;

        iter--;
    }
}

void PlotWidget::addValue(qreal v)
{
    m_values.append(v);

    int valuesRequired = this->width() / SCROLL_STEP;

    if(m_values.size() > valuesRequired) {
        ValueList::Iterator delRangeEndIter = m_values.end() - valuesRequired;
        m_values.erase(m_values.begin(), delRangeEndIter);
    }

    qDebug() << "List size: " << m_values.size();

    // recalculate minimum and maximum value
    m_minValue =  1e27;
    m_maxValue = -1e27;

    for(const qreal &v: m_values) {
        if(v < m_minValue) {
            m_minValue = v;
        }

        if(v > m_maxValue) {
            m_maxValue = v;
        }
    }

    if(m_minValue == m_maxValue) {
        m_minValue -= 0.5;
        m_maxValue += 0.5;
    }

    qDebug() << "Value range: [" << m_minValue << ";" << m_maxValue << "]";
}
