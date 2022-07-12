#pragma once

#include "Logger.h"
#include <protodb/configurable/Configurable.h>

#include <QObject>
#include <QColor>
#include <QFont>
#include <QMap>

class LogFormatter: public QObject
{
    Q_OBJECT

public:
    enum ByteFormat {
        HexFormat,
        AsciiFormat,
    };

public:
    LogFormatter(QObject* parent = nullptr);
    LogFormatter(const LogFormatter& other, QObject* parent = nullptr);

    void setChannelName(Logger::Channel ch, const QString& name);
    QString channelName(Logger::Channel ch) const;

    void setTimeFormat(const QString& format);
    const QString& timeFormat() const;

    void setSeparator(char s);
    char separator() const;

    void setByteFormat(ByteFormat format);
    ByteFormat byteFormat() const;

    QString channelName(const Logger::Event& event) const;
    QString timestamp  (const Logger::Event& event) const;
    QString data       (const Logger::Event& event) const;
    QString format     (const Logger::Event& event) const;

    QString format(Logger::Channel ch) const;
    QString format(const QDateTime& dt) const;
    QString format(Logger::Channel ch, const QByteArray& msg) const;

private:
    QMap<Logger::Channel, QString> m_ch_names;
    QString m_time_format;
    ByteFormat m_byte_format;
    char m_separator;
};


