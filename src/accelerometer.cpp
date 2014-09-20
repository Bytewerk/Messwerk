#include <QStringList>
#include <QDateTime>

#include <qmath.h>

#include "accelerometer.h"


Accelerometer::Accelerometer(bool updateInternally, QObject *parent)
    : Sensor(Sensor::Accelerometer, parent)
{
    m_sensor = new QAccelerometer(this);
    m_logBaseName = "accelerometer";

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }

    QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(logValues()));
}

Accelerometer::~Accelerometer()
{
}

void Accelerometer::logValues(void)
{
    if(isLogging()) {
        QAccelerometer *accelerometer = dynamic_cast<QAccelerometer*>(m_sensor);
        QAccelerometerReading *reading = accelerometer->reading();

        QString line = QString("%1\t%2\t%3\t%4\n")
                               .arg(QDateTime::currentMSecsSinceEpoch()/1000.0, 0, 'f', 3)
                               .arg(reading->x())
                               .arg(reading->y())
                               .arg(reading->z());

        m_logFile.write(line.toUtf8());
    }
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
