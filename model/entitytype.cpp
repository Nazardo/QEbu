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

#include "entitytype.h"
#include <QObject>

EntityType::EntityType()
{
    m_organisationDetails = 0;
}

EntityType::~EntityType()
{
    int s = m_contactDetails.size();
    for (int i=0; i < s; ++i) {
        delete (m_contactDetails.takeAt(0));
    }
    delete m_organisationDetails;
    s = m_roles.size();
    for (int i=0; i < s; ++i) {
        delete (m_roles.takeAt(0));
    }
}

QString EntityType::entityId() const
{
    return m_entityId;
}

void EntityType::setEntityId(const QString &entityId)
{
    m_entityId = entityId;
}

QList<ContactDetailsType *> &EntityType::contactDetails()
{
    return m_contactDetails;
}

OrganisationDetailsType *EntityType::organisationDetails() const
{
    return m_organisationDetails;
}

void EntityType::setOrganisationDetails(OrganisationDetailsType *organisationDetails)
{
    if (organisationDetails != m_organisationDetails)
        delete m_organisationDetails;
    m_organisationDetails = organisationDetails;
}

QList<TypeGroup *> &EntityType::roles()
{
    return m_roles;
}

QString EntityType::toString() const
{
    if (m_entityId.isEmpty())
        return QObject::tr("Unspecified Entity");
    return m_entityId;
}
