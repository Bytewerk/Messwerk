#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QSensor>

class Sensor : public QObject
{
    Q_OBJECT

private:
    unsigned m_activeParts;

protected:
    QSensor *m_sensor;

public:
    static const unsigned PART_PAGE = (1 << 0);
    static const unsigned PART_COVER = (1 << 1);
    static const unsigned PART_LOGGING = (1 << 2);

    explicit Sensor(QObject *parent = 0);

    Q_INVOKABLE void activate(unsigned requestingPart);
    Q_INVOKABLE void deactivate(unsigned requestingPart);

signals:

public slots:
    virtual void refresh(void) = 0;

};

#endif // SENSOR_H
