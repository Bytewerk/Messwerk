#include <QDateTime>
#include <QDebug>

#include "satelliteinfo.h"

void SatelliteInfo::updateMinMax()
{
    m_minSignal =  1e20;
    m_maxSignal = -1e20;

    for(int id: m_satellites.keys()) {
        const SatelliteData &sd = m_satellites[id];

        if(sd.signalStrength < m_minSignal) {
            m_minSignal = sd.signalStrength;
        }

        if(sd.signalStrength > m_maxSignal) {
            m_maxSignal = sd.signalStrength;
        }
    }

    // prevent zero range
    if(m_maxSignal == m_minSignal) {
        m_minSignal -= 1;
    }
}

SatelliteInfo::SatelliteInfo(QObject *parent) :
    QObject(parent), m_sourceActive(false)
{
    m_source = QGeoSatelliteInfoSource::createDefaultSource(this);

    connect(m_source, SIGNAL(satellitesInViewUpdated(const QList<QGeoSatelliteInfo>&)), this, SLOT(setSatellitesInView(const QList<QGeoSatelliteInfo>)));
    connect(m_source, SIGNAL(satellitesInUseUpdated(const QList<QGeoSatelliteInfo>&)), this, SLOT(setSatellitesInUse(const QList<QGeoSatelliteInfo>)));
}

SatelliteInfo::~SatelliteInfo()
{
    delete m_source;
}

// add missing satellites and update used/unused lists
void SatelliteInfo::setSatellitesInUse(const QList<QGeoSatelliteInfo> &satellites)
{
    m_used.clear();

    // add or update satellites
    for(const QGeoSatelliteInfo &sat: satellites) {
        SatelliteData sd;

        sd.azimuth = sat.attribute(QGeoSatelliteInfo::Azimuth);
        sd.elevation = sat.attribute(QGeoSatelliteInfo::Elevation);
        sd.signalStrength = sat.signalStrength();
        sd.satelliteSystem = sat.satelliteSystem();

        SatelliteMap::Iterator iter = m_satellites.find(sat.satelliteIdentifier());

        m_used.insert(sat.satelliteIdentifier());

        if(iter != m_satellites.end()) {
            // entry already exists
            iter->updateFrom(sd);
        } else {
            sd.lastUpdated = QDateTime::currentMSecsSinceEpoch();
            m_satellites.insert(sat.satelliteIdentifier(), sd);
        }
    }

    // rebuild used and unused list
    m_unused.clear();

    for(SatelliteID id: m_satellites.keys()) {
        if(m_used.contains(id)) {
            m_satellites[id].inUse = true;
        } else {
            m_satellites[id].inUse = false;
            m_unused.insert(id);
        }
    }

    m_all = m_used + m_unused;

    updateMinMax();
}

// add missing satellites and remove the ones timed out
void SatelliteInfo::setSatellitesInView(const QList<QGeoSatelliteInfo> &satellites)
{
    for(const QGeoSatelliteInfo &sat: satellites) {
        SatelliteData sd;

        sd.azimuth = sat.attribute(QGeoSatelliteInfo::Azimuth);
        sd.elevation = sat.attribute(QGeoSatelliteInfo::Elevation);
        sd.signalStrength = sat.signalStrength();
        sd.satelliteSystem = sat.satelliteSystem();

        SatelliteMap::Iterator iter = m_satellites.find(sat.satelliteIdentifier());

        if(iter != m_satellites.end()) {
            // entry already exists
            iter->updateFrom(sd);
        } else {
            sd.lastUpdated = QDateTime::currentMSecsSinceEpoch();
            m_satellites.insert(sat.satelliteIdentifier(), sd);
        }
    }

    // remove old satellites
    qint64 threshold = QDateTime::currentMSecsSinceEpoch() - TIMEOUT;
    for(SatelliteID id: m_satellites.keys()) {
        const SatelliteData &sd = m_satellites[id];

        if(sd.lastUpdated < threshold) {
            m_satellites.erase(m_satellites.find(id));
        }
    }

    updateMinMax();

    emit newDataAvailable();
}


void SatelliteInfo::SatelliteData::updateFrom(const SatelliteInfo::SatelliteData &other)
{
    // copy all attributes except inUse
    azimuth = other.azimuth;
    elevation = other.elevation;
    signalStrength = other.signalStrength;
    satelliteSystem = other.satelliteSystem;

    // set last update time
    lastUpdated = QDateTime::currentMSecsSinceEpoch();
}

void SatelliteInfo::activate(unsigned requestingPart)
{
    Activateable::activate(requestingPart);

    if(!m_sourceActive) {
        qDebug() << "Satellite info source started";
        m_source->startUpdates();
        m_sourceActive = true;
    }
}

void SatelliteInfo::deactivate(unsigned requestingPart)
{
    Activateable::deactivate(requestingPart);

    // stop the sensor if all parts are deactivated
    if(!(this->isActive()) && m_sourceActive) {
        qDebug() << "Satellite info source stopped";
        m_source->stopUpdates();
        m_sourceActive = false;
    }
}
