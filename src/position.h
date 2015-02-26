#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QSet>
#include <QMap>
#include <QFile>

#include "activateable.h"

class Position : public QObject, public Activateable
{
    Q_OBJECT

    Q_PROPERTY(bool isLogging READ isLogging NOTIFY isLoggingChanged)

    Q_PROPERTY(qreal   latitude     READ latitude      NOTIFY latitudeChanged)
    Q_PROPERTY(qreal   longitude    READ longitude     NOTIFY longitudeChanged)
    Q_PROPERTY(qreal   altitude     READ altitude      NOTIFY altitudeChanged)
    Q_PROPERTY(QString maidenhead   READ maidenhead    NOTIFY maidenheadChanged)
    Q_PROPERTY(int     coordType    READ coordType     NOTIFY coordTypeChanged)
    Q_PROPERTY(qreal   horzAccuracy READ horzAccuracy  NOTIFY horzAccuracyChanged)
    Q_PROPERTY(qreal   vertAccuracy READ vertAccuracy  NOTIFY vertAccuracyChanged)

private:
    QGeoPositionInfoSource *m_source;
    bool                    m_sourceActive;

    QFile m_logFile;

    qreal   m_latitude;
    qreal   m_longitude;
    qreal   m_altitude;
    QString m_maidenhead;
    int     m_coordType;
    qreal   m_horzAccuracy;
    qreal   m_vertAccuracy;

    void logData(void);

    void updateMaidenhead(void);

public:
    explicit Position(QObject *parent = 0);
    ~Position();

    Q_INVOKABLE void activate(unsigned requestingPart);
    Q_INVOKABLE void deactivate(unsigned requestingPart);

    Q_INVOKABLE void startLogging(void);
    Q_INVOKABLE void stopLogging(void);

    bool isLogging(void) { return isPartActive(Activateable::PART_LOGGING); }

    qreal          latitude(void)     { return m_latitude; };
    qreal          longitude(void)    { return m_longitude; };
    qreal          altitude(void)     { return m_altitude; };
    const QString& maidenhead(void)   { return m_maidenhead; };
    int            coordType(void)    { return m_coordType; };
    qreal          horzAccuracy(void) { return m_horzAccuracy; };
    qreal          vertAccuracy(void) { return m_vertAccuracy; };

signals:
    void isLoggingChanged(bool);

    void latitudeChanged(void);
    void longitudeChanged(void);
    void altitudeChanged(void);
    void maidenheadChanged(void);
    void coordTypeChanged(void);
    void horzAccuracyChanged(void);
    void vertAccuracyChanged(void);

public slots:
    void positionUpdated(const QGeoPositionInfo &posInfo);
};

#endif // POSITION_H
