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

#ifndef DURATION_H
#define DURATION_H

#include <QString>

// This class represent an xsd:duration.
class Duration
{
public:
    Duration(const bool &positive = true, const int &years = 0, const int &months = 0, const int &days = 0, const int &hours = 0, const int &minutes = 0, const int &seconds = 0, const int &mseconds = 0);
    bool positive() const;
    void setPositive(const bool &positive);
    int years() const;
    void setYears(const int &years);
    int months() const;
    void setMonths(const int &months);
    int days() const;
    void setDays(const int &days);
    int hours() const;
    void setHours(const int &hours);
    int minutes() const;
    void setMinutes(const int &minutes);
    int seconds() const;
    void setSeconds(const int &seconds);
    int mseconds() const;
    void setMseconds(const int &mseconds);
    bool isValid() const;
    bool isNull() const;
    QString toString() const;

private:
    bool m_positive;
    int m_years;
    int m_months;
    int m_days;
    int m_hours;
    int m_minutes;
    int m_seconds;
    int m_mseconds;
};

#endif // DURATION_H
