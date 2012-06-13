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

#include "contactdetailstype.h"

ContactDetailsType::ContactDetailsType()
{
}

ContactDetailsType::~ContactDetailsType()
{
    int s = m_details.size();
    for (int i=0; i < s; ++i) {
        delete (m_details.takeAt(0));
    }
    s = m_relatedContacts.size();
    for (int i=0; i < s; ++i) {
        delete (m_relatedContacts.takeAt(0));
    }
}

QString ContactDetailsType::contactId() const
{
    return m_contactId;
}

Name ContactDetailsType::name() const
{
    return m_name;
}

void ContactDetailsType::setName(const Name &name)
{
    m_name = name;
}

QString ContactDetailsType::username() const
{
    return m_username;
}

void ContactDetailsType::setUsername(const QString &username)
{
    m_username = username;
}

QString ContactDetailsType::occupation() const
{
    return m_occupation;
}

void ContactDetailsType::setOccupation(const QString &occupation)
{
    m_occupation = occupation;
}

void ContactDetailsType::setContactId(const QString &contactId)
{
    m_contactId = contactId;
}

QList<DetailsType *>& ContactDetailsType::details()
{
    return m_details;
}

QList<QString>& ContactDetailsType::stageNames()
{
    return m_stageNames;
}

QList<EntityType *>& ContactDetailsType::relatedContacts()
{
    return m_relatedContacts;
}

QString ContactDetailsType::toString() const
{
    return m_name.toString();
}

Name::Name()
{
}

Name::Name(const QString &name)
    : m_name(name), m_complexName(false)
{
}

Name::Name(const QString &givenName, const QString &familyName)
    : m_givenName(givenName), m_familyName(familyName), m_complexName(true)
{
}

bool Name::isComplexName()
{
    return m_complexName;
}

QString Name::getName() const
{
    return m_name;
}

QString Name::getGivenName() const
{
    return m_givenName;
}

QString Name::getFamilyName() const
{
    return m_familyName;
}

QString Name::toString() const
{
    if(m_complexName)
        return getFamilyName()+" "+getGivenName();
    else {
        return getName();
    }

}

