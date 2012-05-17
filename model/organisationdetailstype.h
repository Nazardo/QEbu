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
