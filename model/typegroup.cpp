#include "typegroup.h"

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

QString TypeGroup::typeLink() const
{
    return m_typeLink;
}
