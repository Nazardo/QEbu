/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

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
