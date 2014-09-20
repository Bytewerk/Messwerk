#include <QDateTime>

#include "proximity.h"


Proximity::Proximity(bool updateInternally, QObject *parent)
    : Sensor(Sensor::Proximity, parent)
{
    m_sensor = new QProximitySensor(this);
    m_logBaseName = "proximity";

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }

    QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(logValues()));
}

Proximity::~Proximity()
{
}

void Proximity::logValues(void)
{
    if(isLogging()) {
        QProximitySensor *proximity = dynamic_cast<QProximitySensor*>(m_sensor);
        QProximityReading *reading = proximity->reading();

        QString line = QString("%1\t%2\n")
                               .arg(QDateTime::currentMSecsSinceEpoch()/1000.0, 0, 'f', 3)
                               .arg((int)(reading->close()));

        m_logFile.write(line.toUtf8());
    }
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
