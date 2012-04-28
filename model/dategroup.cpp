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
}

qint32 DateGroup::startYear() const
{
    return m_startYear;
}

void DateGroup::setStartYear(const qint32 startYear)
{
    m_startYear = startYear;
}

QDate DateGroup::startDate() const
{
    return m_startDate;
}

void DateGroup::setStartDate(const QDate &startDate)
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

QDate DateGroup::endDate() const
{
    return m_endDate;
}

void DateGroup::setEndDate(const QDate &endDate)
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
