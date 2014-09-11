#include "settings.h"

Settings::Settings()
{
    m_settings = new QSettings("bytewerk", "Messwerk");
}

Settings::~Settings()
{
    delete m_settings;
}
