#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <QProximitySensor>

#include "sensor.h"

class Proximity : public Sensor
{
    Q_OBJECT

    Q_PROPERTY(bool detected READ detected NOTIFY detectedChanged)

    private:
        bool m_detected;

    public:
        explicit Proximity(bool updateInternally = false, QObject *parent = NULL);
        ~Proximity();

        bool detected(void) const { return m_detected; }

    public slots:
        void refresh(void);

    signals:
        void detectedChanged(void);
};

#endif // PROXIMITY_H
