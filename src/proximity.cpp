#include "proximity.h"


Proximity::Proximity(QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QProximitySensor(this);
}

Proximity::~Proximity()
{
}

void Proximity::refresh(void)
{
    if(!m_sensor->isActive()) {
        return;
    }

    QProximitySensor *proximity = dynamic_cast<QProximitySensor*>(m_sensor);
    QProximityReading *reading = proximity->reading();

    m_detected = reading->close();

    emit detectedChanged();
}
