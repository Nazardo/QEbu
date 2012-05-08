#include "ebuparser.h"
#include "../model/typeconverter.h"

#include <QtXml>

EbuParser::EbuParser()
{
    m_root = 0;
}

bool EbuParser::parseFromFile(QFile &file)
{
    QDomDocument doc("ebuCoreMain");
    if (!doc.setContent(&file, true, &m_errorMsg)) {
        return false;
    }

    /// @todo: Validation !!!

    /*
     * Check for root correctness
     */
    QDomElement root = doc.documentElement();
    if (root.tagName() != "ebucore:ebuCoreMain") {
        m_errorMsg = "Wrong root element";
        return false;
    }

    m_root = new EbuCoreMainType();

    // Get attributes.
    QDate dateLast = TypeConverter::stringToDate(root.attribute("dateLastModified"));
    if (dateLast.isValid())
        m_root->setDateLastModified(dateLast);
    QString documentId = root.attribute("documentId");
    if (!documentId.isEmpty())
        m_root->setDocumentId(documentId);
    QString lang = root.attribute("lang");
    if (!lang.isEmpty())
        m_root->setLang(lang);

    {
        QDomNodeList list = root.elementsByTagName("ebucore:coreMetadata");
        QDomElement element = list.item(0).toElement();
        CoreMetadataType *coreMetadata = parseCoreMetadataType(element);
        if (!coreMetadata)
            return false;
        m_root->setCoreMetadata(coreMetadata);
    }

    {
        QDomNodeList list = root.elementsByTagName("ebucore:metadataProvider");
        if (list.size() == 1) {
            QDomElement element = list.item(0).toElement();
            EntityType *entity = parseEntityType(element);
            if (!entity)
                return false;
            m_root->setMetadataProvider(entity);
        }
    }
    return true;
}

QString EbuParser::errorMsg()
{
    return m_errorMsg;
}

CoreMetadataType *EbuParser::parseCoreMetadataType(const QDomElement &element)
{
    /// @todo CoreMetadata parser
    return 0;
}

EntityType *EbuParser::parseEntityType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "EntityType is null";
        return 0;
    }
    EntityType *entity = new EntityType();
    // Get attribute.
    QString entityId = element.attribute("entityId");
    if (!entityId.isEmpty())
        entity->setEntityId(entityId);

    // contactDetails [0..*]
    QDomNodeList contactDetailsList = element.elementsByTagName("ebucore:contactDetails");
    for (int i=0; i < contactDetailsList.size(); ++i) {
        QDomElement el = contactDetailsList.item(i).toElement();
        ContactDetailsType *contactDetails = parseContactDetailsType(el);
        if (!contactDetails) {
            delete entity;
            return 0;
        }
        entity->contactDetails().append(contactDetails);
    }

    // organisationDetails [0..1]
    QDomElement el = element.elementsByTagName("ebucore:organisationDetails").at(0).toElement();
    if (!el.isNull()) {
        OrganisationDetailsType *organisationDetails = parseOrganisationDetailsType(el);
        if (!organisationDetails) {
            delete entity;
            return 0;
        }
        entity->setOrganisationDetails(organisationDetails);
    }

    // role [0..*]
    QDomNodeList roleList = element.elementsByTagName("ebucore:role");
    for (int i=0; i < roleList.size(); ++i) {
        TypeGroup *role = new TypeGroup();
        parseTypeGroup(roleList.at(i).toElement(), role);
        entity->roles().append(role);
    }

    return entity;
}

ContactDetailsType *EbuParser::parseContactDetailsType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "ContactDetailsType is null";
        return 0;
    }
    ContactDetailsType *contactDetails = new ContactDetailsType();
    // Get attribute.
    QString contactId = element.attribute("contactId");
    if (!contactId.isEmpty())
        contactDetails->setContactId(contactId);

    // Get elements.
    QDomElement el = element.elementsByTagName("ebucore:name").at(0).toElement();
    if (!el.isNull()) {
        QString name = el.text();
        Name n(name);
        contactDetails->setName(n);
    } else {
        el = element.elementsByTagName("ebucore:givenName").at(0).toElement();
        QString givenName = el.text();
        el = element.elementsByTagName("ebucore:familyName").at(0).toElement();
        QString familyName = el.text();
        Name n(givenName, familyName);
        contactDetails->setName(n);
    }

    el = element.elementsByTagName("ebucore:username").at(0).toElement();
    if (!el.isNull())
        contactDetails->setUsername(el.text());
    el = element.elementsByTagName("ebucore:occupation").at(0).toElement();
    if (!el.isNull())
        contactDetails->setOccupation(el.text());

    QDomNodeList el_list = element.elementsByTagName("ebucore:stageName");
    for (int i=0; i < el_list.size(); ++i) {
        el = el_list.at(i).toElement();
        if (!el.isNull())
            contactDetails->stageNames().append(el.text());
    }

    el_list = element.elementsByTagName("ebucore:relatedContacts");
    // Recursive madness ahead. Watch out! ;)
    for (int i=0; i < el_list.size(); ++i) {
        EntityType *relatedContact = parseEntityType(el_list.at(i).toElement());
        if (!relatedContact) {
            delete contactDetails;
            return 0;
        }
        contactDetails->relatedContacts().append(relatedContact);
    }

    el_list = element.elementsByTagName("ebucore:details");
    for (int i=0; i < el_list.size(); ++i) {
        DetailsType *detail = parseDetailsType(el_list.at(i).toElement());
        if (!detail) {
            delete contactDetails;
            return 0;
        }
        contactDetails->details().append(detail);
    }
    return contactDetails;
}

DetailsType *EbuParser::parseDetailsType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "DetailsType is null";
        return 0;
    }
    DetailsType *details = new DetailsType();

    // Get attributes.
    parseTypeGroup(element, details);

    // Code for the others elements
    QDomElement el = element.elementsByTagName("ebucore:emailAddress").at(0).toElement();
    if (!el.isNull())
        details->setEmailAddress(el.text());
    el = element.elementsByTagName("ebucore:webAddress").at(0).toElement();
    if (!el.isNull())
        details->setWebAddress(el.text());

    el = element.elementsByTagName("ebucore:telephoneNumber").at(0).toElement();
    if (!el.isNull())
        details->setTelephoneNumber(el.text());
    el = element.elementsByTagName("ebucore:mobileThelephoneNumber").at(0).toElement();
    if (!el.isNull())
        details->setMobileTelephoneNumber(el.text());

    el = element.elementsByTagName("abucore:address").at(0).toElement();
    if (!el.isNull()) {
        AddressType *address = parseAddressType(el);
        if (!address) {
            delete details;
            return 0;
        }
        details->setAddress(address);
    }
    return details;
}

AddressType *EbuParser::parseAddressType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "AddressType is null";
        return 0;
    }
    AddressType *address = new AddressType();

    QDomNodeList addressLine_list = element.elementsByTagName("ebucore:addressLine");
    for (int i=0; i < addressLine_list.size(); ++i) {
        QDomElement el = addressLine_list.at(i).toElement();
        if (!el.isNull())
            address->lines().append(el.text());
    }

    QDomElement el = element.elementsByTagName("ebucore:addressTownCity").at(0).toElement();
    if (!el.isNull())
        address->setTownCity(el.text());
    el = element.elementsByTagName("ebucore:addressCoutryState").at(0).toElement();
    if (!el.isNull())
        address->setCountyState(el.text());
    el = element.elementsByTagName("ebucore:addressDeliveryCode").at(0).toElement();
    if (!el.isNull())
        address->setDeliveryCode(el.text());
    el = element.elementsByTagName("ebucore:addressTownCity").at(0).toElement();
    if (!el.isNull())
        address->setTownCity(el.text());
    el = element.elementsByTagName("ebucore:country").at(0).toElement();
    if (!el.isNull()) {
        TypeGroup *country = new TypeGroup();
        parseTypeGroup(el, country);
        address->setCountry(country);
    }
    return address;
}

OrganisationDetailsType *EbuParser::parseOrganisationDetailsType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "OrganisationDetailsType is null";
        return 0;
    }
    OrganisationDetailsType *organisationDetails = new OrganisationDetailsType();

    // Get attribute.
    QString organisationId = element.attribute("organisationId");
    if (!organisationId.isEmpty())
        organisationDetails->setOrganisationId(organisationId);

    // Get elements.
    QDomElement el = element.elementsByTagName("ebucore:organisationName").at(0).toElement();
    if (!el.isNull()) {
        ElementType *organisationName = parseElementType(el);
        if (!organisationName) {
            delete organisationDetails;
            return 0;
        }
        organisationDetails->setOrganisationName(organisationName);
    }

    el = element.elementsByTagName("ebucore:organisationDepartment").at(0).toElement();
    if (!el.isNull()) {
        OrganisationDepartmentType *department = new OrganisationDepartmentType();
        QString lang = element.attribute("lang", "en");
        department->setLang(lang);
        QString value = element.text();
        if (!value.isEmpty())
            department->setValue(value);
        QString departmentId = element.attribute("departmentId");
        if (!departmentId.isNull())
            department->setDepartmentId(departmentId);
        organisationDetails->setOrganisationDepartment(department);
    }

    QDomNodeList el_list = element.elementsByTagName("ebucore:details");
    for (int i=0; i < el_list.size(); ++i) {
        DetailsType *detail = parseDetailsType(el_list.at(i).toElement());
        if (!detail) {
            delete organisationDetails;
            return 0;
        }
        organisationDetails->details().append(detail);
    }

    el_list = element.elementsByTagName("ebucore:contacts");
    for (int i=0; i < el_list.size(); ++i) {
        EntityType *contact = parseEntityType(el_list.at(i).toElement());
        if (!contact) {
            delete organisationDetails;
            return 0;
        }
        organisationDetails->contacts().append(contact);
    }

    return organisationDetails;
}

ElementType *EbuParser::parseElementType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "OrganisationDetailsType is null";
        return 0;
    }
    QString lang = element.attribute("lang", "en");
    QString value = element.text();
    return new ElementType(value, lang);
}

void EbuParser::parseTypeGroup(const QDomElement &element, TypeGroup* const typeGroup)
{
    QString typeLabel = element.attribute("typeLabel");
    if (!typeLabel.isEmpty())
        typeGroup->setTypeLabel(typeLabel);
    QString typeDefinition = element.attribute("typeDefinition");
    if (!typeDefinition.isEmpty())
        typeGroup->setTypeDefinition(typeDefinition);
    QString typeLink = element.attribute("typeLink");
    if (!typeLink.isEmpty())
        typeGroup->setTypeLink(typeLink);
}

