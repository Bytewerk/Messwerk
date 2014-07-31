#include "proximity.h"


Proximity::Proximity(bool updateInternally, QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QProximitySensor(this);

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }
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
