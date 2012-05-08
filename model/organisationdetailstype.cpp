#include "organisationdetailstype.h"

OrganisationDetailsType::OrganisationDetailsType()
{
    m_organisationName = 0;
    m_organisationDepartment = 0;
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
    m_organisationName = organisationName;
}

OrganisationDepartmentType *OrganisationDetailsType::organisationDepartment() const
{
    return m_organisationDepartment;
}

void OrganisationDetailsType::setOrganisationDepartment(OrganisationDepartmentType *organisationDepartment)
{
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
