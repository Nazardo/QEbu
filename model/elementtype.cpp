#include "elementtype.h"
#include <QObject>

ElementType::ElementType()
{
    m_lang = "en";
}

ElementType::ElementType(const QString &value, const QString &lang)
{
    m_value = value;
    m_lang = lang;
}

QString ElementType::value() const
{
    return m_value;
}

void ElementType::setValue(const QString &value)
{
    m_value = value;
}

QString ElementType::lang() const
{
    return m_lang;
}

void ElementType::setLang(const QString &lang)
{
    m_lang = lang;
}

QString ElementType::toString() const
{
    if (m_value.isEmpty())
        return QObject::tr("Undefined element");
    return m_value;
}
