#include "timetype.h"

TimeType::TimeType()
{
    m_time = 0;
}

TimeType::TimeType(const QString &timecode)
{
    m_timeTypeRepresentation = TimeType::enumTimecode;
    m_timecode = timecode;
}

TimeType::TimeType(const QDateTime &normalPlayTime)
{
    m_timeTypeRepresentation = TimeType::enumNormalPlayTime;
    m_normalPlayTime = normalPlayTime;
}

TimeType::TimeType(const unsigned int &editRate, const unsigned int &factorNumerator, const unsigned int &factorDenominator)
{
    m_timeTypeRepresentation = TimeType::enumEditUnitNumber;
    m_editRate = editRate;
    m_factorNumerator = factorNumerator;
    m_factorDenominator = factorDenominator;
}

TimeType::TimeType(const QString &timeString, FormatGroup *time)
{
    m_timeTypeRepresentation = TimeType::enumTime;
    m_timeString = timeString;
    m_time = time;
}

TimeType::~TimeType()
{
    delete m_time;
}

QString TimeType::timecode() const
{
    return m_timecode;
}

void TimeType::setTimecode(const QString &timecode)
{
    m_timecode = timecode;
}

QDateTime TimeType::normalPlayTime() const
{
    return m_normalPlayTime;
}

void TimeType::setNormalPlayTime(const QDateTime &normalPlayTime)
{
    m_normalPlayTime = normalPlayTime;
}

unsigned int TimeType::editRate() const
{
    return m_editRate;
}

void TimeType::setEditRate(unsigned int editRate)
{
    m_editRate = editRate;
}

unsigned int TimeType::factorNumerator() const
{
    return m_factorNumerator;
}

void TimeType::setFactorNumerator(unsigned int factorNumerator)
{
    m_factorNumerator = factorNumerator;
}

unsigned int TimeType::factorDenominator() const
{
    return m_factorDenominator;
}

void TimeType::setFactorDenominator(unsigned int factorDenominator)
{
    m_factorDenominator = factorDenominator;
}

FormatGroup *TimeType::time() const
{
    return m_time;
}

void TimeType::setTime(FormatGroup *time)
{
    m_time = time;
}




