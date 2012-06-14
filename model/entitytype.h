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

#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

#include <QList>
#include <QString>

#include "organisationdetailstype.h"
#include "contactdetailstype.h"

class OrganisationDetailsType;
class ContactDetailsType;

class EntityType
{
public:
    EntityType();
    ~EntityType();
    // Attributes
    QString entityId() const;
    void setEntityId(const QString &entityId);
    // Elements
    QList<ContactDetailsType *> &contactDetails();
    OrganisationDetailsType *organisationDetails() const;
    void setOrganisationDetails(OrganisationDetailsType *organisationDetails);
    QList<TypeGroup *> &roles();
    QString toString() const;
private:
    // Attributes
    QString m_entityId; // anyURI
    // Elements
    QList<ContactDetailsType*> m_contactDetails;
    OrganisationDetailsType *m_organisationDetails;
    QList<TypeGroup*> m_roles;
};



#endif // ENTITYTYPE_H
