#ifndef TIMETYPE_H
#define TIMETYPE_H

#include <QString>
#include <QTime>
#include "formattype.h"

class FormatType;

class TimeType
{
public:
    TimeType();
    TimeType(const QString &timecode,
             const QTime &normalPlayTime);
    ~TimeType();
    QString timecode() const;
    void setTimecode(const QString &timecode);
    QTime normalPlayTime() const;
    void setNormalPlayTime(const QTime &normalPlayTime);
    unsigned int editRate() const;
    void setEditRate(unsigned int editRate);
    unsigned int factorNumerator() const;
    void setFactorNumerator(unsigned int factorNumerator);
    unsigned int factorDenominator() const;
    void setFactorDenominator(unsigned int factorDenominator);
    FormatGroup *time() const;
    void setTime(FormatGroup *time);
private:
    QString m_timecode;
    QTime m_normalPlayTime;
    unsigned int m_editRate;
    unsigned int m_factorNumerator;
    unsigned int m_factorDenominator;
    FormatGroup *m_time;
};

#endif // TIMETYPE_H
