#include <qmath.h>

#include "accelerometer.h"


Accelerometer::Accelerometer(QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QAccelerometer(this);
}

Accelerometer::~Accelerometer()
{
}

void Accelerometer::refresh(void)
{
    if(!m_sensor->isActive()) {
        return;
    }

    QAccelerometer *accelerometer = dynamic_cast<QAccelerometer*>(m_sensor);
    QAccelerometerReading *reading = accelerometer->reading();

    m_ax = reading->x();
    m_ay = reading->y();
    m_az = reading->z();

    m_abs = sqrt(m_ax*m_ax + m_ay*m_ay + m_az*m_az);

    emit axChanged();
    emit ayChanged();
    emit azChanged();

    emit absChanged();
}
