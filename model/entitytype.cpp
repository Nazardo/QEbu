#include "entitytype.h"

EntityType::EntityType()
{
    m_organisationDetails = 0;
}

QString EntityType::entityId() const
{
    return m_entityId;
}

void EntityType::setEntityId(const QString &entityId)
{
    m_entityId = entityId;
}

QList<ContactDetailsType *> &EntityType::contactDetails()
{
    return m_contactDetails;
}

OrganisationDetailsType *EntityType::organisationDetails() const
{
    return m_organisationDetails;
}

void EntityType::setOrganisationDetails(OrganisationDetailsType *organisationDetails)
{
    m_organisationDetails = organisationDetails;
}

QList<RoleType *> &EntityType::roles()
{
    return m_roles;
}
