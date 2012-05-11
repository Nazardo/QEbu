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

DurationType *TypeConverter::stringToDuration(const QString &duration)
{

    if (duration.isNull()) {
        m_errorMsg = "stringToDuration received an empty string";
        return new DurationType();
    }
    m_errorMsg = "-no errors-";

    //Schema duration format: PnYnMnDTnHnMnS

    DurationType *durationType = new DurationType();
    int i = 0;
    if (duration[i] == '-') {
        durationType->setPositive(false);
        i++;
    }

    if (duration[i] != 'P') {
        m_errorMsg = "Invalid duration string: " + duration;
        delete durationType;
        return new DurationType();
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
                    durationType->setYears(buf.toInt());
                    break;

                case 'M':
                    durationType->setMonths(buf.toInt());
                    break;

                case 'D':
                    durationType->setDays(buf.toInt());
                    break;

                case 'T':
                    codeTAppeared = true;
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    delete durationType;
                    return new DurationType();
                }

            } else {
                // After T (PnYnMnD T nHnMnS)
                switch (duration[i].toAscii()) {
                case 'H':
                    durationType->setHours(buf.toInt());
                    break;

                case 'M':
                    durationType->setMinutes(buf.toInt());
                    break;

                case '.':
                    // Decimal point may be present in Seconds value
                    durationType->setSeconds(buf.toInt());
                    buf="";
                    for (i++; duration[i].isDigit() && i < duration.length(); i++) {
                        buf += duration[i];
                    }

                    if(duration[i] != 'S' || i >= duration.length()) {
                        m_errorMsg = "Error in duration, S not found after decimal point";
                        delete durationType;
                        return new DurationType();
                    }

                    durationType->setMseconds(buf.toInt());
                    break;

                case 'S':
                    durationType->setSeconds(buf.toInt());
                    break;

                default:
                    m_errorMsg = "Invalid duration string: " + duration;
                    delete durationType;
                    return new DurationType();
                }

            }
            i++;
        }
    }

    return durationType;
}

QString TypeConverter::durationToString(const DurationType *duration)
{
    if (duration->isNull()) {
        m_errorMsg = "durationToString received an empty object";
        return QString();
    }
    m_errorMsg = "-no errors-";

    return duration->toString();
}

QDateTime TypeConverter::stringToTime(const QString &time)
{
    if (time.isNull()) {
        m_errorMsg = "stringToTime received an empty string";
        return QDateTime();
    }
    m_errorMsg = "-no errors-";

    // Time schema format: hh:mm:ss('.'s+)?(zzzzzz)?

    int hours = time.mid(0,2).toInt();
    int minutes = time.mid(3,2).toInt();
    int seconds = time.mid(6,2).toInt();
    int mseconds = 0;
    // Timezone datas will be stored in the year part of QDataTime
    int minutesUTCOffset = -1;
    int offsetSignFlag = 1;
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

        // Timezone datas (will be stored in the year part of QDataTime)
        if (i < time.length()) {

           if (time[i] == 'Z') {
               // UTC time
               timeZone = Qt::UTC;
               minutesUTCOffset = -1;

           } else {

               if (time[i] == '-')
                   offsetSignFlag = 2;
               i++;

               // Offset from the UTC time
               timeZone = Qt::OffsetFromUTC;

               int hours = time.mid(i,2).toInt();
               int minutes = time.mid(i+4,2).toInt();
               minutesUTCOffset = hours*60 + minutes;
               if (minutesUTCOffset == 0)
                   minutesUTCOffset = -1;

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
    QDateTime dt = QDateTime(QDate(minutesUTCOffset,offsetSignFlag,1), QTime(hours,minutes,seconds,mseconds));
    dt.setTimeSpec(timeZone);
    return dt;
}

QString TypeConverter::timeToString(const QDateTime &time)
{
    if (time.isNull()) {
        m_errorMsg = "timeToString received an empty object";
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
        int offsetSignFlag = time.date().month();

        switch (offsetSignFlag) {
        case 1:
            timeString += "+";
            break;
        case 2:
            timeString += "-";
            break;
        default:
            m_errorMsg = "Invalid month value, should be used as flag for the sign of timezone offset (1 or 2)";
            return QString();
        }

        int minutesUTCOffset = time.date().year();

        if(minutesUTCOffset == -1)
            minutesUTCOffset = 0;

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

bool TypeConverter::validateUri(const QString &uri)
{
    return QUrl(uri, QUrl::StrictMode).isValid();
}

QString TypeConverter::errorMsg()
{
    return m_errorMsg;
}
