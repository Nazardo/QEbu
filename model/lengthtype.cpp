#include "lengthtype.h"
#include <QObject>

LengthType::LengthType()
{
    m_value= 0;
}

LengthType::~LengthType()
{
    delete m_value;
}

LengthType::LengthType(const unsigned int &value, const QString &unit)
{
    m_value = new unsigned int(value);
    m_unit = unit;
}

unsigned int *LengthType::value() const
{
    return m_value;
}

void LengthType::setValue(const unsigned int &value)
{
    delete m_value;
    m_value = new unsigned int(value);
}

QString LengthType::unit() const
{
    return m_unit;
}

void LengthType::setUnit(const QString &unit)
{
    m_unit = unit;
}

QString LengthType::toString() const
{
    if (m_value)
        return QString::number(*m_value);
    return QObject::tr("Undefined length");
}
