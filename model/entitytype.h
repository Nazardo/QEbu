#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

#include <QList>
#include <QString>

#include "organisationdetailstype.h"
#include "contactdetailstype.h"

class OrganisationDetailsType;
class ContactDetailsType;

class RoleType : public TypeGroup { };

class EntityType
{
public:
    EntityType();
    // Attributes
    QString entityId() const;
    void setEntityId(const QString &entityId);
    // Elements
    QList<ContactDetailsType *> &contactDetails();
    OrganisationDetailsType *organisationDetails() const;
    void setOrganisationDetails(OrganisationDetailsType *organisationDetails);
    QList<RoleType *> &roles();
private:
    // Attributes
    QString m_entityId; // anyURI
    // Elements
    QList<ContactDetailsType*> m_contactDetails;
    OrganisationDetailsType *m_organisationDetails;
    QList<RoleType*> m_roles;
};



#endif // ENTITYTYPE_H
