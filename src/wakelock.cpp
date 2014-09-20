#include <QDebug>

#include "settings.h"
#include "wakelock.h"

WakeLock::WakeLock(void)
  : m_backgroundParts(0), m_screenLockParts(0)
{
    m_backgroundActivity = new BackgroundActivity(this);
    m_backgroundActivity->setWakeupFrequency(BackgroundActivity::ThirtySeconds);
    connect(m_backgroundActivity, SIGNAL(stateChanged(void)), this, SLOT(debugState(void)));

    m_displayBlanking = new DisplayBlanking(this);
}

WakeLock::~WakeLock(void)
{
    delete m_backgroundActivity;
    delete m_displayBlanking;
}

void WakeLock::activateBackground(unsigned requestingPart)
{
    m_backgroundParts |= requestingPart;

    qDebug() << "Active background parts: " << m_backgroundParts;

    if(!m_backgroundActivity->isRunning()) {
        m_backgroundActivity->run();
    }
}

void WakeLock::deactivateBackground(unsigned requestingPart)
{
    m_backgroundParts &= ~requestingPart;

    qDebug() << "Active background parts: " << m_backgroundParts;

    if((m_backgroundParts == 0) && m_backgroundActivity->isRunning()) {
        m_backgroundActivity->stop();
    }
}

void WakeLock::forceDeactivateBackground(void)
{
    // deactivate all parts
    deactivateBackground(0xFFFFFFFF);
}

void WakeLock::activateScreenLock(unsigned requestingPart)
{
    m_screenLockParts |= requestingPart;

    qDebug() << "Active screenLock parts: " << m_screenLockParts;

    if(Settings::instance().getPreventDisplayBlanking()
            && (m_screenLockParts != 0)
            && !m_displayBlanking->preventBlanking()) {
        m_displayBlanking->setPreventBlanking(true);
    }
}

void WakeLock::deactivateScreenLock(unsigned requestingPart)
{
    m_screenLockParts &= ~requestingPart;

    qDebug() << "Active screenLock parts: " << m_screenLockParts;

    if((m_screenLockParts == 0)
            && m_displayBlanking->preventBlanking()) {
        m_displayBlanking->setPreventBlanking(false);
    }
}

void WakeLock::forceDeactivateScreenLock(void)
{
    // deactivate all parts
    deactivateScreenLock(0xFFFFFFFF);
}

void WakeLock::debugState(void)
{
    qDebug() << "Background activity state:" << m_backgroundActivity->state();
}
