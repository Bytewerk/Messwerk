#include <qmath.h>

#include "gyroscope.h"


Gyroscope::Gyroscope(QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QGyroscope(this);
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
