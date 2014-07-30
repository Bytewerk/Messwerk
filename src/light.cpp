#include "light.h"


Light::Light(QObject *parent)
    : Sensor(parent)
{
    m_sensor = new QLightSensor(this);
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
