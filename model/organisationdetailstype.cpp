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

#include "organisationdetailstype.h"
#include <QObject>

OrganisationDetailsType::OrganisationDetailsType()
{
    m_organisationName = 0;
    m_organisationDepartment = 0;
}

OrganisationDetailsType::~OrganisationDetailsType()
{
    delete m_organisationName;
    delete m_organisationDepartment;
    int s = m_details.size();
    for (int i=0; i < s; ++i) {
        delete (m_details.takeAt(0));
    }
    s = m_contacts.size();
    for (int i=0; i < s; ++i) {
        delete (m_contacts.takeAt(0));
    }
}

QString OrganisationDetailsType::organisationId() const
{
    return m_organisationId;
}

void OrganisationDetailsType::setOrganisationId(const QString &organisationId)
{
    m_organisationId = organisationId;
}

ElementType *OrganisationDetailsType::organisationName() const
{
    return m_organisationName;
}

void OrganisationDetailsType::setOrganisationName(ElementType *organisationName)
{
    if (organisationName != m_organisationName)
        delete m_organisationName;
    m_organisationName = organisationName;
}

OrganisationDepartmentType *OrganisationDetailsType::organisationDepartment() const
{
    return m_organisationDepartment;
}

void OrganisationDetailsType::setOrganisationDepartment(OrganisationDepartmentType *organisationDepartment)
{
    if (organisationDepartment != m_organisationDepartment)
        delete m_organisationDepartment;
    m_organisationDepartment = organisationDepartment;
}

QList<DetailsType*> &OrganisationDetailsType::details()
{
    return m_details;
}

QList<EntityType*> &OrganisationDetailsType::contacts()
{
    return m_contacts;
}

QString OrganisationDetailsType::toString() const
{
    if (m_organisationName)
        return m_organisationName->toString();
    if (!m_organisationId.isEmpty())
        return m_organisationId;
    return QObject::tr("Unnamed organisation");
}

OrganisationDepartmentType::OrganisationDepartmentType()
{
}

QString OrganisationDepartmentType::departmentId() const
{
    return m_departmentId;
}

void OrganisationDepartmentType::setDepartmentId(const QString &departmentId)
{
    m_departmentId = departmentId;
}

QString OrganisationDepartmentType::toString() const
{
    if (m_departmentId.isEmpty())
        return QObject::tr("Unnamed department");
    return m_departmentId;
}
