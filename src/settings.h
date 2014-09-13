#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QDir>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString loggingPath READ getLoggingPath WRITE setLoggingPath NOTIFY loggingPathChanged)
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

    QString getLoggingPath(void) { return m_settings->value("LoggingPath", QDir::home().absolutePath()).toString(); }

public slots:
    void setLoggingPath(const QString &path)
    {
        m_settings->setValue("LoggingPath", path);
        emit loggingPathChanged(path);
    }

signals:
    void loggingPathChanged(const QString &newPath);
};

#endif // SETTINGS_H
