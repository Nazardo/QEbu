#include "timetype.h"

TimeType::TimeType()
{
    m_time = 0;
}

TimeType::TimeType(const QString &timecode,
                   const QTime &normalPlayTime)
    : m_timecode(timecode), m_normalPlayTime(normalPlayTime)
{
    m_time = 0;
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

QTime TimeType::normalPlayTime() const
{
    return m_normalPlayTime;
}

void TimeType::setNormalPlayTime(const QTime &normalPlayTime)
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




