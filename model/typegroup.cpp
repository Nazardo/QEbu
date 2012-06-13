/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
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
    return QObject::tr("Unspecified type");
}

QString TypeGroup::typeLink() const
{
    return m_typeLink;
}
