#include <QDateTime>

#include "light.h"


Light::Light(bool updateInternally, QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QLightSensor(this);
    m_logBaseName = "light";

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }

    QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(logValues()));
}

Light::~Light()
{
}

void Light::logValues(void)
{
    if(isLogging()) {
        QLightSensor *light = dynamic_cast<QLightSensor*>(m_sensor);
        QLightReading *reading = light->reading();

        QString line = QString("%1\t%2\n")
                               .arg(QDateTime::currentMSecsSinceEpoch()/1000.0, 0, 'f', 3)
                               .arg(reading->lux());

        m_logFile.write(line.toUtf8());
    }
}

void Light::refresh(void)
{
    if(!m_sensor->isActive()) {
        return;
    }

    QLightSensor *light = dynamic_cast<QLightSensor*>(m_sensor);
    QLightReading *reading = light->reading();

    m_brightness = reading->lux();

    emit brightnessChanged();
}
