#include <QDateTime>

#include <qmath.h>

#include "gyroscope.h"


Gyroscope::Gyroscope(bool updateInternally, QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QGyroscope(this);
    m_logBaseName = "gyroscope";

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }

    QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(logValues()));
}

Gyroscope::~Gyroscope()
{
}

void Gyroscope::logValues(void)
{
    if(isLogging()) {
        QGyroscope *gyroscope = dynamic_cast<QGyroscope*>(m_sensor);
        QGyroscopeReading *reading = gyroscope->reading();

        QString line = QString("%1\t%2\t%3\t%4\n")
                               .arg(QDateTime::currentMSecsSinceEpoch()/1000.0, 0, 'f', 3)
                               .arg(reading->x())
                               .arg(reading->y())
                               .arg(reading->z());

        m_logFile.write(line.toUtf8());
    }
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
