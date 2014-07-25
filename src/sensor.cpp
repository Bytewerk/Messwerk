#include <QDebug>

#include "sensor.h"

Sensor::Sensor(QObject *parent) :
    QObject(parent), m_activeParts(0), m_sensor(NULL)
{
}


void Sensor::activate(unsigned requestingPart)
{
    Q_ASSERT(m_sensor);

    m_activeParts |= requestingPart;

    qDebug() << "Active Parts: " << m_activeParts;

    if(!m_sensor->isActive()) {
        qDebug() << "Sensor started";
        m_sensor->start();
    }
}

void Sensor::deactivate(unsigned requestingPart)
{
    Q_ASSERT(m_sensor);

    m_activeParts &= ~requestingPart;

    qDebug() << "Active Parts: " << m_activeParts;

    // stop the sensor if all parts are deactivated
    if((m_activeParts == 0) && m_sensor->isActive()) {
        qDebug() << "Sensor stopped";
        m_sensor->stop();
    }
}
