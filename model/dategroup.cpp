#include "dategroup.h"

DateGroup::DateGroup()
{
}

DateGroup::DateGroup(const DateGroup &copy)
{
    m_startYear = copy.startYear();
    m_startDate = copy.startDate();
    m_startTime = copy.startTime();
    m_endYear = copy.endYear();
    m_endDate = copy.endDate();
    m_endTime = copy.endTime();
    m_period = copy.period();
}

qint32 DateGroup::startYear() const
{
    return m_startYear;
}

void DateGroup::setStartYear(const qint32 startYear)
{
    m_startYear = startYear;
}

QDateTime DateGroup::startDate() const
{
    return m_startDate;
}

void DateGroup::setStartDate(const QDateTime &startDate)
{
    m_startDate = startDate;
}

QTime DateGroup::startTime() const
{
    return m_startTime;
}

void DateGroup::setStartTime(const QTime &startTime)
{
    m_startTime = startTime;
}

qint32 DateGroup::endYear() const
{
    return m_endYear;
}

void DateGroup::setEndYear(const qint32 endYear)
{
    m_endYear = endYear;
}

QDateTime DateGroup::endDate() const
{
    return m_endDate;
}

void DateGroup::setEndDate(const QDateTime &endDate)
{
    m_endDate = endDate;
}

QTime DateGroup::endTime() const
{
    return m_endTime;
}

void DateGroup::setEndTime(const QTime &endTime)
{
    m_endTime = endTime;
}

QString DateGroup::period() const
{
    return m_period;
}

void DateGroup::setPeriod(const QString &period)
{
    m_period = period;
}
