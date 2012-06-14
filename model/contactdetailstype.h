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

#ifndef CONTACTDETAILSTYPE_H
#define CONTACTDETAILSTYPE_H

#include <QString>
#include "detailstype.h"
#include "entitytype.h"

class EntityType;

class Name
{
public:
    Name();
    Name(const QString &name);
    Name(const QString &givenName, const QString &familyName);
    bool isComplexName();
    QString getName() const;
    QString getGivenName() const;
    QString getFamilyName() const;
    QString toString() const;
private:
    QString m_name;
    QString m_givenName;
    QString m_familyName;
    bool m_complexName;
};

class ContactDetailsType
{
public:
    ContactDetailsType();
    ~ContactDetailsType();
    QString contactId() const;
    void setContactId(const QString &contactId);
    Name name() const;
    void setName(const Name &name);
    QString username() const;
    void setUsername(const QString &username);
    QString occupation() const;
    void setOccupation(const QString &occupation);
    QList<DetailsType*> &details();
    QList<QString> &stageNames();
    QList<EntityType*> &relatedContacts();
    QString toString() const;

private:
    QString m_contactId; // anyURI
    Name m_name; // (required)
    QString m_username;
    QString m_occupation;
    QList<DetailsType*> m_details;
    QList<QString> m_stageNames;
    QList<EntityType*> m_relatedContacts;
};

#endif // CONTACTDETAILSTYPE_H
