#include "typeconverter.h"
#include <QDebug>

QString TypeConverter::m_errorMsg = "-no errors-";

TypeConverter::TypeConverter()
{
}

QDateTime TypeConverter::stringToDate(const QString &date)
{
    // Schema date format: '-'? yyyy '-' mm '-' dd zzzzzz?

    if (date[0] == '-') {
        m_errorMsg = "B.C. years are considered invalid";
        return QDateTime();
    }

    if (date.length() < 10) {
        m_errorMsg = "Invalid date length (considering a 4 digits year)";
        return QDateTime();
    }

    QDateTime dateTime=QDateTime::fromString(date.left(10),"yyyy-MM-dd");

    if (date.length() == 10) {
        // Unspecified timezone
        dateTime.setTimeSpec(Qt::LocalTime);
    } else {
        // Timezone format: (('+' | '-') hh ':' mm) | 'Z'
        int hours;
        int minutes;

        if(date[10] == 'Z'){
            // UTC time
            dateTime.setTimeSpec(Qt::UTC);
            hours = 0;
            minutes = 0;
        } else {
            // Offset from the UTC time
            dateTime.setTimeSpec(Qt::OffsetFromUTC);
            hours = date.mid(10,3).toInt();
            minutes = date.mid(14,2).toInt();
            if (date[13] != ':') {
                m_errorMsg = "Invalid hours/minutes separator: " + date[13].toAscii();
                return QDateTime();
            }
            if (hours < -14 || hours > 14) {
                m_errorMsg = "Invalid hours value: "+ QString::number(hours);
                return QDateTime();
            }
            if (minutes<0 || minutes>59) {
                m_errorMsg = "Invalid minutes value: "+ QString::number(minutes);
                return QDateTime();
            }
            if ((hours == 14 || hours == -14) && minutes != 0) {
                m_errorMsg = "Invalid hours/minutes value: " + QString::number(hours) + "/" + QString::number(minutes);
                return QDateTime();
            }
        }

        //qDebug() <<"ora:" + QString::number(hours) + " minuti: " + QString::number(minutes);
        //if(dateTime->isValid()==false) qDebug() <<"dateTime is invalid!";

        dateTime.setUtcOffset( (hours * 60 + minutes) * 60);

        //if(dateTime->isValid()==false) qDebug() <<"dateTime is invalid!";
    }

    return dateTime;
}

QString TypeConverter::dateToString(const QDateTime &date)
{
    QString d(date.toString("yyyy-MM-dd"));
    int utcOffset = date.utcOffset();

    if (date.timeSpec() == Qt::UTC && utcOffset == 0) {
        d.append("Z");
    } else {
        if (date.timeSpec() == Qt::OffsetFromUTC){
            if (utcOffset > 0) {
                d.append("+");
            } else {
                d.append("-");
                utcOffset*=-1;
            }
            utcOffset /= 60;
            int hours = utcOffset / 60;
            int minutes = utcOffset % 60;

            if (hours < 10 && hours > -10)
                d.append("0");
            d.append(QString::number(hours) + ":");
            if (minutes < 10)
                d.append("0");
            d.append(QString::number(minutes));
        }
    }
    return d;
}

QDateTime TypeConverter::stringToDuration(const QString &duration)
{
    //Schema duration format: PnYnMnDTnHnMnS

    int i = 0;
    bool negative = false;
    if (duration[i] == '-') {
        negative=true;
        i++;
    }

    if (duration[i] != 'P') {
        m_errorMsg = "Invalid duration string: " + duration;
        return QDateTime();
    }

    i++;
    int years = 0;
    int months = 0;
    int days = 0;
    while (i < duration.length()) {

        for (; i < duration.length() && duration[i].isDigit(); i++) {}

        if(i < duration.length()){
            switch(duration[i]) {
            case 'Y':
                break;
            case 'M':
                break;
            case 'D':
                break;
            case 'T':
                break;
            default:

            }

            i++;
        }


    }


    int hours = 0;
    int minutes = 0;
    int seconds = 0;



    return QDateTime(); //TODO
}

QString TypeConverter::durationToString(const QDateTime &duration)
{
    return QString(); //TODO
}

QTime TypeConverter::stringToTime(const QString &time)
{
    return QTime(); //TODO
}

QString TypeConverter::timeToString(const QTime &time)
{
    return QString(); //TODO
}

bool TypeConverter::validateUri(const QString &uri)
{
    return QUrl(uri, QUrl::StrictMode).isValid();
}

QString TypeConverter::errorMsg()
{
    return m_errorMsg;
}
