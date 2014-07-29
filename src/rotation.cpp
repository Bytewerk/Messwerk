#include <qmath.h>
#include <QDebug>

#include "rotation.h"


Rotation::Rotation(QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QRotationSensor(this);

    if(m_sensor) {
        qDebug() << "Rotation sensor activated" << m_sensor;
    } else {
        qDebug() << "Failed to activate Rotation sensor";
    }
}

Rotation::~Rotation()
{
}

void Rotation::refresh(void)
{
    if(!m_sensor->isActive()) {
        return;
    }

    QRotationSensor *rotation = dynamic_cast<QRotationSensor*>(m_sensor);
    QRotationReading *reading = rotation->reading();

    m_rx = reading->x();
    m_ry = reading->y();
    m_rz = reading->z();

    emit rxChanged();
    emit ryChanged();
    emit rzChanged();
}
