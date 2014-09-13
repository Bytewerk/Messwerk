#include <QDebug>
#include <QDateTime>

#include "settings.h"

#include "sensor.h"

Sensor::Sensor(QObject *parent) :
    QObject(parent), m_sensor(NULL)
{
}


void Sensor::activate(unsigned requestingPart)
{
    Activateable::activate(requestingPart);

    Q_ASSERT(m_sensor);

    if(!m_sensor->isActive()) {
        qDebug() << "Sensor started";
        m_sensor->start();
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
