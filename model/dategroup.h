#ifndef DATEGROUP_H
#define DATEGROUP_H

#include <QDate>
#include <QTime>

class DateGroup
{
public:
    DateGroup();
    DateGroup(const DateGroup &copy);
    qint32 startYear() const;
    void setStartYear(const qint32 startYear);
    QDate startDate() const;
    void setStartDate(const QDate &startDate);
    QTime startTime() const;
    void setStartTime(const QTime &startTime);
    qint32 endYear() const;
    void setEndYear(const qint32 endYear);
    QDate endDate() const;
    void setEndDate(const QDate &endDate);
    QTime endTime() const;
    void setEndTime(const QTime &endTime);

private:
    qint32 m_startYear;
    QDate m_startDate;
    QTime m_startTime;
    qint32 m_endYear;
    QDate m_endDate;
    QTime m_endTime;
    QString m_period;
};

#endif // DATEGROUP_H
