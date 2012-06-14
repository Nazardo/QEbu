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

#include "dategroup.h"
#include <QStringList>

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

QString DateGroup::toString() const
{
    QStringList sl;
    if (m_startDate.isValid())
        sl.append(m_startDate.date().toString());
    if (m_startTime.isValid())
        sl.append(m_startTime.time().toString());
    if (m_startYear)
        sl.append(QString::number(*m_startYear));
    if (sl.size() == 0)
        return QString(QObject::tr("Unspecified starting date"));
    return sl.join(" ");
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
