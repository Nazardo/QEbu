#include "timetype.h"
#include "typeconverter.h"

TimeType::TimeType()
{
    m_time = 0;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
}

TimeType::TimeType(const QString &timecode)
{
    m_timeTypeRepresentation = TimeType::enumTimecode;
    m_timecode = timecode;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
}

TimeType::TimeType(const QDateTime &normalPlayTime)
{
    m_timeTypeRepresentation = TimeType::enumNormalPlayTime;
    m_normalPlayTime = normalPlayTime;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
}

TimeType::TimeType(const unsigned int &editRate, const unsigned long &editUnitNumberValue, const unsigned int &factorNumerator = 1, const unsigned int &factorDenominator = 1)
{
    m_timeTypeRepresentation = TimeType::enumEditUnitNumber;
    m_editRate = new unsigned int(editRate);
    m_factorNumerator = factorNumerator;
    m_factorDenominator = factorDenominator;
    m_editUnitNumberValue = new unsigned long(editUnitNumberValue);
}

TimeType::TimeType(const QString &timeString, FormatGroup *time)
{
    m_timeTypeRepresentation = TimeType::enumTime;
    m_timeValue = timeString;
    m_time = time;
    m_factorNumerator = 1; // default
    m_factorDenominator = 1; // default
    m_editRate = 0;
    m_editUnitNumberValue = 0;
}

TimeType::~TimeType()
{
    delete m_time;
    delete m_editRate;
    delete m_editUnitNumberValue;
}

TimeType::TimeTypeRepresentation TimeType::timeTypeRepresentation() const
{
    return m_timeTypeRepresentation;
}

QString TimeType::timecode() const
{
    return m_timecode;
}

void TimeType::setTimecode(const QString &timecode)
{
    m_timeTypeRepresentation = TimeType::enumTimecode;
    m_timecode = timecode;
}

QDateTime TimeType::normalPlayTime() const
{
    return m_normalPlayTime;
}

void TimeType::setNormalPlayTime(const QDateTime &normalPlayTime)
{
    m_timeTypeRepresentation = TimeType::enumNormalPlayTime;
    m_normalPlayTime = normalPlayTime;
}

unsigned int *TimeType::editRate() const
{
    return m_editRate;
}

void TimeType::setEditRate(unsigned int editRate)
{
    m_timeTypeRepresentation = TimeType::enumEditUnitNumber;
    delete m_editRate;
    m_editRate = new unsigned int(editRate);
}

void TimeType::clearEditRate()
{
    delete m_editRate;
    m_editRate = 0;
}

unsigned int TimeType::factorNumerator() const
{
    return m_factorNumerator;
}

void TimeType::setFactorNumerator(unsigned int factorNumerator)
{
    m_timeTypeRepresentation = TimeType::enumEditUnitNumber;
    m_factorNumerator = factorNumerator;
}

void TimeType::clearFactorNumerator()
{
    m_factorNumerator = 0;
}

unsigned int TimeType::factorDenominator() const
{
    return m_factorDenominator;
}

void TimeType::setFactorDenominator(unsigned int factorDenominator)
{
    m_timeTypeRepresentation = TimeType::enumEditUnitNumber;
    m_factorDenominator = factorDenominator;
}

void TimeType::clearFactorDenominator()
{
    m_factorDenominator = 0;
}

unsigned long *TimeType::editUnitNumberValue() const
{
    return m_editUnitNumberValue;
}

void TimeType::setEditUnitNumberValue(unsigned long editUnitNumberValue)
{
    m_timeTypeRepresentation = TimeType::enumEditUnitNumber;
    delete m_editUnitNumberValue;
    m_editUnitNumberValue = new unsigned long(editUnitNumberValue);
}

void TimeType::clearEditUnitNumberValue()
{
    delete m_editUnitNumberValue;
    m_editUnitNumberValue = 0;
}

QString TimeType::timeValue() const
{
    return m_timeValue;
}

void TimeType::setTimeValue(const QString &timeString)
{
    m_timeTypeRepresentation = TimeType::enumTime;
    m_timeValue = timeString;
}

FormatGroup *TimeType::time() const
{
    return m_time;
}

void TimeType::setTime(FormatGroup *time)
{
    m_timeTypeRepresentation = TimeType::enumTime;
    delete m_time;
    m_time = time;
}

QString TimeType::toString() const
{
    switch (m_timeTypeRepresentation) {
        case DurationType::enumEditUnitNumber:
            return QString::number(*m_editUnitNumberValue, 10);
        case DurationType::enumNormalPlayTime:
            return TypeConverter::dateToString(m_normalPlayTime);
        case DurationType::enumTime:
            return m_timeValue;
        case DurationType::enumTimecode:
            return m_timecode;
    }
    return QObject::tr("Undefined time");
}




