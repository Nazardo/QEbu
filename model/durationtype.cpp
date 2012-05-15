#include "durationtype.h"

DurationType::DurationType()
{
    m_time = 0;
}

DurationType::DurationType(const QString &timecode)
{
    m_durationTypeRepresentation = DurationType::enumTimecode;
    m_timecode = timecode;
}

DurationType::DurationType(const Duration &normalPlayTime)
{
    m_durationTypeRepresentation = DurationType::enumNormalPlayTime;
    m_normalPlayTime = normalPlayTime;
}

DurationType::DurationType(const unsigned int &editRate, const unsigned int &factorNumerator, const unsigned int &factorDenominator)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    m_editRate = editRate;
    m_factorNumerator = factorNumerator;
    m_factorDenominator = factorDenominator;
}

DurationType::DurationType(const QString &timeString, FormatGroup *time)
{
    m_durationTypeRepresentation = DurationType::enumTime;
    m_timeValue = timeString;
    m_time = time;
}


DurationType::~DurationType()
{
    delete m_time;
}

DurationType::DurationTypeRepresentation DurationType::durationTypeRepresentation() const
{
    return m_durationTypeRepresentation;
}

void DurationType::setDurationTypeRepresentation(const DurationType::DurationTypeRepresentation durationTypeRepresentation)
{
    m_durationTypeRepresentation = durationTypeRepresentation;
}

QString DurationType::timecode() const
{
    return m_timecode;
}

void DurationType::setTimecode(const QString &timecode)
{
    m_durationTypeRepresentation = DurationType::enumTimecode;
    m_timecode = timecode;
}

Duration DurationType::normalPlayTime() const
{
    return m_normalPlayTime;
}

void DurationType::setNormalPlayTime(const Duration &normalPlayTime)
{
    m_durationTypeRepresentation = DurationType::enumNormalPlayTime;
    m_normalPlayTime = normalPlayTime;
}

unsigned int DurationType::editRate() const
{
    return m_editRate;
}

void DurationType::setEditRate(unsigned int editRate)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    m_editRate = editRate;
}

unsigned int DurationType::factorNumerator() const
{
    return m_factorNumerator;
}

void DurationType::setFactorNumerator(unsigned int factorNumerator)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    m_factorNumerator = factorNumerator;
}

unsigned int DurationType::factorDenominator() const
{
    return m_factorDenominator;
}

void DurationType::setFactorDenominator(unsigned int factorDenominator)
{
    m_durationTypeRepresentation = DurationType::enumEditUnitNumber;
    m_factorDenominator = factorDenominator;
}

unsigned long DurationType::editUnitNumberValue() const
{
    return m_editUnitNumberValue;
}

void DurationType::setEditUnitNumberValue(unsigned long editUnitNumberValue)
{
    m_editUnitNumberValue = editUnitNumberValue;
}

QString DurationType::timeValue() const
{
    return m_timeValue;
}

void DurationType::setTimeValue(const QString &timeString)
{
    m_durationTypeRepresentation = DurationType::enumTime;
    m_timeValue = timeString;
}

FormatGroup *DurationType::time() const
{
    return m_time;
}

void DurationType::setTime(FormatGroup *time)
{
    m_durationTypeRepresentation = DurationType::enumTime;
    delete m_time;
    m_time = time;
}
