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

#ifndef ORGANIZATIONDETAILSTYPE_H
#define ORGANIZATIONDETAILSTYPE_H

#include <QString>
#include <QList>

#include "entitytype.h"
#include "elementtype.h"
#include "detailstype.h"

class EntityType;
class OrganisationDepartmentType;

class OrganisationDetailsType
{
public:
    OrganisationDetailsType();
    ~OrganisationDetailsType();
    // Attributes
    QString organisationId() const;
    void setOrganisationId(const QString &organisationId);
    // Elements
    ElementType *organisationName() const;
    void setOrganisationName(ElementType *organisationName);
    OrganisationDepartmentType *organisationDepartment() const;
    void setOrganisationDepartment(OrganisationDepartmentType *organisationDepartment);
    QList<DetailsType*> &details();
    QList<EntityType*> &contacts();
    QString toString() const;
private:
    QString m_organisationId; // anyURI
    ElementType *m_organisationName;
    OrganisationDepartmentType *m_organisationDepartment;
    QList<DetailsType*> m_details;
    QList<EntityType*> m_contacts;
};

class OrganisationDepartmentType : public ElementType
{
public:
    OrganisationDepartmentType();
    QString departmentId() const;
    void setDepartmentId(const QString &departmentId);
    QString toString() const;
private:
    QString m_departmentId;
};

#endif // ORGANIZATIONDETAILSTYPE_H
