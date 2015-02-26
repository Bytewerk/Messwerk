#include <QDateTime>
#include <QDebug>
#include <QStringList>

#include "settings.h"
#include "wakelock.h"

#include "position.h"

void Position::logData()
{
    if(isLogging()) {
        /* Log file line format:
         * timestamp<tab>latitude<tab>longitude<tab>altitude\n
         */
        QString line = QString("%1\t%2\t%3\t%4\n")
                               .arg(QDateTime::currentMSecsSinceEpoch()/1000.0, 0, 'f', 3)
                               .arg(m_latitude)
                               .arg(m_longitude)
                               .arg(m_altitude);

        m_logFile.write(line.toUtf8());
    }
}

void Position::updateMaidenhead(void)
{
    const unsigned FIELDS     = 18;
    const unsigned SQUARES    = 10;
    const unsigned SUBSQUARES = 24;

    const unsigned GRIDLEN = FIELDS * SQUARES * SUBSQUARES;

    unsigned gridIdxLon = (m_longitude + 180) * GRIDLEN / 360.0;
    unsigned gridIdxLat = (m_latitude  + 90)  * GRIDLEN / 180.0;

    unsigned fieldLon = gridIdxLon / (SQUARES * SUBSQUARES);
    unsigned fieldLat = gridIdxLat / (SQUARES * SUBSQUARES);

    unsigned squareLon = (gridIdxLon / SUBSQUARES) % SQUARES;
    unsigned squareLat = (gridIdxLat / SUBSQUARES) % SQUARES;

    unsigned subSquareLon = gridIdxLon % SUBSQUARES;
    unsigned subSquareLat = gridIdxLat % SUBSQUARES;

    m_maidenhead = "";

    m_maidenhead += ('A' + fieldLon);
    m_maidenhead += ('A' + fieldLat);

    m_maidenhead += ('0' + squareLon);
    m_maidenhead += ('0' + squareLat);

    m_maidenhead += ('a' + subSquareLon);
    m_maidenhead += ('a' + subSquareLat);
}

Position::Position(QObject *parent) :
    QObject(parent), m_sourceActive(false)
{
    m_source = QGeoPositionInfoSource::createDefaultSource(this);

    if(!connect(m_source, SIGNAL(positionUpdated(const QGeoPositionInfo&)), this, SLOT(positionUpdated(const QGeoPositionInfo&)))) {
        qDebug() << "Failed to connect m_source";
    }
}

Position::~Position()
{
    delete m_source;
}


void Position::activate(unsigned requestingPart)
{
    Activateable::activate(requestingPart);

    if(!m_sourceActive) {
        qDebug() << "Position info source started";
        m_source->startUpdates();
        m_sourceActive = true;
    }

    if(requestingPart == PART_PAGE) {
        WakeLock::instance().activateScreenLock(WakeLock::PART_POSITION);
    }

    if(requestingPart == PART_LOGGING) {
        WakeLock::instance().activateBackground(WakeLock::PART_POSITION);
    }
}

void Position::deactivate(unsigned requestingPart)
{
    Activateable::deactivate(requestingPart);

    // stop the sensor if all parts are deactivated
    if(!(this->isActive()) && m_sourceActive) {
        qDebug() << "Position info source stopped";
        m_source->stopUpdates();
        m_sourceActive = false;
    }

    if(requestingPart == PART_PAGE) {
        WakeLock::instance().deactivateScreenLock(WakeLock::PART_POSITION);
    }

    if(requestingPart == PART_LOGGING) {
        WakeLock::instance().deactivateBackground(WakeLock::PART_POSITION);
    }
}

void Position::startLogging()
{
    activate(Activateable::PART_LOGGING);

    QDateTime now = QDateTime::currentDateTime();

    QString fileName = "position_" + now.toString("yyyyMMdd-hhmmss") + ".csv";
    QString absPath = QDir(Settings::instance().getLoggingPath()).filePath(fileName);

    qDebug() << "Starting to log at" << absPath;

    m_logFile.setFileName(absPath);
    m_logFile.open(QFile::WriteOnly);

    emit isLoggingChanged(true);
}

void Position::stopLogging()
{
    deactivate(Activateable::PART_LOGGING);

    m_logFile.close();

    emit isLoggingChanged(false);
}

void Position::positionUpdated(const QGeoPositionInfo &posInfo)
{
    // update coordinates
    m_latitude  = posInfo.coordinate().latitude();
    m_longitude = posInfo.coordinate().longitude();
    m_altitude  = posInfo.coordinate().altitude();
    m_coordType = posInfo.coordinate().type();

    emit latitudeChanged();
    emit longitudeChanged();
    emit altitudeChanged();
    emit coordTypeChanged();

    // update attributes
    if(posInfo.hasAttribute(QGeoPositionInfo::HorizontalAccuracy)) {
        m_horzAccuracy = posInfo.attribute(QGeoPositionInfo::HorizontalAccuracy);
    } else {
        m_horzAccuracy = -1;
    }

    if(posInfo.hasAttribute(QGeoPositionInfo::VerticalAccuracy)) {
        m_vertAccuracy = posInfo.attribute(QGeoPositionInfo::VerticalAccuracy);
    } else {
        m_vertAccuracy = -1;
    }

    emit horzAccuracyChanged();
    emit vertAccuracyChanged();

    // recalculate Maidenhead locator
    updateMaidenhead();

    emit maidenheadChanged();
}
