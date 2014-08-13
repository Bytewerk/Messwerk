#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QSensor>

#include "activateable.h"

class Sensor : public QObject, public Activateable
{
    Q_OBJECT

protected:
    QSensor *m_sensor;

public:
    explicit Sensor(QObject *parent = 0);

    Q_INVOKABLE virtual void activate(unsigned requestingPart);
    Q_INVOKABLE virtual void deactivate(unsigned requestingPart);

signals:

public slots:
    virtual void refresh(void) = 0;

};

#endif // SENSOR_H
