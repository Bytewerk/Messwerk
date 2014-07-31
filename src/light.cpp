#include "light.h"


Light::Light(bool updateInternally, QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QLightSensor(this);

    if(updateInternally) {
        QObject::connect(m_sensor, SIGNAL(readingChanged()), this, SLOT(refresh()));
    }
}

Light::~Light()
{
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
