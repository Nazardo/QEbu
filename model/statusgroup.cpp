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

