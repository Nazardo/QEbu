#include "typegroup.h"
#include <QObject>

TypeGroup::TypeGroup()
{
}

void TypeGroup::setTypeLabel(const QString &typeLabel)
{
    m_typeLabel = typeLabel;
}

QString TypeGroup::typeLabel() const
{
    return m_typeLabel;
}

void TypeGroup::setTypeDefinition(const QString &typeDefinition)
{
    m_typeDefinition = typeDefinition;
}

QString TypeGroup::typeDefinition() const
{
    return m_typeDefinition;
}

void TypeGroup::setTypeLink(const QString &typeLink)
{
    m_typeLink = typeLink;
}

QString TypeGroup::toString() const
{
    if (!m_typeLabel.isEmpty())
        return m_typeLabel;
    if (!m_typeDefinition.isEmpty())
        return m_typeDefinition;
    if (!m_typeLink.isEmpty())
        return m_typeLink;
    return QObject::tr("Undefined type");
}

QString TypeGroup::typeLink() const
{
    return m_typeLink;
}
