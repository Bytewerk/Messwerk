#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QSensor>
#include <QFile>

#include "activateable.h"

class Sensor : public QObject, public Activateable
{
    Q_OBJECT

    Q_PROPERTY(bool isLogging READ isLogging NOTIFY isLoggingChanged)

public:
    enum Type {
        Accelerometer,
        Gyroscope,
        Magnetometer,
        Rotation,
        Light,
        Proximity
    };

private:
    unsigned sensorTypeToWakeLockPart(Type type);

protected:
    QSensor *m_sensor;
    QFile    m_logFile;
    QString  m_logBaseName;
    Type     m_type;

public:
    explicit Sensor(Type type, QObject *parent = 0);

    Q_INVOKABLE virtual void activate(unsigned requestingPart);
    Q_INVOKABLE virtual void deactivate(unsigned requestingPart);

    Q_INVOKABLE virtual void startLogging(void);
    Q_INVOKABLE virtual void stopLogging(void);
    Q_INVOKABLE virtual bool isLogging(void);

signals:
    void isLoggingChanged(bool);

public slots:
    virtual void refresh(void) = 0;

};

#endif // SENSOR_H
