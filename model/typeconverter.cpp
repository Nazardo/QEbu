#include "typeconverter.h"
#include <QDebug>

QString TypeConverter::m_errorMsg = "-no errors-";

TypeConverter::TypeConverter()
{
}

QDateTime TypeConverter::stringToDate(const QString &date)
{
    if(date.isNull()){
        m_errorMsg = "stringToDate received an empty string";
        return QDateTime();
    }
    m_errorMsg = "-no errors-";

    // Schema date format: '-'? yyyy '-' mm '-' dd zzzzzz?

    // Find the year and the number of digits used for the year
    int i=0;
    QString yearString;
    if (date[i] == '-'){
        yearString+="-";
        i++;
    }

    while(date[i].isDigit()){
        yearString+=date[i];
        i++;
    }

    if(yearString.toInt() == 0){
        m_errorMsg = "Dates in year '0' are considered invalid (see QDateTime documentation)";
        return QDateTime();
    }

    if(i > 5 || (i > 4 && yearString.toInt() > 0)){
        m_errorMsg = "Year can be of max 4 digits";
        return QDateTime();
    }

    QDateTime dateTime=QDateTime::fromString(date.mid(i,6),"-MM-dd");

    //Set the correct year
    int yearDiff=yearString.toInt() - dateTime.date().year();
    qDebug() <<yearDiff <<" yearDiff........";
    if(yearString.toInt() > 0)
        dateTime=dateTime.addYears(  yearDiff );
    else
        dateTime=dateTime.addYears( yearDiff + 1);


    i+=6;   // Add the length of "-MM-dd"

    if (date.length() == i) {
        // Unspecified timezone
        dateTime.setTimeSpec(Qt::LocalTime);
    } else {
        // Timezone format: (('+' | '-') hh ':' mm) | 'Z'
        int hours;
        int minutes;

        if(date[i] == 'Z'){
            // UTC time
            dateTime.setTimeSpec(Qt::UTC);
            hours = 0;
            minutes = 0;
        } else {
            // Offset from the UTC time
            dateTime.setTimeSpec(Qt::OffsetFromUTC);
            hours = date.mid(i,3).toInt();
            minutes = date.mid(i+4,2).toInt();
            if (date[i+3] != ':') {
                m_errorMsg = "Invalid hours/minutes separator: " + date[i+3].toAscii();
                return QDateTime();
            }
            if (hours < -14 || hours > 14) {
                m_errorMsg = "Invalid hours value: "+ QString::number(hours);
                return QDateTime();
            }
            if (minutes < 0 || minutes > 59) {
                m_errorMsg = "Invalid minutes value: "+ QString::number(minutes);
                return QDateTime();
            }
            if ((hours == 14 || hours == -14) && minutes != 0) {
                m_errorMsg = "Invalid hours/minutes value: " + QString::number(hours) + "/" + QString::number(minutes);
                return QDateTime();
            }
        }

        dateTime.setUtcOffset((hours * 60 + minutes) * 60);
    }

    return dateTime;
}

QString TypeConverter::dateToString(const QDateTime &date)
{
    if(date.isNull()){
        m_errorMsg = "dateToString received an empty object";
        return QString();
    }
    m_errorMsg = "-no errors-";

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

    if (duration.isNull()) {
        m_errorMsg = "stringToDuration received an empty string";
        return QDateTime();
    }
    m_errorMsg = "-no errors-";

    /* // duration schema type
    //Schema duration format: PnYnMnDTnHnMnS

    int i = 0;
    bool negative = false;
    if (duration[i] == '-') {
        negative = true;
        i++;
        qDebug() <<"WUT";
    }

    if (duration[i] != 'P') {
        m_errorMsg = "Invalid duration string: " + duration;
        return QDateTime();
    }

    i++;
    int years = 4712;   // Invalid year value (0 is not accepted by QDateTime, 4713 is the lower bound)
    int months = 0;
    int days = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int milliseconds = 0;
    bool codeTAppeared = false;
    while (i < duration.length()) {

        QString buf;
        for (; i < duration.length() && duration[i].isDigit(); i++) {
            buf += duration[i];
        }

        if (i < duration.length()) {

            if (codeTAppeared == false) {
                // After T (PnYnMnD T nHnMnS)
                switch (duration[i].toAscii()) {
                case 'Y':
                    years  =buf.toInt();
                    break;

                case 'M':
                    months = buf.toInt();
                    break;

                case 'D':
                    days = buf.toInt();
                    break;

                case 'T':
                    codeTAppeared = true;
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    return QDateTime();
                }

            } else {
                // Before T (PnYnMnD T nHnMnS)
                switch (duration[i].toAscii()) {
                case 'H':
                    hours = buf.toInt();
                    break;

                case 'M':
                    minutes = buf.toInt();
                    break;

                case '.':
                    // Decimal point may be present in Seconds value
                    buf="";
                    for (i++; i < duration.length() && duration[i].isDigit(); i++) {
                        buf += duration[i];
                    }

                    if (i < duration.length() || duration[i] != 'S') {
                        m_errorMsg = "Error in duration, S not found after decimal point";
                        return QDateTime();
                    }

                    milliseconds = buf.toInt();
                    break;

                case 'S':
                    seconds = buf.toInt();
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    return QDateTime();
                }

            }
            i++;
        }
    }

    if (negative) {
        // Mark negative duration with a negative year
        years = years*-1 +1;    // Must be incremented by 1
    }

    qDebug() <<years <<"Y";
    qDebug() <<months <<"M";
    qDebug() <<days <<"D";

    QDateTime dateTime(QDate(years,months,days),QTime(hours,minutes,seconds,milliseconds));

    qDebug() <<dateTime.date().year() <<"Y";
    qDebug() <<dateTime.date().month() <<"M";
    qDebug() <<dateTime.date().day() <<"D";

    return dateTime;
    */
    return QDateTime();
}

QString TypeConverter::durationToString(const QDateTime &duration)
{
    if (duration.isNull()) {
        m_errorMsg = "stringToDuration received an empty string";
        return QString();
    }
    m_errorMsg = "-no errors-";

    /* //duration schema type
    //Schema duration format: PnYnMnDTnHnMnS

    int years = duration.date().year();
    int months = duration.date().month();
    int days = duration.date().day();
    int hours = duration.time().hour();
    int minutes = duration.time().minute();
    int seconds = duration.time().second();
    int milliseconds = duration.time().msec();

    QString durationString;
    if (years < 0) {
        durationString+="-";
        years *= -1;
    }
    durationString+="P";
    if (years != 4712)  // Invalid year value
        durationString += years + "Y";
    if (months != 0)
        durationString += months + "M";
    if (days != 0)
        durationString += days + "D";
    if (hours != 0 || minutes != 0 || seconds != 0) {
        durationString += months + "T";
        if (hours != 0)
            durationString += hours + "H";
        if (minutes != 0)
            durationString += minutes + "M";
        if (seconds != 0 || milliseconds != 0) {
            durationString += seconds;
            if (seconds != 0 || milliseconds != 0)
                durationString += "." + milliseconds;
            durationString += "S";
        }
    }

    return durationString;
    */
    return QString;
}

QTime TypeConverter::stringToTime(const QString &time)
{
    if (time.isNull()) {
        m_errorMsg = "stringToTime received an empty string";
        return QTime();
    }
    m_errorMsg = "-no errors-";

    // Time schama format: hh:mm:ss('.'s+)?(zzzzzz)?

    int hours = time.mid(0,2).toInt();
    int minutes = time.mid(3,2).toInt();
    int seconds = time.mid(6,2).toInt();
    QTime t(hours,minutes,seconds);
    int milliseconds = 0;
    int i=9;
    if (time.length() > 10) {
       while (i < time.length() && time[i].isDigit())
           i++;

       milliseconds = time.mid(9,i-9).toInt();

       if(time[i] == 'Z'){
           // UTC time
           t..setTimeSpec(Qt::UTC);
           hours = 0;
           minutes = 0;
       } else {
           // Offset from the UTC time
           dateTime.setTimeSpec(Qt::OffsetFromUTC);
           hours = date.mid(i,3).toInt();
           minutes = date.mid(i+4,2).toInt();
           if (date[i+3] != ':') {
               m_errorMsg = "Invalid hours/minutes separator: " + date[i+3].toAscii();
               return QDateTime();
           }
           if (hours < -14 || hours > 14) {
               m_errorMsg = "Invalid hours value: "+ QString::number(hours);
               return QDateTime();
           }
           if (minutes < 0 || minutes > 59) {
               m_errorMsg = "Invalid minutes value: "+ QString::number(minutes);
               return QDateTime();
           }
           if ((hours == 14 || hours == -14) && minutes != 0) {
               m_errorMsg = "Invalid hours/minutes value: " + QString::number(hours) + "/" + QString::number(minutes);
               return QDateTime();
           }
       }

       dateTime.setUtcOffset((hours * 60 + minutes) * 60);
    }


    while (i < duration.length()) {

        QString buf;
        for (; i < duration.length() && duration[i].isDigit(); i++) {
            buf += duration[i];
        }

        if (i < duration.length()) {

            if (codeTAppeared == false) {
                // After T (PnYnMnD T nHnMnS)
                switch (duration[i].toAscii()) {
                case 'Y':
                    years  =buf.toInt();
                    break;

                case 'M':
                    months = buf.toInt();
                    break;

                case 'D':
                    days = buf.toInt();
                    break;

                case 'T':
                    codeTAppeared = true;
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    return QDateTime();
                }

            } else {
                // Before T (PnYnMnD T nHnMnS)
                switch (duration[i].toAscii()) {
                case 'H':
                    hours = buf.toInt();
                    break;

                case 'M':
                    minutes = buf.toInt();
                    break;

                case '.':
                    // Decimal point may be present in Seconds value
                    buf="";
                    for (i++; i < duration.length() && duration[i].isDigit(); i++) {
                        buf += duration[i];
                    }

                    if (i < duration.length() || duration[i] != 'S') {
                        m_errorMsg = "Error in duration, S not found after decimal point";
                        return QDateTime();
                    }

                    milliseconds = buf.toInt();
                    break;

                case 'S':
                    seconds = buf.toInt();
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    return QDateTime();
                }

            }
            i++;
        }
    }

    if (negative) {
        // Mark negative duration with a negative year
        years = years*-1 +1;    // Must be incremented by 1
    }

    qDebug() <<years <<"Y";
    qDebug() <<months <<"M";
    qDebug() <<days <<"D";

    QDateTime dateTime(QDate(years,months,days),QTime(hours,minutes,seconds,milliseconds));

    qDebug() <<dateTime.date().year() <<"Y";
    qDebug() <<dateTime.date().month() <<"M";
    qDebug() <<dateTime.date().day() <<"D";

    return dateTime;
    */
    return QDateTime();
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
