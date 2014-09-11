#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QDir>

class Settings
{
private:
    QSettings *m_settings;

    Settings(); // singleton class, constructor is private

public:
    ~Settings();

    static Settings& instance()
    {
        static Settings theSettings;
        return theSettings;
    }

    void setLoggingPath(const QString &path) { m_settings->setValue("LoggingPath", path); }
    QString getLoggingPath(void) { return m_settings->value("LoggingPath", QDir::home().absolutePath()).toString(); }
};

#endif // SETTINGS_H
