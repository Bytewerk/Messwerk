#include <QDebug>
#include <QDateTime>

#include "settings.h"
#include "wakelock.h"

#include "sensor.h"


unsigned Sensor::sensorTypeToWakeLockPart(Sensor::Type type)
{
    switch(type) {
        case Accelerometer: return WakeLock::PART_ACCELEROMETER;
        case Gyroscope:     return WakeLock::PART_GYROSCOPE;
        case Magnetometer:  return WakeLock::PART_MAGNETOMETER;
        case Rotation:      return WakeLock::PART_ROTATION;
        case Light:         return WakeLock::PART_LIGHT;
        case Proximity:     return WakeLock::PART_PROXIMITY;
        default:            return 0;
    }
}

Sensor::Sensor(Sensor::Type type, QObject *parent) :
    QObject(parent), m_sensor(NULL), m_type(type)
{
}


void Sensor::activate(unsigned requestingPart)
{
    Activateable::activate(requestingPart);

    Q_ASSERT(m_sensor);

    if(!m_sensor->isActive()) {
        qDebug() << "Sensor started";
        m_sensor->setAlwaysOn(true);
        m_sensor->start();
    }

    if(requestingPart == PART_PAGE) {
        WakeLock::instance().activateScreenLock(sensorTypeToWakeLockPart(m_type));
    }

    if(requestingPart == PART_LOGGING) {
        WakeLock::instance().activateBackground(sensorTypeToWakeLockPart(m_type));
    }
}

void Sensor::deactivate(unsigned requestingPart)
{
    Q_ASSERT(m_sensor);

    Activateable::deactivate(requestingPart);

    // stop the sensor if all parts are deactivated
    if(!(this->isActive()) && m_sensor->isActive()) {
        qDebug() << "Sensor stopped";
        m_sensor->stop();
    }

    if(requestingPart == PART_PAGE) {
        WakeLock::instance().deactivateScreenLock(sensorTypeToWakeLockPart(m_type));
    }

    if(requestingPart == PART_LOGGING) {
        WakeLock::instance().deactivateBackground(sensorTypeToWakeLockPart(m_type));
    }
}

void Sensor::startLogging()
{
    QDateTime now = QDateTime::currentDateTime();

    QString fileName = m_logBaseName + "_" + now.toString("yyyyMMdd-hhmmss") + ".csv";
    QString absPath = QDir(Settings::instance().getLoggingPath()).filePath(fileName);

    qDebug() << "Starting to log at" << absPath;

    m_logFile.setFileName(absPath);
    m_logFile.open(QFile::WriteOnly);

    activate(Activateable::PART_LOGGING);

    emit isLoggingChanged(true);
}

void Sensor::stopLogging()
{
    deactivate(Activateable::PART_LOGGING);

    m_logFile.close();

    emit isLoggingChanged(false);
}

bool Sensor::isLogging()
{
    return isPartActive(Activateable::PART_LOGGING);
}
