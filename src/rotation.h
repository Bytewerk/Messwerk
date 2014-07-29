#ifndef ROTATION_H
#define ROTATION_H

#include <QRotationSensor>

#include "sensor.h"

class Rotation : public Sensor
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
        explicit Rotation(QObject *parent = NULL);
        ~Rotation();

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

#endif // ROTATION_H
