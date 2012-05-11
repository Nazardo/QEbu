#ifndef DURATIONTYPE_H
#define DURATIONTYPE_H

#include <QTime>
#include <QString>

// This class represent an xsd:duration. It implements QTime just to be easier to handle.
class DurationType : public QTime
{
public:
    DurationType(const bool &positive = true, const int &years = 0, const int &months = 0, const int &days = 0, const int &hours = 0, const int &minutes = 0, const int &seconds = 0, const int &mseconds = 0);
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

#endif // DURATIONTYPE_H
