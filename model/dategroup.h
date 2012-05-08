#ifndef DATEGROUP_H
#define DATEGROUP_H

#include <QDateTime>
#include <QTime>

class DateGroup
{
public:
    DateGroup();
    DateGroup(const DateGroup &copy);
    qint32 startYear() const;
    void setStartYear(const qint32 startYear);
    QDateTime startDate() const;
    void setStartDate(const QDateTime &startDate);
    QTime startTime() const;
    void setStartTime(const QTime &startTime);
    qint32 endYear() const;
    void setEndYear(const qint32 endYear);
    QDateTime endDate() const;
    void setEndDate(const QDateTime &endDate);
    QTime endTime() const;
    void setEndTime(const QTime &endTime);
    QString period() const;
    void setPeriod(const QString &period);

private:
    qint32 m_startYear;
    QDateTime m_startDate;
    QTime m_startTime;
    qint32 m_endYear;
    QDateTime m_endDate;
    QTime m_endTime;
    QString m_period;
};

#endif // DATEGROUP_H
