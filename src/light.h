#ifndef LIGHT_H
#define LIGHT_H

#include <QLightSensor>

#include "sensor.h"

class Light : public Sensor
{
    Q_OBJECT

    Q_PROPERTY(qreal brightness READ brightness NOTIFY brightnessChanged)

    private:
        qreal m_brightness;

    public:
        explicit Light(bool updateInternally = false, QObject *parent = NULL);
        ~Light();

        qreal brightness(void) const { return m_brightness; }

    public slots:
        void refresh(void);

    signals:
        void brightnessChanged(void);
};

#endif // LIGHT_H
