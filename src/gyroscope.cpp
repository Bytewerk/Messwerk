#include <qmath.h>

#include "gyroscope.h"


Gyroscope::Gyroscope(bool updateInternally, QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QGyroscope(this);

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }
}

Gyroscope::~Gyroscope()
{
}

void Gyroscope::refresh(void)
{
    if(!m_sensor->isActive()) {
        return;
    }

    QGyroscope *gyroscope = dynamic_cast<QGyroscope*>(m_sensor);
    QGyroscopeReading *reading = gyroscope->reading();

    m_rx = reading->x();
    m_ry = reading->y();
    m_rz = reading->z();

    emit rxChanged();
    emit ryChanged();
    emit rzChanged();
}
