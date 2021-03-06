/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "duration.h"

Duration::Duration(const bool &positive, const int &years, const int &months, const int &days, const int &hours, const int &minutes, const int &seconds, const int &mseconds)
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

bool Duration::positive() const
{
    return m_positive;
}

void Duration::setPositive(const bool &positive)
{
    m_positive = positive;
}

int Duration::years() const
{
    return m_years;
}

void Duration::setYears(const int &years)
{
    m_years = years;
}

int Duration::months() const
{
    return m_months;
}

void Duration::setMonths(const int &months)
{
    m_months = months;
}

int Duration::days() const
{
    return m_days;
}

void Duration::setDays(const int &days)
{
    m_days = days;
}

int Duration::hours() const
{
    return m_hours;
}

void Duration::setHours(const int &hours)
{
    m_hours = hours;
}

int Duration::minutes() const
{
    return m_minutes;
}

void Duration::setMinutes(const int &minutes)
{
    m_minutes = minutes;
}

int Duration::seconds() const
{
    return m_seconds;
}

void Duration::setSeconds(const int &seconds)
{
    m_seconds = seconds;
}

int Duration::mseconds() const
{
    return m_mseconds;
}

void Duration::setMseconds(const int &mseconds)
{
    m_mseconds = mseconds;
}

bool Duration::isValid() const
{
    return !isNull();
}

bool Duration::isNull() const
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

QString Duration::toString() const
{
    //Schema duration format: PnYnMnDTnHnMnS

    QString durationString;
    if (!m_positive)
        durationString+="-";

    durationString+="P";
    if (m_years != 0)
        durationString += QString::number(m_years) + "Y";
    if (m_months != 0)
        durationString += QString::number(m_months) + "M";
    if (m_days != 0)
        durationString += QString::number(m_days) + "D";

    if (m_hours != 0 || m_minutes != 0 || m_seconds != 0 || m_mseconds != 0) {
        durationString += "T";
        if (m_hours != 0)
            durationString += QString::number(m_hours) + "H";
        if (m_minutes != 0)
            durationString += QString::number(m_minutes) + "M";
        if (m_seconds != 0 || m_mseconds != 0) {
            durationString += QString::number(m_seconds);
            if (m_mseconds != 0)
                durationString += "." + QString::number(m_mseconds);
            durationString += "S";
        }
    }

    return durationString;
}

