#ifndef TIMETYPE_H
#define TIMETYPE_H

#include <QString>
#include <QTime>
#include "formattype.h"

class FormatType;
class FormatGroup;

class TimeType
{
public:

    enum TimeTypeRepresentation {
        enumTimecode,   // To express the start time using timecode compliant with SMPTE ST 12-1:2008
        enumNormalPlayTime, // To express the start time in the format HH:MM:SS.S
        enumEditUnitNumber, // The express the start time as a number of edit Units
        enumTime    // To express the start time in a user defined time format
    };

    TimeType();
    TimeType(const QString &timecode);
    TimeType(const QDateTime &normalPlayTime);
    TimeType(const unsigned int &editRate,
             const unsigned int &factorNumerator,
             const unsigned int &factorDenominator);
    TimeType(const QString &timeString, FormatGroup *time);
    ~TimeType();

    enum TimeTypeRepresentation timeTypeRepresentation() const;
    void setTimeTypeRepresentation(const enum TimeTypeRepresentation timeTypeRepresentation);
    QString timecode() const;
    void setTimecode(const QString &timecode);
    QDateTime normalPlayTime() const;
    void setNormalPlayTime(const QDateTime &normalPlayTime);
    unsigned int editRate() const;
    void setEditRate(unsigned int editRate);
    unsigned int factorNumerator() const;
    void setFactorNumerator(unsigned int factorNumerator);
    unsigned int factorDenominator() const;
    void setFactorDenominator(unsigned int factorDenominator);
    QString timeString() const;
    void setTimeString(const QString &timeString);
    FormatGroup *time() const;
    void setTime(FormatGroup *time);

private:
    enum TimeTypeRepresentation m_timeTypeRepresentation;

    QString m_timecode;

    QDateTime m_normalPlayTime;

    unsigned int m_editRate;
    unsigned int m_factorNumerator;
    unsigned int m_factorDenominator;

    QString m_timeString;
    FormatGroup *m_time;
};

#endif // TIMETYPE_H
