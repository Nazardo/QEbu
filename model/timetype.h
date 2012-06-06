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
             const unsigned long &editUnitNumberValue,
             const unsigned int &factorNumerator,
             const unsigned int &factorDenominator);
    TimeType(const QString &timeValue, FormatGroup *time);
    ~TimeType();

    enum TimeTypeRepresentation timeTypeRepresentation() const;
    QString timecode() const;
    void setTimecode(const QString &timecode);
    QDateTime normalPlayTime() const;
    void setNormalPlayTime(const QDateTime &normalPlayTime);
    unsigned int *editRate() const;
    void setEditRate(unsigned int editRate);
    void clearEditRate();
    unsigned int factorNumerator() const;
    void setFactorNumerator(unsigned int factorNumerator);
    void clearFactorNumerator();
    unsigned int factorDenominator() const;
    void setFactorDenominator(unsigned int factorDenominator);
    void clearFactorDenominator();
    unsigned long *editUnitNumberValue() const;
    void setEditUnitNumberValue(unsigned long editUnitNumberValue);
    void clearEditUnitNumberValue();
    QString timeValue() const;
    void setTimeValue(const QString &timeValue);
    FormatGroup *time() const;
    void setTime(FormatGroup *time);
    QString toString() const;
private:
    enum TimeTypeRepresentation m_timeTypeRepresentation;

    QString m_timecode;

    QDateTime m_normalPlayTime;

    unsigned int *m_editRate;
    unsigned int m_factorNumerator;
    unsigned int m_factorDenominator;
    unsigned long *m_editUnitNumberValue;

    QString m_timeValue;
    FormatGroup *m_time;
};

#endif // TIMETYPE_H
