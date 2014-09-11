#include <QDebug>

#include "activateable.h"

Activateable::Activateable(void)
  : m_activeParts(0)
{
}

void Activateable::activate(unsigned requestingPart)
{
    m_activeParts |= requestingPart;

    qDebug() << "Active Parts: " << m_activeParts;
}

void Activateable::deactivate(unsigned requestingPart)
{
    m_activeParts &= ~requestingPart;

    qDebug() << "Active Parts: " << m_activeParts;
}

bool Activateable::isActive(void)
{
    return (m_activeParts != 0);
}

bool Activateable::isPartActive(unsigned part)
{
    return (m_activeParts & part) != 0;
}
