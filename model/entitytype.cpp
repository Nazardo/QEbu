#include "entitytype.h"

EntityType::EntityType()
{
    m_organisationDetails = 0;
}

EntityType::~EntityType()
{
    int s = m_contactDetails.size();
    for (int i=0; i < s; ++i) {
        delete (m_contactDetails.takeAt(0));
    }
    delete m_organisationDetails;
    s = m_roles.size();
    for (int i=0; i < s; ++i) {
        delete (m_roles.takeAt(0));
    }
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

QList<TypeGroup *> &EntityType::roles()
{
    return m_roles;
}
