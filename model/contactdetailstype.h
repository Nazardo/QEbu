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
