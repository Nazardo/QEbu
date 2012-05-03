#include "lengthtype.h"

LengthType::LengthType()
{
}

LengthType::LengthType(const unsigned int &value)
{
    m_value = value;
}

unsigned int LengthType::value() const
{
    return m_value;
}

void LengthType::setValue(const unsigned int &value)
{
    m_value = value;
}

QString LengthType::unit() const
{
    return m_unit;
}

void LengthType::setUnit(const QString &unit)
{
    m_unit = unit;
}