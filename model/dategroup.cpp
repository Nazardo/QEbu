#include "dategroup.h"

DateGroup::DateGroup()
{
    m_startYear = 0;
    m_endYear = 0;
}

DateGroup::~DateGroup()
{
    delete m_startYear;
    delete m_endYear;
}

qint32 *DateGroup::startYear() const
{
    return m_startYear;
}

void DateGroup::setStartYear(const qint32 startYear)
{
    delete m_startYear;
    m_startYear = new qint32(startYear);
}

void DateGroup::removeStartYear()
{
    delete m_startYear;
    m_startYear = 0;
}

QDateTime DateGroup::startDate() const
{
    return m_startDate;
}

void DateGroup::setStartDate(const QDateTime &startDate)
{
    m_startDate = startDate;
}

QDateTime DateGroup::startTime() const
{
    return m_startTime;
}

void DateGroup::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

qint32 *DateGroup::endYear() const
{
    return m_endYear;
}

void DateGroup::setEndYear(const qint32 endYear)
{
    delete m_endYear;
    m_endYear = new qint32(endYear);
}

void DateGroup::removeEndYear()
{
    delete m_endYear;
    m_endYear = 0;
}

QDateTime DateGroup::endDate() const
{
    return m_endDate;
}

void DateGroup::setEndDate(const QDateTime &endDate)
{
    m_endDate = endDate;
}

QDateTime DateGroup::endTime() const
{
    return m_endTime;
}

void DateGroup::setEndTime(const QDateTime &endTime)
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
