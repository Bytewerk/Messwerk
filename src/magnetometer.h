#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include <QMagnetometer>

#include "sensor.h"

class Magnetometer : public Sensor
{
    Q_OBJECT

    Q_PROPERTY(qreal mx READ mx NOTIFY mxChanged)
    Q_PROPERTY(qreal my READ my NOTIFY myChanged)
    Q_PROPERTY(qreal mz READ mz NOTIFY mzChanged)
    Q_PROPERTY(qreal precision READ precision NOTIFY precisionChanged)

    private:
        qreal m_mx;
        qreal m_my;
        qreal m_mz;
        qreal m_precision;

    public:
        explicit Magnetometer(QObject *parent = NULL);
        ~Magnetometer();

        qreal mx(void) const { return m_mx; }
        qreal my(void) const { return m_my; }
        qreal mz(void) const { return m_mz; }
        qreal precision(void) const { return m_precision; }

    public slots:
        void refresh(void);

    signals:
        void mxChanged(void);
        void myChanged(void);
        void mzChanged(void);
        void precisionChanged(void);
};

#endif // MAGNETOMETER_H
