#ifndef TYPECONVERTER_H
#define TYPECONVERTER_H

#include <QDateTime>
#include <QUrl>
#include "model/duration.h"

class TypeConverter
{
public:
    static QDateTime stringToDate(const QString &date);
    static QString dateToString(const QDateTime &date);

    static Duration *stringToDuration(const QString &duration);
    static QString durationToString(const Duration *duration);

    static QDateTime stringToTime(const QString &time);
    static QString timeToString(const QDateTime &time);

    static bool validateUri(const QString &uri);

    static QString errorMsg();

private:
    TypeConverter();

    static QString m_errorMsg;
};

#endif // TYPECONVERTER_H
