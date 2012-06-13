/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
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

#ifndef DATEGROUP_H
#define DATEGROUP_H

#include <QDateTime>
#include <QTime>

class DateGroup
{
public:
    DateGroup();
    ~DateGroup();
    QString toString() const;
    qint32 *startYear() const;
    void setStartYear(const qint32 startYear);
    void removeStartYear();
    QDateTime startDate() const;
    void setStartDate(const QDateTime &startDate);
    QDateTime startTime() const;
    void setStartTime(const QDateTime &startTime);
    qint32 *endYear() const;
    void setEndYear(const qint32 endYear);
    void removeEndYear();
    QDateTime endDate() const;
    void setEndDate(const QDateTime &endDate);
    QDateTime endTime() const;
    void setEndTime(const QDateTime &endTime);
    QString period() const;
    void setPeriod(const QString &period);

private:
    qint32 *m_startYear;
    QDateTime m_startDate;
    QDateTime m_startTime;
    qint32 *m_endYear;
    QDateTime m_endDate;
    QDateTime m_endTime;
    QString m_period;
};

#endif // DATEGROUP_H
