#ifndef WAKELOCK_H
#define WAKELOCK_H

#include <QObject>

#ifndef FOR_HARBOUR
#include <keepalive/backgroundactivity.h>
#include <keepalive/displayblanking.h>
#endif

class WakeLock : public QObject
{
    Q_OBJECT

private:
    unsigned m_backgroundParts;
    unsigned m_screenLockParts;

#ifndef FOR_HARBOUR
    BackgroundActivity *m_backgroundActivity;
    DisplayBlanking    *m_displayBlanking;
#endif

    WakeLock(void);

public:
    static const unsigned PART_ACCELEROMETER = (1 << 0);
    static const unsigned PART_GYROSCOPE     = (1 << 1);
    static const unsigned PART_ROTATION      = (1 << 2);
    static const unsigned PART_MAGNETOMETER  = (1 << 3);
    static const unsigned PART_LIGHT         = (1 << 4);
    static const unsigned PART_PROXIMITY     = (1 << 5);
    static const unsigned PART_SATELLITES    = (1 << 6);
    static const unsigned PART_POSITION      = (1 << 7);

    ~WakeLock();

    static WakeLock& instance()
    {
        static WakeLock theWakeLock;
        return theWakeLock;
    }

    virtual void activateBackground(unsigned requestingPart);
    virtual void deactivateBackground(unsigned requestingPart);
    virtual void forceDeactivateBackground(void);

    virtual void activateScreenLock(unsigned requestingPart);
    virtual void deactivateScreenLock(unsigned requestingPart);
    virtual void forceDeactivateScreenLock(void);

public slots:
    void debugState(void);
};

#endif // WAKELOCK_H
