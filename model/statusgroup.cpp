#include "statusgroup.h"

StatusGroup::StatusGroup()
{
}

StatusGroup::StatusGroup(const StatusGroup &copy)
{
    m_statusLabel = copy.statusLabel();
    m_statusDefinition = copy.statusDefinition();
    m_statusLink = copy.statusLink();
}

void StatusGroup::setStatusLabel(const QString &statusLabel)
{
    m_statusLabel = statusLabel;
}

QString StatusGroup::statusLabel() const
{
    return m_statusLabel;
}

void StatusGroup::setStatusDefinition(const QString &statusDefinition)
{
    m_statusDefinition = statusDefinition;
}

QString StatusGroup::statusDefinition() const
{
    return m_statusDefinition;
}

void StatusGroup::setStatusLink(const QString &statusLink)
{
    m_statusLink = statusLink;
}

QString StatusGroup::statusLink() const
{
    return m_statusLink;
}

