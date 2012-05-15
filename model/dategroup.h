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
    QDateTime startTime() const;
    void setStartTime(const QDateTime &startTime);
    qint32 endYear() const;
    void setEndYear(const qint32 endYear);
    QDateTime endDate() const;
    void setEndDate(const QDateTime &endDate);
    QDateTime endTime() const;
    void setEndTime(const QDateTime &endTime);
    QString period() const;
    void setPeriod(const QString &period);

private:
    qint32 m_startYear;
    QDateTime m_startDate;
    QDateTime m_startTime;
    qint32 m_endYear;
    QDateTime m_endDate;
    QDateTime m_endTime;
    QString m_period;
};

#endif // DATEGROUP_H
