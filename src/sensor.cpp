#include <QDebug>

#include "sensor.h"

Sensor::Sensor(QObject *parent) :
    QObject(parent), m_sensor(NULL)
{
}


void Sensor::activate(unsigned requestingPart)
{
    Activateable::activate(requestingPart);

    Q_ASSERT(m_sensor);

    if(!m_sensor->isActive()) {
        qDebug() << "Sensor started";
        m_sensor->start();
    }
}

void Sensor::deactivate(unsigned requestingPart)
{
    Q_ASSERT(m_sensor);

    Activateable::deactivate(requestingPart);

    // stop the sensor if all parts are deactivated
    if(!(this->isActive()) && m_sensor->isActive()) {
        qDebug() << "Sensor stopped";
        m_sensor->stop();
    }
}
