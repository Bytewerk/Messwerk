#include <QDateTime>

#include <qmath.h>

#include "magnetometer.h"


Magnetometer::Magnetometer(bool updateInternally, QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QMagnetometer(this);
    m_logBaseName = "magnetometer";

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }

    QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(logValues()));
}

Magnetometer::~Magnetometer()
{
}

void Magnetometer::logValues(void)
{
    if(isLogging()) {
        QMagnetometer *magnetometer = dynamic_cast<QMagnetometer*>(m_sensor);
        QMagnetometerReading *reading = magnetometer->reading();

        QString line = QString("%1\t%2\t%3\t%4\n")
                               .arg(QDateTime::currentMSecsSinceEpoch()/1000.0, 0, 'f', 3)
                               .arg(reading->x())
                               .arg(reading->y())
                               .arg(reading->z());

        m_logFile.write(line.toUtf8());
    }
}

void Magnetometer::refresh(void)
{
    if(!m_sensor->isActive()) {
        return;
    }

    QMagnetometer *magnetometer = dynamic_cast<QMagnetometer*>(m_sensor);
    QMagnetometerReading *reading = magnetometer->reading();

    m_mx = reading->x();
    m_my = reading->y();
    m_mz = reading->z();

    m_precision = reading->calibrationLevel();

    emit mxChanged();
    emit myChanged();
    emit mzChanged();
    emit precisionChanged();
}
