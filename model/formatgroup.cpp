#include "formatgroup.h"
#include <QObject>

FormatGroup::FormatGroup()
{
}

FormatGroup::FormatGroup(const FormatGroup &copy)
{
    m_formatLabel = copy.formatLabel();
    m_formatDefinition = copy.formatDefinition();
    m_formatLink = copy.formatLink();
}

QString FormatGroup::formatLabel() const
{
    return m_formatLabel;
}

void FormatGroup::setFormatLabel(const QString &formatLabel)
{
    m_formatLabel = formatLabel;
}

QString FormatGroup::formatDefinition() const
{
    return m_formatDefinition;
}

void FormatGroup::setFormatDefinition(const QString &formatDefinition)
{
    m_formatDefinition = formatDefinition;
}

QString FormatGroup::formatLink() const
{
    return m_formatLink;
}

void FormatGroup::setFormatLink(const QString &formatLink)
{
    m_formatLink = formatLink;
}

QString FormatGroup::toString() const
{
    if (!m_formatLabel.isEmpty())
        return m_formatLabel;
    if (!m_formatDefinition.isEmpty())
        return m_formatDefinition;
    if (!m_formatLink.isEmpty())
        return m_formatLink;
    return QObject::tr("Unspecified format");
}
