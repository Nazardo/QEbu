#include "typeconverter.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

QString TypeConverter::m_errorMsg = "-no errors-";
QValidator *TypeConverter::m_uriValidator = 0;

TypeConverter::TypeConverter()
{
}

QDateTime TypeConverter::stringToDate(const QString &date)
{
    if(date.isEmpty()){
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
    if(!date.isValid()){
        m_errorMsg = "dateToString received an invalid object";
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

Duration *TypeConverter::stringToDuration(const QString &duration)
{

    if (duration.isEmpty()) {
        m_errorMsg = "stringToDuration received an empty string";
        return new Duration();
    }
    m_errorMsg = "-no errors-";

    //Schema duration format: PnYnMnDTnHnMnS

    Duration *d = new Duration();
    int i = 0;
    if (duration[i] == '-') {
        d->setPositive(false);
        i++;
    }

    if (duration[i] != 'P') {
        m_errorMsg = "Invalid duration string: " + duration;
        delete d;
        return new Duration();
    }

    i++;
    bool codeTAppeared = false;
    while (i < duration.length()) {

        QString buf;
        for (; i < duration.length() && duration[i].isDigit(); i++) {
            buf += duration[i];
        }

        if (i < duration.length()) {

            if (codeTAppeared == false) {

                // Before T (PnYnMnD T nHnMnS)
                switch (duration[i].toAscii()) {
                case 'Y':
                    d->setYears(buf.toInt());
                    break;

                case 'M':
                    d->setMonths(buf.toInt());
                    break;

                case 'D':
                    d->setDays(buf.toInt());
                    break;

                case 'T':
                    codeTAppeared = true;
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    delete d;
                    return new Duration();
                }

            } else {
                // After T (PnYnMnD T nHnMnS)
                switch (duration[i].toAscii()) {
                case 'H':
                    d->setHours(buf.toInt());
                    break;

                case 'M':
                    d->setMinutes(buf.toInt());
                    break;

                case '.':
                    // Decimal point may be present in Seconds value
                    d->setSeconds(buf.toInt());
                    buf="";
                    for (i++; duration[i].isDigit() && i < duration.length(); i++) {
                        buf += duration[i];
                    }

                    if(duration[i] != 'S' || i >= duration.length()) {
                        m_errorMsg = "Error in duration, S not found after decimal point";
                        delete d;
                        return new Duration();
                    }

                    d->setMseconds(buf.toInt());
                    break;

                case 'S':
                    d->setSeconds(buf.toInt());
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    delete d;
                    return new Duration();
                }

            }
            i++;
        }
    }

    return d;
}

QString TypeConverter::durationToString(const Duration *duration)
{
    if (!duration) {
        m_errorMsg = "durationToString received a null object";
        return QString();
    }
    if (!duration->isValid()) {
        m_errorMsg = "durationToString received an invalid object";
        return QString();
    }
    m_errorMsg = "-no errors-";

    return duration->toString();
}

QDateTime TypeConverter::stringToTime(const QString &time)
{
    if (time.isEmpty()) {
        m_errorMsg = "stringToTime received an empty string";
        return QDateTime();
    }
    m_errorMsg = "-no errors-";

    // Time schema format: hh:mm:ss('.'s+)?(zzzzzz)?

    int hours = time.mid(0,2).toInt();
    int minutes = time.mid(3,2).toInt();
    int seconds = time.mid(6,2).toInt();
    int mseconds = 0;

    int minutesUTCOffset = 0;
    Qt::TimeSpec timeZone=Qt::LocalTime;

    int i = 8;
    if (i < time.length()) {

        // Milliseconds
        if (time[i] == '.') {
            QString buf;
            for (i++; i < time.length() && time[i].isDigit(); i++)
                buf += time[i];
            mseconds = buf.toInt();
        }

        // Timezone datas
        if (i < time.length()) {

           if (time[i] == 'Z') {
               // UTC time
               timeZone = Qt::UTC;
               minutesUTCOffset = 0;

           } else {
               int offsetSignFlag = 1;
               if (time[i] == '-')
                   offsetSignFlag = -1;
               i++;

               // Offset from the UTC time
               timeZone = Qt::OffsetFromUTC;

               int hours = time.mid(i,2).toInt();
               int minutes = time.mid(i+4,2).toInt();
               minutesUTCOffset = hours*60 + minutes;
               minutesUTCOffset*=offsetSignFlag;

               if (time[i+2] != ':') {
                   m_errorMsg = "Invalid hours/minutes separator: " + time[i+2].toAscii();
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
        }
    }
    QDateTime dt = QDateTime(QDate(1,1,1), QTime(hours,minutes,seconds,mseconds));
    dt.setUtcOffset(minutesUTCOffset*60);
    dt.setTimeSpec(timeZone);
    return dt;
}

QString TypeConverter::timeToString(const QDateTime &time)
{
    if (!time.isValid()) {
        m_errorMsg = "timeToString received an invalid object";
        return QString();
    }
    m_errorMsg = "-no errors-";

    QString timeString;

    int hours = time.time().hour();
    int minutes = time.time().minute();
    int seconds = time.time().second();
    int mseconds = time.time().msec();

    if (hours < 10)
        timeString += "0";
    timeString += QString::number(hours) + ":";

    if (minutes < 10)
        timeString += "0";
    timeString += QString::number(minutes) + ":";

    if (seconds < 10)
        timeString += "0";
    timeString += QString::number(seconds);

    if (mseconds > 0)
        timeString += "." + QString::number(mseconds);

    switch (time.timeSpec()) {
    case Qt::LocalTime: // Nothing to add
        break;

    case Qt::UTC:
        timeString += "Z";
        break;

    case Qt::OffsetFromUTC:

        // Add the timezone
        if (time.utcOffset()>=0) {
            timeString += "+";
        } else {
            timeString += "-";
        }

        int minutesUTCOffset = time.utcOffset() / 60;
        if (minutesUTCOffset<0)
            minutesUTCOffset*=-1;

        int hoursOffset=minutesUTCOffset/60;
        int minutesOffset=minutesUTCOffset%60;

        if (hoursOffset < 10)
            timeString += "0";
        timeString += QString::number(hoursOffset) + ":";

        if (minutesOffset < 10)
            timeString += "0";
        timeString += QString::number(minutesOffset);
    }

    return timeString;
}

QDateTime TypeConverter::timeToDateTime(const QTime &time, Qt::TimeSpec timeSpec, int minutesUTCOffset)
{
    QDateTime dt = QDateTime(QDate(1,1,1), time);
    dt.setUtcOffset(minutesUTCOffset*60);
    dt.setTimeSpec(timeSpec);
    return dt;
}

QValidator *TypeConverter::getUriValidator()
{
    if (m_uriValidator!=0)
        return m_uriValidator;
    else {
        m_uriValidator = new QRegExpValidator(QRegExp("(\\S ?[\\t\\r\\n]{0}((( ){2,}){0}))*",Qt::CaseInsensitive));
        return m_uriValidator;
    }
}

QString TypeConverter::errorMsg()
{
    return m_errorMsg;
}
