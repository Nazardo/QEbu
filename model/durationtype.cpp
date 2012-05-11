#include "durationtype.h"

DurationType::DurationType(const bool &positive, const int &years, const int &months, const int &days, const int &hours, const int &minutes, const int &seconds, const int &mseconds)
{
    m_positive = positive;
    m_years = years;
    m_months = months;
    m_days = days;
    m_hours = hours;
    m_minutes = minutes;
    m_seconds = seconds;
    m_mseconds = mseconds;
}

bool DurationType::positive() const
{
    return m_positive;
}

void DurationType::setPositive(const bool &positive)
{
    m_positive = positive;
}

int DurationType::years() const
{
    return m_years;
}

void DurationType::setYears(const int &years)
{
    m_years = years;
}

int DurationType::months() const
{
    return m_months;
}

void DurationType::setMonths(const int &months)
{
    m_months = months;
}

int DurationType::days() const
{
    return m_days;
}

void DurationType::setDays(const int &days)
{
    m_days = days;
}

int DurationType::hours() const
{
    return m_hours;
}

void DurationType::setHours(const int &hours)
{
    m_hours = hours;
}

int DurationType::minutes() const
{
    return m_minutes;
}

void DurationType::setMinutes(const int &minutes)
{
    m_minutes = minutes;
}

int DurationType::seconds() const
{
    return m_seconds;
}

void DurationType::setSeconds(const int &seconds)
{
    m_seconds = seconds;
}

int DurationType::mseconds() const
{
    return m_mseconds;
}

void DurationType::setMseconds(const int &mseconds)
{
    m_mseconds = mseconds;
}

bool DurationType::isValid() const
{
    return !isNull();
}

bool DurationType::isNull() const
{
    if (m_years != 0
            || m_months != 0
            || m_days != 0
            || m_hours != 0
            || m_minutes != 0
            || m_seconds != 0
            || m_mseconds != 0)
        return false;
    return true;
}

QString DurationType::toString() const
{
    //Schema duration format: PnYnMnDTnHnMnS

    QString durationString;
    if (!m_positive)
        durationString+="-";

    durationString+="P";
    if (m_years != 0)
        durationString += m_years + "Y";
    if (m_months != 0)
        durationString += m_months + "M";
    if (m_days != 0)
        durationString += m_days + "D";
    if (m_hours != 0 || m_minutes != 0 || m_seconds != 0 || m_mseconds != 0) {
        durationString += m_months + "T";
        if (m_hours != 0)
            durationString += m_hours + "H";
        if (m_minutes != 0)
            durationString += m_minutes + "M";
        if (m_seconds != 0 || m_mseconds != 0) {
            durationString += m_seconds;
            if (m_seconds != 0 || m_mseconds != 0)
                durationString += "." + m_mseconds;
            durationString += "S";
        }
    }

    return durationString;
}
