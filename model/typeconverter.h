#ifndef TYPECONVERTER_H
#define TYPECONVERTER_H

#include <QDate>

class TypeConverter
{
public:
    static QDate stringToDate(QString date);
    static QString dateToString(QDate date);

    static QDate stringToDuration(QString duration);
    static QString durationToString(QDate duration);

    static QTime stringToTime(QString time);
    static QString timeToString(QTime time);

    static bool validateUri(QString uri);

private:
    TypeConverter();
};

#endif // TYPECONVERTER_H
