#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <QGyroscope>

#include "sensor.h"

class Gyroscope : public Sensor
{
    Q_OBJECT

    Q_PROPERTY(qreal rx READ rx NOTIFY rxChanged)
    Q_PROPERTY(qreal ry READ ry NOTIFY ryChanged)
    Q_PROPERTY(qreal rz READ rz NOTIFY rzChanged)

    private:
        qreal m_rx;
        qreal m_ry;
        qreal m_rz;

    public:
        explicit Gyroscope(bool updateInternally = false, QObject *parent = NULL);
        ~Gyroscope();

        qreal rx(void) const { return m_rx; }
        qreal ry(void) const { return m_ry; }
        qreal rz(void) const { return m_rz; }

    public slots:
        void refresh(void);

    signals:
        void rxChanged(void);
        void ryChanged(void);
        void rzChanged(void);
};

#endif // GYROSCOPE_H
