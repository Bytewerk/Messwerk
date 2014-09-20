#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QDir>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString loggingPath READ getLoggingPath WRITE setLoggingPath NOTIFY loggingPathChanged)
    Q_PROPERTY(bool preventDisplayBlanking READ getPreventDisplayBlanking WRITE setPreventDisplayBlanking NOTIFY preventDisplayBlankingChanged)
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
    bool getPreventDisplayBlanking(void) { return m_settings->value("PreventDisplayBlanking", false).toBool(); }

public slots:
    void setLoggingPath(const QString &path)
    {
        m_settings->setValue("LoggingPath", path);
        emit loggingPathChanged(path);
    }

    void setPreventDisplayBlanking(bool prevent)
    {
        m_settings->setValue("PreventDisplayBlanking", prevent);
        emit preventDisplayBlankingChanged(prevent);
    }

signals:
    void loggingPathChanged(const QString &newPath);
    void preventDisplayBlankingChanged(bool prevented);
};

#endif // SETTINGS_H
