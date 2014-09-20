#include <QDateTime>

#include <qmath.h>
#include <QDebug>

#include "rotation.h"


Rotation::Rotation(bool updateInternally, QObject *parent)
    : Sensor(Sensor::Rotation, parent)
{
    m_sensor = new QRotationSensor(this);
    m_logBaseName = "rotation";

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }

    QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(logValues()));
}

Rotation::~Rotation()
{
}

void Rotation::logValues(void)
{
    if(isLogging()) {
        QRotationSensor *rotation = dynamic_cast<QRotationSensor*>(m_sensor);
        QRotationReading *reading = rotation->reading();

        QString line = QString("%1\t%2\t%3\t%4\n")
                               .arg(QDateTime::currentMSecsSinceEpoch()/1000.0, 0, 'f', 3)
                               .arg(reading->x())
                               .arg(reading->y())
                               .arg(reading->z());

        m_logFile.write(line.toUtf8());
    }
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
