#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QAccelerometer>

#include "sensor.h"

class Accelerometer : public Sensor
{
	Q_OBJECT

    Q_PROPERTY(qreal ax READ ax NOTIFY axChanged)
    Q_PROPERTY(qreal ay READ ay NOTIFY ayChanged)
    Q_PROPERTY(qreal az READ az NOTIFY azChanged)
    Q_PROPERTY(qreal abs READ abs NOTIFY absChanged)

	private:
        qreal m_ax;
        qreal m_ay;
        qreal m_az;
        qreal m_abs;

	public:
        explicit Accelerometer(bool updateInternally = false, QObject *parent = NULL);
		~Accelerometer();

        qreal ax(void) const { return m_ax; }
        qreal ay(void) const { return m_ay; }
        qreal az(void) const { return m_az; }
        qreal abs(void) const { return m_abs; }

	public slots:
		void refresh(void);

	signals:
        void axChanged(void);
        void ayChanged(void);
        void azChanged(void);
        void absChanged(void);
};

#endif // ACCELEROMETER_H
