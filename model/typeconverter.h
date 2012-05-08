#ifndef TYPECONVERTER_H
#define TYPECONVERTER_H

#include <QDateTime>
#include <QUrl>

class TypeConverter
{
public:
    static QDateTime *stringToDate(const QString &date);
    static QString *dateToString(const QDateTime &date);

    static QDateTime *stringToDuration(const QString &duration);
    static QString *durationToString(const QDateTime &duration);

    static QTime *stringToTime(const QString &time);
    static QString *timeToString(const QTime &time);

    static bool validateUri(const QString &uri);

    static QString *errorMsg();

private:
    TypeConverter();

    static QString m_errorMsg;
};

#endif // TYPECONVERTER_H
