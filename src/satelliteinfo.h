#ifndef SATELLITEINFO_H
#define SATELLITEINFO_H

#include <QObject>
#include <QGeoSatelliteInfo>
#include <QGeoSatelliteInfoSource>
#include <QSet>
#include <QMap>

#include "activateable.h"

class SatelliteInfo : public QObject, public Activateable
{
    Q_OBJECT

public:
    struct SatelliteData {
        qreal  azimuth;         // in Degrees
        qreal  elevation;       // in Degrees
        int    signalStrength;  // in dB
        bool   inUse;
        qint64 lastUpdated;     // in milliseconds
        QGeoSatelliteInfo::SatelliteSystem satelliteSystem;

        void updateFrom(const SatelliteData& other);
    };

    typedef int SatelliteID;

    static const qint64 TIMEOUT = 10000; // timeout of satellites in milliseconds

private:
    typedef QMap<SatelliteID, SatelliteData> SatelliteMap;
    typedef QSet<SatelliteID> SatelliteIDSet;

    SatelliteMap m_satellites;

    SatelliteIDSet m_used;
    SatelliteIDSet m_unused;
    SatelliteIDSet m_all;

    qreal m_minSignal;
    qreal m_maxSignal;

    QGeoSatelliteInfoSource *m_source;
    bool                     m_sourceActive;

    void updateMinMax(void);

public:
    explicit SatelliteInfo(QObject *parent = 0);
    ~SatelliteInfo();

    int getNumberOfSatellites(void) { return m_satellites.size(); }
    const SatelliteData& operator[] (SatelliteID idx) { return m_satellites[idx]; }

    const SatelliteIDSet& usedSatellites(void) { return m_used; }
    const SatelliteIDSet& unusedSatellites(void) { return m_unused; }
    const SatelliteIDSet& allSatellites(void) { return m_all; }

    qreal minSignal(void) { return m_minSignal; }
    qreal maxSignal(void) { return m_maxSignal; }

    Q_INVOKABLE void activate(unsigned requestingPart);
    Q_INVOKABLE void deactivate(unsigned requestingPart);
signals:
    void newDataAvailable(void);

public slots:
    void setSatellitesInUse(const QList<QGeoSatelliteInfo> &satellites);
    void setSatellitesInView(const QList<QGeoSatelliteInfo> &satellites);


};

#endif // SATELLITEINFO_H
