#ifndef DURATIONTYPE_H
#define DURATIONTYPE_H

#include <QString>
#include <QTime>
#include "formattype.h"
#include "duration.h"

class FormatGroup;

class DurationType
{
public:

    enum DurationTypeRepresentation {
        enumTimecode,       // To express the duration using timecode compliant with SMPTE ST 12-1:2008
        enumNormalPlayTime, // To express the duration in the format HH:MM:SS.S
        enumEditUnitNumber, // The express the duration as a number of edit Units
        enumTime            // To express the duration in a user defined time format
    };

    DurationType();
    DurationType(const QString &timecode);
    DurationType(const Duration &normalPlayTime);
    DurationType(const unsigned int &editRate,
                const unsigned int &factorNumerator,
                const unsigned int &factorDenominator);
    DurationType(const QString &timeValue, FormatGroup *time);
    ~DurationType();

    enum DurationTypeRepresentation durationTypeRepresentation() const;
    void setDurationTypeRepresentation(const enum DurationTypeRepresentation durationTypeRepresentation);
    QString timecode() const;
    void setTimecode(const QString &timecode);
    Duration normalPlayTime() const;
    void setNormalPlayTime(const Duration &normalPlayTime);
    unsigned int editRate() const;
    void setEditRate(unsigned int editRate);
    unsigned int factorNumerator() const;
    void setFactorNumerator(unsigned int factorNumerator);
    unsigned int factorDenominator() const;
    void setFactorDenominator(unsigned int factorDenominator);
    unsigned long editUnitNumberValue() const;
    void setEditUnitNumberValue(unsigned long editUnitNumberValue);
    QString timeValue() const;
    void setTimeValue(const QString &timeValue);
    FormatGroup *time() const;
    void setTime(FormatGroup *time);

private:
    enum DurationTypeRepresentation m_durationTypeRepresentation;

    QString m_timecode;

    Duration m_normalPlayTime;

    unsigned int m_editRate;
    unsigned int m_factorNumerator;
    unsigned int m_factorDenominator;
    unsigned long m_editUnitNumberValue;

    QString m_timeValue;
    FormatGroup *m_time;
};

#endif // DURATIONTYPE_H
