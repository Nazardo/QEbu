#ifndef ORGANIZATIONDETAILSTYPE_H
#define ORGANIZATIONDETAILSTYPE_H

#include <QString>
#include <QList>

#include "entitytype.h"
#include "elementtype.h"
#include "detailstype.h"

class EntityType;

class OrganisationDetailsType
{
public:
    OrganisationDetailsType();
    // Attributes
    QString organisationId() const;
    void setOrganisationId(const QString &organisationId);
    // Elements
    ElementType *organisationName() const;
    void setOrganisationName(ElementType *organisationName);
    ElementType *organisationDepartment() const;
    void setOrganisationDepartment(ElementType *organisationDepartment);
    QList<DetailsType*> &details();
    QList<EntityType*> &contacts();
private:
    QString m_organisationId; // anyURI
    ElementType *m_organisationName;
    ElementType *m_organisationDepartment;
    QList<DetailsType*> m_details;
    QList<EntityType*> m_contacts;
};

#endif // ORGANIZATIONDETAILSTYPE_H
