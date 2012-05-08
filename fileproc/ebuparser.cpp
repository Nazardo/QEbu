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
    if (element.isNull()) {
        m_errorMsg = "CoreMetadataType is null";
        return 0;
    }
    CoreMetadataType *coreMetadata = new CoreMetadataType();

    // title [0..*]
    QDomNodeList titleList = element.elementsByTagName("ebucore:title");
    for (int i=0; i < titleList.size(); ++i) {
        QDomElement el = titleList.item(i).toElement();
        TitleType *title = parseTitleType(el);
        if (!title) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->title().append(title);
    }

    // alternativeTitle [0..*]
    QDomNodeList alternativeTitleList = element.elementsByTagName("ebucore:alternativeTitle");
    for (int i=0; i < alternativeTitleList.size(); ++i) {
        QDomElement el = alternativeTitleList.item(i).toElement();
        AlternativeTitleType *alternativeTitle = parseAlternativeTitleType(el);
        if (!alternativeTitle) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->alternativeTitle().append(alternativeTitle);
    }

    // creator [0..*]
    QDomNodeList creatorList = element.elementsByTagName("ebucore:creator");
    for (int i=0; i < creatorList.size(); ++i) {
        QDomElement el = creatorList.item(i).toElement();
        EntityType *creator = parseEntityType(el);
        if (!creator) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->creator().append(creator);
    }

    // subject [0..*]
    QDomNodeList subjectList = element.elementsByTagName("ebucore:subject");
    for (int i=0; i < subjectList.size(); ++i) {
        QDomElement el = subjectList.item(i).toElement();
        SubjectType *subject = parseSubjectType(el);
        if (!subject) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->subject().append(subject);
    }

    // description [0..*]
    QDomNodeList descriptionList = element.elementsByTagName("ebucore:description");
    for (int i=0; i < descriptionList.size(); ++i) {
        QDomElement el = descriptionList.item(i).toElement();
        DescriptionType *description = parseDescriptionType(el);
        if (!description) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->description().append(description);
    }

    // publisher [0..*]
    QDomNodeList publisherList = element.elementsByTagName("ebucore:publisher");
    for (int i=0; i < publisherList.size(); ++i) {
        QDomElement el = publisherList.item(i).toElement();
        EntityType *publisher = parseEntityType(el);
        if (!publisher) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->publisher().append(publisher);
    }

    // contributor [0..*]
    QDomNodeList contributorList = element.elementsByTagName("ebucore:contributor");
    for (int i=0; i < contributorList.size(); ++i) {
        QDomElement el = contributorList.item(i).toElement();
        EntityType *contributor = parseEntityType(el);
        if (!contributor) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->contributor().append(contributor);
    }

    // date [0..*]
    QDomNodeList dateList = element.elementsByTagName("ebucore:date");
    for (int i=0; i < dateList.size(); ++i) {
        QDomElement el = dateList.item(i).toElement();
        DateType *date = parseDateType(el);
        if (!date) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->date().append(date);
    }

    // type [0..*]
    QDomNodeList typeList = element.elementsByTagName("ebucore:type");
    for (int i=0; i < typeList.size(); ++i) {
        QDomElement el = typeList.item(i).toElement();
        TypeType *type = parseTypeType(el);
        if (!type) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->type().append(type);
    }

    // format [0..*]
    QDomNodeList formatList = element.elementsByTagName("ebucore:format");
    for (int i=0; i < formatList.size(); ++i) {
        QDomElement el = formatList.item(i).toElement();
        FormatType *format = parseFormatType(el);
        if (!format) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->format().append(format);
    }

    // identifier [0..*]
    QDomNodeList identifierList = element.elementsByTagName("ebucore:identifier");
    for (int i=0; i < identifierList.size(); ++i) {
        QDomElement el = identifierList.item(i).toElement();
        IdentifierType *identifier = parseIdentifierType(el);
        if (!identifier) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->identifier().append(identifier);
    }

    // source [0..*]
    QDomNodeList sourceList = element.elementsByTagName("ebucore:source");
    for (int i=0; i < sourceList.size(); ++i) {
        QDomElement el = sourceList.item(i).toElement();
        ElementType *source = parseElementType(el);
        if (!source) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->source().append(source);
    }

    // language [0..*]
    QDomNodeList languageList = element.elementsByTagName("ebucore:language");
    for (int i=0; i < languageList.size(); ++i) {
        QDomElement el = languageList.item(i).toElement();
        LanguageType *language = parseLanguageType(el);
        if (!language) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->language().append(language);
    }

    // relation [0..*]
    QDomNodeList relationList = element.elementsByTagName("ebucore:relation");
    for (int i=0; i < relationList.size(); ++i) {
        QDomElement el = relationList.item(i).toElement();
        RelationType *relation = parseRelationType(el);
        if (!relation) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->relation().append(relation);
    }

    // isVersionOf [0..*]
    QDomNodeList isVersionOfList = element.elementsByTagName("ebucore:isVersionOf");
    for (int i=0; i < isVersionOfList.size(); ++i) {
        QDomElement el = isVersionOfList.item(i).toElement();
        RelationType *isVersionOf = parseRelationType(el);
        if (!isVersionOf) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isVersionOf().append(isVersionOf);
    }

    // hasVersion [0..*]
    QDomNodeList hasVersionList = element.elementsByTagName("ebucore:hasVersion");
    for (int i=0; i < hasVersionList.size(); ++i) {
        QDomElement el = hasVersionList.item(i).toElement();
        RelationType *hasVersion = parseRelationType(el);
        if (!hasVersion) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->hasVersion().append(hasVersion);
    }

    // isReplacedBy [0..*]
    QDomNodeList isReplacedByList = element.elementsByTagName("ebucore:isReplacedBy");
    for (int i=0; i < isReplacedByList.size(); ++i) {
        QDomElement el = isReplacedByList.item(i).toElement();
        RelationType *isReplacedBy = parseRelationType(el);
        if (!isReplacedBy) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isReplacedBy().append(isReplacedBy);
    }

    // replaces [0..*]
    QDomNodeList replacesList = element.elementsByTagName("ebucore:replaces");
    for (int i=0; i < replacesList.size(); ++i) {
        QDomElement el = replacesList.item(i).toElement();
        RelationType *replaces = parseRelationType(el);
        if (!replaces) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->replaces().append(replaces);
    }

    // isRequiredBy [0..*]
    QDomNodeList isRequiredByList = element.elementsByTagName("ebucore:isRequiredBy");
    for (int i=0; i < isRequiredByList.size(); ++i) {
        QDomElement el = isRequiredByList.item(i).toElement();
        RelationType *isRequiredBy = parseRelationType(el);
        if (!isRequiredBy) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isRequiredBy().append(isRequiredBy);
    }

    // requires [0..*]
    QDomNodeList requiresList = element.elementsByTagName("ebucore:requires");
    for (int i=0; i < requiresList.size(); ++i) {
        QDomElement el = requiresList.item(i).toElement();
        RelationType *requires = parseRelationType(el);
        if (!requires) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->requires().append(requires);
    }

    // isPartOf [0..*]
    QDomNodeList isPartOfList = element.elementsByTagName("ebucore:isPartOf");
    for (int i=0; i < isPartOfList.size(); ++i) {
        QDomElement el = isPartOfList.item(i).toElement();
        RelationType *isPartOf = parseRelationType(el);
        if (!isPartOf) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isPartOf().append(isPartOf);
    }

    // hasPart [0..*]
    QDomNodeList hasPartList = element.elementsByTagName("ebucore:hasPart");
    for (int i=0; i < hasPartList.size(); ++i) {
        QDomElement el = hasPartList.item(i).toElement();
        RelationType *hasPart = parseRelationType(el);
        if (!hasPart) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->hasPart().append(hasPart);
    }

    // hasTrackPart [0..*]
    QDomNodeList hasTrackPartList = element.elementsByTagName("ebucore:hasTrackPart");
    for (int i=0; i < hasTrackPartList.size(); ++i) {
        QDomElement el = hasTrackPartList.item(i).toElement();
        HasTrackPartType *hasTrackPart = parseHasTrackPartType(el);
        if (!hasTrackPart) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->hasTrackPart().append(hasTrackPart);
    }

    // isReferencedBy [0..*]
    QDomNodeList isReferencedByList = element.elementsByTagName("ebucore:isReferencedBy");
    for (int i=0; i < isReferencedByList.size(); ++i) {
        QDomElement el = isReferencedByList.item(i).toElement();
        RelationType *isReferencedBy = parseRelationType(el);
        if (!isReferencedBy) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isReferencedBy().append(isReferencedBy);
    }

    // references [0..*]
    QDomNodeList referencesList = element.elementsByTagName("ebucore:references");
    for (int i=0; i < referencesList.size(); ++i) {
        QDomElement el = referencesList.item(i).toElement();
        RelationType *references = parseRelationType(el);
        if (!references) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->references().append(references);
    }

    // isFormatOf [0..*]
    QDomNodeList isFormatOfList = element.elementsByTagName("ebucore:isFormatOf");
    for (int i=0; i < isFormatOfList.size(); ++i) {
        QDomElement el = isFormatOfList.item(i).toElement();
        RelationType *isFormatOf = parseRelationType(el);
        if (!isFormatOf) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isFormatOf().append(isFormatOf);
    }

    // hasFormat [0..*]
    QDomNodeList hasFormatList = element.elementsByTagName("ebucore:hasFormat");
    for (int i=0; i < hasFormatList.size(); ++i) {
        QDomElement el = hasFormatList.item(i).toElement();
        RelationType *hasFormat = parseRelationType(el);
        if (!hasFormat) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->hasFormat().append(hasFormat);
    }

    // isEpisodeOf [0..*]
    QDomNodeList isEpisodeOfList = element.elementsByTagName("ebucore:isEpisodeOf");
    for (int i=0; i < isEpisodeOfList.size(); ++i) {
        QDomElement el = isEpisodeOfList.item(i).toElement();
        RelationType *isEpisodeOf = parseRelationType(el);
        if (!isEpisodeOf) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isEpisodeOf().append(isEpisodeOf);
    }

    // isMemberOf [0..*]
    QDomNodeList isMemberOfList = element.elementsByTagName("ebucore:isMemberOf");
    for (int i=0; i < isMemberOfList.size(); ++i) {
        QDomElement el = isMemberOfList.item(i).toElement();
        RelationType *isMemberOf = parseRelationType(el);
        if (!isMemberOf) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->isMemberOf().append(isMemberOf);
    }

    // coverage [0..*]
    QDomNodeList coverageList = element.elementsByTagName("ebucore:coverage");
    for (int i=0; i < coverageList.size(); ++i) {
        QDomElement el = coverageList.item(i).toElement();
        CoverageType *coverage = parseCoverageType(el);
        if (!coverage) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->coverage().append(coverage);
    }

    // rights [0..*]
    QDomNodeList rightsList = element.elementsByTagName("ebucore:rights");
    for (int i=0; i < rightsList.size(); ++i) {
        QDomElement el = rightsList.item(i).toElement();
        RightsType *rights = parseRightsType(el);
        if (!rights) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->rights().append(rights);
    }

    // version [0..1]
    QDomElement el = element.elementsByTagName("ebucore:version").at(0).toElement();
    if (!el.isNull()) {
        ElementType *version = parseElementType(el);
        if (!version) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->setVersion(version);
    }

    // pubblicationHistory [0..1]
    el = element.elementsByTagName("ebucore:pubblicationHistory").at(0).toElement();
    if (!el.isNull()) {
        PublicationHistoryType *publicationHistory = parsePublicationHistoryType(el);
        if (!publicationHistory) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->setPubblicationHistory(publicationHistory);
    }

    // rating [0..*]
    QDomNodeList ratingList = element.elementsByTagName("ebucore:rating");
    for (int i=0; i < ratingList.size(); ++i) {
        QDomElement el = ratingList.item(i).toElement();
        RatingType *rating = parseRatingType(el);
        if (!rating) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->rating().append(rating);
    }

    // part [0..*]
    QDomNodeList partList = element.elementsByTagName("ebucore:part");
    for (int i=0; i < partList.size(); ++i) {
        QDomElement el = partList.item(i).toElement();
        PartType *part = parsePartType(el);
        if (!part) {
            delete coreMetadata;
            return 0;
        }
        coreMetadata->part().append(part);
    }

    return coreMetadata;
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
        m_errorMsg = "ElementType is null";
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

void EbuParser::parseFormatGroup(const QDomElement &element, FormatGroup* const formatGroup)
{
    QString formatLabel = element.attribute("formatLabel");
    if (!formatLabel.isEmpty())
        formatGroup->setFormatLabel(formatLabel);
    QString formatDefinition = element.attribute("formatDefinition");
    if (!formatDefinition.isEmpty())
        formatGroup->setFormatDefinition(formatDefinition);
    QString formatLink = element.attribute("formatLink");
    if (!formatLink.isEmpty())
        formatGroup->setFormatLink(formatLink);
}

void EbuParser::parseDateGroup(const QDomElement &element, DateGroup* const dateGroup)
{
    bool ok;
    QString period = element.attribute("period");
    if (!period.isEmpty())
        dateGroup->setPeriod(period);
    qint32 startYear = element.attribute("startYear").toInt(&ok, 10);
    if(ok)
        dateGroup->setStartYear(startYear);
    qint32 endYear = element.attribute("endYear").toInt(&ok, 10);
    if(ok)
        dateGroup->setEndYear(endYear);
    QDate startDate = TypeConverter::stringToDate(element.attribute("startDate"));
    if(startDate.isValid())
        dateGroup->setStartDate(startDate);
    QDate endDate = TypeConverter::stringToDate(element.attribute("endDate"));
    if(endDate.isValid())
        dateGroup->setEndDate(endDate);
    QTime startTime = TypeConverter::stringToTime(element.attribute("startTime"));
    if(startTime.isValid())
        dateGroup->setStartTime(startTime);
    QTime endTime = TypeConverter::stringToTime(element.attribute("endTime"));
    if(endTime.isValid())
        dateGroup->setEndTime(endTime);
}

void EbuParser::parseStatusGroup(const QDomElement &element, StatusGroup* const statusGroup)
{
    QString statusLabel = element.attribute("statusLabel");
    if (!statusLabel.isEmpty())
        statusGroup->setStatusLabel(statusLabel);
    QString statusDefinition = element.attribute("statusDefinition");
    if (!statusDefinition.isEmpty())
        statusGroup->setStatusDefinition(statusDefinition);
    QString statusLink = element.attribute("statusLink");
    if (!statusLink.isEmpty())
        statusGroup->setStatusLink(statusLink);
}

RelationType *EbuParser::parseRelationType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "RelationType is null";
        return 0;
    }

    RelationType *relation = new RelationType();

    // Get attributes.
    parseTypeGroup(element, relation);

    QString note = element.attribute("note");
    if (!note.isEmpty())
        relation->setNote(note);

    bool ok;
    int runningOrderNumber = element.attribute("runningOrderNumber").toInt(&ok, 10);
    if (ok)
        relation->setRunningOrderNumber(runningOrderNumber);

    // Get elements.
    QDomElement el = element.elementsByTagName("ebucore:relation").at(0).toElement();
    if (!el.isNull()) {
        ElementType *relationEl = parseElementType(el);
        if (!relationEl) {
            delete relation;
            return 0;
        }
        relation->setRelation(relationEl);
    }

    el = element.elementsByTagName("ebucore:relationLink").at(0).toElement();
    QString relationLink = el.text();
    if (!relationLink.isEmpty())
        relation->setRelationLink(relationLink);

    el = element.elementsByTagName("ebucore:relationIdentifier").at(0).toElement();
    if (!el.isNull()) {
        IdentifierType *relationIdentifier = parseIdentifierType(el);
        if (!relationIdentifier) {
            delete relation;
            return 0;
        }
        relation->setRelationIdentifier(relationIdentifier);
    }

    return relation;
}

IdentifierType *EbuParser::parseIdentifierType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "IdentifierType is null";
        return 0;
    }

    IdentifierType *identifier = new IdentifierType();

    // Get attributes.
    parseTypeGroup(element, identifier);
    parseFormatGroup(element, identifier);
    QString note = element.attribute("note");
    if (!note.isEmpty())
        identifier->setNote(note);

    // Get elements.
    QDomElement el = element.elementsByTagName("ebucore:identifier").at(0).toElement();
    if (!el.isNull()) {
        ElementType *identifierEl = parseElementType(el);
        if (!identifierEl) {
            delete identifier;
            return 0;
        }
        identifier->setIdentifier(identifierEl);
    }

    el = element.elementsByTagName("ebucore:attributor").at(0).toElement();
    if (!el.isNull()) {
        EntityType *attributor = parseEntityType(el);
        if (!attributor) {
            delete identifier;
            return 0;
        }
        identifier->setAttributor(attributor);
    }

    return identifier;
}

TitleType *EbuParser::parseTitleType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "IdentifierType is null";
        return 0;
    }
    TitleType *title = new TitleType();

    // Get attributes.
    QString note = element.attribute("note");
    if (!note.isEmpty())
        title->setNote(note);
    QDate attributionDate = TypeConverter::stringToDate(element.attribute("attributiondate"));
    if (attributionDate.isValid())
        title->setAttributionDate(attributionDate);

    // Get element.
    QDomElement el = element.elementsByTagName("ebucore:title").at(0).toElement();
    if (!el.isNull()) {
        ElementType *titleEl = parseElementType(el);
        if (!titleEl) {
            delete title;
            return 0;
        }
        title->setTitle(titleEl);
    }
    return title;
}

AlternativeTitleType *EbuParser::parseAlternativeTitleType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "IdentifierType is null";
        return 0;
    }
    AlternativeTitleType *alternativeTitle = new AlternativeTitleType();

    // Get attributes.
    parseTypeGroup(element, alternativeTitle);
    parseStatusGroup(element, alternativeTitle);
    parseDateGroup(element, alternativeTitle);
    QString note = element.attribute("note");
    if (!note.isEmpty())
        alternativeTitle->setNote(note);

    // Get element.
    QDomElement el = element.elementsByTagName("ebucore:title").at(0).toElement();
    if (!el.isNull()) {
        ElementType *title = parseElementType(el);
        if (!title) {
            delete alternativeTitle;
            return 0;
        }
        alternativeTitle->setTitle(title);
    }
    return alternativeTitle;
}

