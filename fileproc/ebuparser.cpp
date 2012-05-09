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
    QDateTime dateLast = TypeConverter::stringToDate(root.attribute("dateLastModified"));
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
    QDateTime startDate = TypeConverter::stringToDate(element.attribute("startDate"));
    if(startDate.isValid())
        dateGroup->setStartDate(startDate);
    QDateTime endDate = TypeConverter::stringToDate(element.attribute("endDate"));
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
    QDateTime attributionDate = TypeConverter::stringToDate(element.attribute("attributiondate"));
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

SubjectType *EbuParser::parseSubjectType(const QDomElement &element)
{
    if (element.isNull()) {
         m_errorMsg = "SubjectType is null";
         return 0;
     }
     SubjectType *subject = new SubjectType();

     // Get attributes.
     parseTypeGroup(element, subject);
     QString note = element.attribute("note");
     if (!note.isEmpty())
         subject->setNote(note);

     // Get elements.
     QDomElement el = element.elementsByTagName("ebucore:subject").at(0).toElement();
     if (!el.isNull()) {
         ElementType *subjectEl = parseElementType(el);
         if (!subjectEl) {
             delete subject;
             return 0;
         }
         subject->setSubject(subjectEl);
     }

     el = element.elementsByTagName("ebucore:attributor").at(0).toElement();
     if (!el.isNull()) {
         EntityType *attributor = parseEntityType(el);
         if (!attributor) {
             delete subject;
             return 0;
         }
         subject->setAttributor(attributor);
     }

     el = element.elementsByTagName("ebucore:subjectCode").at(0).toElement();
     if (!el.isNull())
         subject->setSubjectCode(el.text());

     el = element.elementsByTagName("ebucore:subjectDefinition").at(0).toElement();
     if (!el.isNull())
         subject->setSubjectDefinition(el.text());

     return subject;
}

DateType *EbuParser::parseDateType(const QDomElement &element)
{
    if (element.isNull()) {
         m_errorMsg = "DateType is null";
         return 0;
     }

     DateType *date = new DateType();

     // Get elements.
     QDomNodeList el_list = element.elementsByTagName("ebucore:date");
     for (int i=0; i < el_list.size(); ++i) {
         ElementType *dateEl = parseElementType(el_list.at(i).toElement());
         if (!dateEl) {
             delete date;
             return 0;
         }
         date->date().append(dateEl);
     }

     QDomElement el = element.elementsByTagName("ebucore:created").at(0).toElement();
     if (!el.isNull()) {
         parseDateGroup(el, date->created());
     }

     el = element.elementsByTagName("ebucore:issued").at(0).toElement();
     if (!el.isNull()) {
         parseDateGroup(el, date->issued());
     }

     el = element.elementsByTagName("ebucore:modified").at(0).toElement();
     if (!el.isNull()) {
         parseDateGroup(el, date->modified());
     }

     el = element.elementsByTagName("ebucore:digitised").at(0).toElement();
     if (!el.isNull()) {
         parseDateGroup(el, date->digitised());
     }

     el_list = element.elementsByTagName("ebucore:alternative");
     for (int i=0; i < el_list.size(); ++i) {
         AlternativeType *alternative = parseAlternativeType(el_list.at(i).toElement());
         if (!alternative) {
             delete date;
             return 0;
         }
         date->alternative().append(alternative);
     }
     return 0;
}

AlternativeType *EbuParser::parseAlternativeType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "AlternativeType is null";
        return 0;
    }

    AlternativeType *alternative = new AlternativeType();

    // Get attributes.
    parseDateGroup(element, alternative);
    parseTypeGroup(element, alternative);

    return alternative;
}

TypeType *EbuParser::parseTypeType(const QDomElement &element)
{
    if (element.isNull()) {
         m_errorMsg = "TypeType is null";
         return 0;
     }

     TypeType *type = new TypeType();

     // Get attributes.
     QString note = element.attribute("note");
     if (!note.isEmpty())
         type->setNote(note);

     // Get elements.
     QDomNodeList el_list = element.elementsByTagName("ebucore:type");
     for (int i=0; i < el_list.size(); ++i) {
         ElementType *typeEl = parseElementType(el_list.at(i).toElement());
         if (!typeEl) {
             delete type;
             return 0;
         }
         type->type().append(typeEl);
     }

     el_list = element.elementsByTagName("ebucore:genre");
     for (int i=0; i < el_list.size(); ++i) {
         QDomElement el = el_list.at(i).toElement();
         if(el.isNull())
         {
             delete type;
             return 0;
         }
         type->genre().append(new TypeGroup());
         parseTypeGroup(el, type->genre().at(i));
     }

     el_list = element.elementsByTagName("ebucore:targetAudience");
     for (int i=0; i < el_list.size(); ++i) {
         QDomElement el = el_list.at(i).toElement();
         if(el.isNull())
         {
             delete type;
             return 0;
         }
         type->targetAudience().append(new TypeGroup());
         parseTypeGroup(el, type->targetAudience().at(i));
     }

     el_list = element.elementsByTagName("ebucore:objectType");
     for (int i=0; i < el_list.size(); ++i) {
         QDomElement el = el_list.at(i).toElement();
         if(el.isNull())
         {
             delete type;
             return 0;
         }
         type->objectType().append(new TypeGroup());
         parseTypeGroup(el, type->objectType().at(i));
     }

     return type;
}

FormatType *EbuParser::parseFormatType(const QDomElement &element)
{
    if (element.isNull()) {
         m_errorMsg = "FormatType is null";
         return 0;
     }

     FormatType *format = new FormatType();

     // Get attributes.
     QString formatId = element.attribute("formatId");
     if (!formatId.isEmpty())
         format->setFormatId(formatId);
     QString formatName = element.attribute("formatName");
     if (!formatName.isEmpty())
         format->setFormatName(formatName);
     QString formatDefinition = element.attribute("formatDefinition");
     if (!formatDefinition.isEmpty())
         format->setFormatDefinition(formatDefinition);

     // Get elements.
     QDomElement el = element.elementsByTagName("ebucore:format").at(0).toElement();
     if (!el.isNull()) {
         ElementType *formatEl = parseElementType(el);
         if (!formatEl) {
             delete format;
             return 0;
         }
         format->setFormat(formatEl);
     }

     bool ok;
     el = element.elementsByTagName("ebucore:regionDelimX").at(0).toElement();
     qint32 regionDelimX = el.text().toInt(&ok, 10);
     if(ok)
         format->setRegionDelimX(regionDelimX);
     el = element.elementsByTagName("ebucore:regionDelimY").at(0).toElement();
     qint32 regionDelimY = el.text().toInt(&ok, 10);
     if(ok)
         format->setRegionDelimY(regionDelimY);

     el = element.elementsByTagName("ebucore:width").at(0).toElement();
     if (!el.isNull()) {
         LengthType *width = parseLengthType(el);
         if (!width) {
             delete format;
             return 0;
         }
         format->setWidth(width);
     }
     el = element.elementsByTagName("ebucore:width").at(0).toElement();
     if (!el.isNull()) {
         LengthType *length = parseLengthType(el);
         if (!length) {
             delete format;
             return 0;
         }
         format->setWidth(length);
     }
     QDomNodeList el_list = element.elementsByTagName("ebucore:mediumType");
     for (int i=0; i < el_list.size(); ++i) {
         QDomElement el = el_list.at(i).toElement();
         if(el.isNull())
         {
             delete format;
             return 0;
         }
         format->medium().append(new TypeGroup());
         parseTypeGroup(el, format->medium().at(i));
     }
     el_list = element.elementsByTagName("ebucore:mimeType");
     for (int i=0; i < el_list.size(); ++i) {
         QDomElement el = el_list.at(i).toElement();
         if(el.isNull())
         {
             delete format;
             return 0;
         }
         format->mimeType().append(new TypeGroup());
         parseTypeGroup(el, format->mimeType().at(i));
     }
     el_list = element.elementsByTagName("ebucore:imageFormat");
     for (int i=0; i < el_list.size(); ++i) {
         ImageFormatType *imageFormat = parseImageFormatType(el_list.at(i).toElement());
         if (!imageFormat) {
             delete format;
             return 0;
         }
         format->imageFormat().append(imageFormat);
     }
     el_list = element.elementsByTagName("ebucore:videoFormat");
     for (int i=0; i < el_list.size(); ++i) {
         VideoFormatType *videoFormat = parseVideoFormatType(el_list.at(i).toElement());
         if (!videoFormat) {
             delete format;
             return 0;
         }
         format->videoFormat().append(videoFormat);
     }
     el_list = element.elementsByTagName("ebucore:audioFormat");
     for (int i=0; i < el_list.size(); ++i) {
         AudioFormatType *audioFormat = parseAudioFormatType(el_list.at(i).toElement());
         if (!audioFormat) {
             delete format;
             return 0;
         }
         format->audioFormat().append(audioFormat);
     }
     el_list = element.elementsByTagName("ebucore:dataFormat");
     for (int i=0; i < el_list.size(); ++i) {
         DataFormatType *dataFormat = parseDataFormatType(el_list.at(i).toElement());
         if (!dataFormat) {
             delete format;
             return 0;
         }
         format->dataFormat().append(dataFormat);
     }
     el = element.elementsByTagName("ebucore:containerFormat").at(0).toElement();
     for (int i=0; i < el_list.size(); ++i) {
         QDomElement el = el_list.at(i).toElement();
         if(el.isNull())
         {
             delete format;
             return 0;
         }
         format->containerFormat().append(new FormatGroup());
         parseFormatGroup(el, format->containerFormat().at(i));
     }
     el_list = element.elementsByTagName("ebucore:signingFormat");
     for (int i=0; i < el_list.size(); ++i) {
         SigningFormatType *signingFormat = parseSigningFormatType(el_list.at(i).toElement());
         if (!signingFormat) {
             delete format;
             return 0;
         }
         format->signingFormat().append(signingFormat);
     }
     return format;
}


LengthType *EbuParser::parseLengthType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "LengthType is null";
        return 0;
    }
    LengthType *length = new LengthType();

    // Get attributes.
    QString unit = element.attribute("unit");
    if (!unit.isEmpty())
        length->setUnit(unit);

    bool ok;
    qint32 value = element.text().toInt(&ok, 10);
    if(ok)
        length->setValue(value);

    return length;
}

SigningFormatType *EbuParser::parseSigningFormatType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "SigningFormatType is null";
        return 0;
    }
    SigningFormatType *signingFormat = new SigningFormatType();

    // Get attributes.
    parseFormatGroup(element, signingFormat);
    parseTypeGroup(element, signingFormat);

    QString trackId = element.attribute("trackId");
    if (!trackId.isEmpty())
        signingFormat->setTrackId(trackId);
    QString trackName = element.attribute("trackName");
    if (!trackName.isEmpty())
        signingFormat->setTrackName(trackName);
    QString language = element.attribute("language");
    if (!language.isEmpty())
        signingFormat->setLanguage(language);
    QString signingSourceUri = element.attribute("signingSourceUri");
    if (!signingSourceUri.isEmpty())
        signingFormat->setSigningSourceUri(signingSourceUri);
    QString signingFormatId = element.attribute("signingFormatId");
    if (!signingFormatId.isEmpty())
        signingFormat->setSigningFormatId(signingFormatId);
    QString signingFormatName = element.attribute("signingFormatName");
    if (!signingFormatName.isEmpty())
        signingFormat->setSigningFormatName(signingFormatName);
    QString signingFormatDefinition = element.attribute("signingFormatDefinition");
    if (!signingFormatDefinition.isEmpty())
        signingFormat->setSigningFormatDefinition(signingFormatDefinition);

    return signingFormat;
}


VideoFormatType *EbuParser::parseVideoFormatType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "VideoFormatType is null";
        return 0;
    }
    VideoFormatType *videoFormat = new VideoFormatType();

    // Get attributes.

    // Get element.

    return videoFormat;
}

ImageFormatType *EbuParser::parseImageFormatType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "ImageFormatType is null";
        return 0;
    }
    ImageFormatType *imageFormat = new ImageFormatType();

    // Get attributes.
    QString imageFormatId = element.attribute("imageFormatId");
    if (!imageFormatId.isEmpty())
        imageFormat->setImageFormatId(imageFormatId);
    QString imageFormatName = element.attribute("imageFormatName");
    if (!imageFormatName.isEmpty())
        imageFormat->setImageFormatName(imageFormatName);
    QString imageFormatDefinition = element.attribute("imageFormatDefinition");
    if (!imageFormatDefinition.isEmpty())
        imageFormat->setImageFormatDefinition(imageFormatDefinition);

    // Get elemens.
    bool ok;

    QDomElement el = element.elementsByTagName("ebucore:regionDelimX").at(0).toElement();
    qint32 regionDelimX = el.text().toInt(&ok, 10);
    if(ok)
        imageFormat->setRegionDelimX(regionDelimX);
    el = element.elementsByTagName("ebucore:regionDelimY").at(0).toElement();
    qint32 regionDelimY = el.text().toInt(&ok, 10);
    if(ok)
        imageFormat->setRegionDelimY(regionDelimY);

    el = element.elementsByTagName("ebucore:width").at(0).toElement();
    if (!el.isNull()) {
        LengthType *width = parseLengthType(el);
        if (!width) {
            delete imageFormat;
            return 0;
        }
        imageFormat->setWidth(width);
    }
    el = element.elementsByTagName("ebucore:width").at(0).toElement();
    if (!el.isNull()) {
        LengthType *length = parseLengthType(el);
        if (!length) {
            delete imageFormat;
            return 0;
        }
        imageFormat->setWidth(length);
    }

    el = element.elementsByTagName("ebucore:orientation").at(0).toElement();
    if (!el.isNull()) {
        // THIS DOES NOTHING!
        ImageFormatType::Orientation *orientation = new ImageFormatType::Orientation();
        imageFormat->setOrientation(*orientation);
    }
    QDomNodeList el_list = element.elementsByTagName("ebucore:imageEncoding");
    for (int i=0; i < el_list.size(); ++i) {
        QDomElement el = el_list.at(i).toElement();
        if(el.isNull())
        {
            delete imageFormat;
            return 0;
        }
        imageFormat->imageEncoding().append(new TypeGroup());
        parseTypeGroup(el, imageFormat->imageEncoding().at(i));
    }
    TechnicalAttributes *technicalAttributes = parseTechnicalAttributes(element);
    if(technicalAttributes)
    {
        imageFormat->setTechnicalAttributes(technicalAttributes);
    }


    return imageFormat;

    return 0;
}

TechnicalAttributes *EbuParser::parseTechnicalAttributes(const QDomElement &element)
{
    // There is no need to check for null element, since this call is made within another
    // parse function...
    TechnicalAttributes *ta = new TechnicalAttributes();

    // Get elements.
    QDomNodeList technicalAttributeStringList = element.elementsByTagName("ebucore:technicalAttributeString");
    for (int i=0; i < technicalAttributeStringList.size(); ++i) {
        QDomElement el = technicalAttributeStringList.item(i).toElement();
        String *technicalAttributeString = parseString(el);
        if (!technicalAttributeString) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeString().append(technicalAttributeString);
    }
    QDomNodeList technicalAttributeByteList = element.elementsByTagName("ebucore:technicalAttributeByte");
    for (int i=0; i < technicalAttributeByteList.size(); ++i) {
        QDomElement el = technicalAttributeByteList.item(i).toElement();
        Int8 *technicalAttributeByte = parseInt8(el);
        if (!technicalAttributeByte) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeByte().append(technicalAttributeByte);
    }
    QDomNodeList technicalAttributeShortList = element.elementsByTagName("ebucore:technicalAttributeShort");
    for (int i=0; i < technicalAttributeShortList.size(); ++i) {
        QDomElement el = technicalAttributeShortList.item(i).toElement();
        Int16 *technicalAttributeShort = parseInt16(el);
        if (!technicalAttributeShort) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeShort().append(technicalAttributeShort);
    }
    QDomNodeList technicalAttributeIntegerList = element.elementsByTagName("ebucore:technicalAttributeInteger");
    for (int i=0; i < technicalAttributeIntegerList.size(); ++i) {
        QDomElement el = technicalAttributeIntegerList.item(i).toElement();
        Int32 *technicalAttributeInteger = parseInt32(el);
        if (!technicalAttributeInteger) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeInteger().append(technicalAttributeInteger);
    }
    QDomNodeList technicalAttributeLongList = element.elementsByTagName("ebucore:technicalAttributeLong");
    for (int i=0; i < technicalAttributeLongList.size(); ++i) {
        QDomElement el = technicalAttributeLongList.item(i).toElement();
        Int64 *technicalAttributeLong = parseInt64(el);
        if (!technicalAttributeLong) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeLong().append(technicalAttributeLong);
    }
    QDomNodeList technicalAttributeUnsignedByteList = element.elementsByTagName("ebucore:technicalAttributeUnsignedByte");
    for (int i=0; i < technicalAttributeUnsignedByteList.size(); ++i) {
        QDomElement el = technicalAttributeUnsignedByteList.item(i).toElement();
        UInt8 *technicalAttributeUnsignedByte = parseUInt8(el);
        if (!technicalAttributeUnsignedByte) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeUnsignedByte().append(technicalAttributeUnsignedByte);
    }
    QDomNodeList technicalAttributeUnsignedShortList = element.elementsByTagName("ebucore:technicalAttributeUnsignedShort");
    for (int i=0; i < technicalAttributeUnsignedShortList.size(); ++i) {
        QDomElement el = technicalAttributeUnsignedShortList.item(i).toElement();
        UInt16 *technicalAttributeUnsignedShort = parseUInt16(el);
        if (!technicalAttributeUnsignedShort) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeUnsignedShort().append(technicalAttributeUnsignedShort);
    }
    QDomNodeList technicalAttributeUnsignedIntegerList = element.elementsByTagName("ebucore:technicalAttributeUnsignedInteger");
    for (int i=0; i < technicalAttributeUnsignedIntegerList.size(); ++i) {
        QDomElement el = technicalAttributeUnsignedIntegerList.item(i).toElement();
        UInt32 *technicalAttributeUnsignedInteger = parseUInt32(el);
        if (!technicalAttributeUnsignedInteger) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeUnsignedInteger().append(technicalAttributeUnsignedInteger);
    }
    QDomNodeList technicalAttributeUnsignedLongList = element.elementsByTagName("ebucore:technicalAttributeUnsignedLong");
    for (int i=0; i < technicalAttributeUnsignedLongList.size(); ++i) {
        QDomElement el = technicalAttributeUnsignedLongList.item(i).toElement();
        UInt64 *technicalAttributeUnsignedLong = parseUInt64(el);
        if (!technicalAttributeUnsignedLong) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeUnsignedLong().append(technicalAttributeUnsignedLong);
    }
    QDomNodeList technicalAttributeBooleanList = element.elementsByTagName("ebucore:technicalAttributeBoolean");
    for (int i=0; i < technicalAttributeBooleanList.size(); ++i) {
        QDomElement el = technicalAttributeBooleanList.item(i).toElement();
        Boolean *technicalAttributeBoolean = parseBoolean(el);
        if (!technicalAttributeBoolean) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeBoolean().append(technicalAttributeBoolean);
    }
    QDomNodeList technicalAttributeFloatList = element.elementsByTagName("ebucore:technicalAttributeFloat");
    for (int i=0; i < technicalAttributeFloatList.size(); ++i) {
        QDomElement el = technicalAttributeFloatList.item(i).toElement();
        Float *technicalAttributeFloat = parseFloat(el);
        if (!technicalAttributeFloat) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeFloat().append(technicalAttributeFloat);
    }
    QDomNodeList technicalAttributeRationalList = element.elementsByTagName("ebucore:technicalAttributeRational");
    for (int i=0; i < technicalAttributeRationalList.size(); ++i) {
        QDomElement el = technicalAttributeRationalList.item(i).toElement();
        TechnicalAttributeRationalType *technicalAttributeRational = parseTechnicalAttributeRationalType(el);
        if (!technicalAttributeRational) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeRational().append(technicalAttributeRational);
    }
    QDomNodeList technicalAttributeUriList = element.elementsByTagName("ebucore:technicalAttributeUri");
    for (int i=0; i < technicalAttributeUriList.size(); ++i) {
        QDomElement el = technicalAttributeUriList.item(i).toElement();
        TechnicalAttributeUriType *technicalAttributeUri = parseTechnicalAttributeUriType(el);
        if (!technicalAttributeUri) {
            delete ta;
            return 0;
        }
        ta->technicalAttributeUri().append(technicalAttributeUri);
    }


    return ta;
}

DataFormatType *EbuParser::parseDataFormatType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "DataeFormatType is null";
        return 0;
    }
    DataFormatType *dataFormat = new DataFormatType();

    // Get attributes.

    // Get element.

    return dataFormat;
}

AudioFormatType *EbuParser::parseAudioFormatType(const QDomElement &element)
{
    if (element.isNull()) {
        m_errorMsg = "AudioFormatType is null";
        return 0;
    }
    AudioFormatType *audioFormat = new AudioFormatType();

    // Get attributes.

    // Get element.

    return audioFormat;
}


LanguageType *EbuParser::parseLanguageType(const QDomElement &element)
{
    /// @todo Implement method.
    return 0;
}

HasTrackPartType *EbuParser::parseHasTrackPartType(const QDomElement &element)
{
    /// @todo Implement method.
    return 0;
}

CoverageType *EbuParser::parseCoverageType(const QDomElement &element)
{
    /// @todo Implement method.
    return 0;
}

RightsType *EbuParser::parseRightsType(const QDomElement &element)
{
    /// @todo Implement method.
    return 0;
}

PublicationHistoryType *EbuParser::parsePublicationHistoryType(const QDomElement &element)
{
    /// @todo Implement method.
    return 0;
}

RatingType *EbuParser::parseRatingType(const QDomElement &element)
{
    /// @todo Implement method.
    return 0;
}

PartType *EbuParser::parsePartType(const QDomElement &element)
{
    /// @todo Implement method.
    return 0;
}

DescriptionType *EbuParser::parseDescriptionType(const QDomElement &element)
{
    if (element.isNull()) {
         m_errorMsg = "DescriptionType is null";
         return 0;
     }
     DescriptionType *description = new DescriptionType();

     // Get attributes.
     parseTypeGroup(element, description);
     QString note = element.attribute("note");
     if (!note.isEmpty())
         description->setNote(note);

     // Get elements.
     QDomElement el = element.elementsByTagName("ebucore:description").at(0).toElement();
     if (!el.isNull()) {
         ElementType *descriptionEl = parseElementType(el);
         if (!descriptionEl) {
             delete description;
             return 0;
         }
         description->setDescription(descriptionEl);
     }

     return description;
}

String *EbuParser::parseString(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "String is null";
        return 0;
    }
    String *s = new String();
    parseTypeGroup(element, s);
    parseFormatGroup(element, s);
    QString value = element.attribute("value");
    if(!value.isEmpty())
        s->setValue(value);
    return s;
}
Int8 *EbuParser::parseInt8(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "Int8 is null";
        return 0;
    }
    bool ok;
    Int8 *int8 = new Int8();
    parseTypeGroup(element, int8);
    qint8 value = element.attribute("value").toInt(&ok,10);
    if(ok)
        int8->setValue(value);
    return int8;
}
Int16 *EbuParser::parseInt16(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "Int16 is null";
        return 0;
    }
    bool ok;
    Int16 *int16 = new Int16();
    parseTypeGroup(element, int16);
    short value = element.attribute("value").toShort(&ok, 10);
    if(ok)
        int16->setValue(value);
    return int16;
}
Int32 *EbuParser::parseInt32(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "Int32 is null";
        return 0;
    }
    bool ok;
    Int32 *int32 = new Int32();
    parseTypeGroup(element, int32);
    int value = element.attribute("value").toInt(&ok, 10);
    if(ok)
        int32->setValue(value);
    return int32;
}
Int64 *EbuParser::parseInt64(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "Int64 is null";
        return 0;
    }
    bool ok;
    Int64 *int64 = new Int64();
    parseTypeGroup(element, int64);
    long value = element.attribute("value").toLong(&ok, 10);
    if(ok)
        int64->setValue(value);
    return int64;
}
UInt8 *EbuParser::parseUInt8(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "UInt8 is null";
        return 0;
    }
}
UInt16 *EbuParser::parseUInt16(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "UInt16 is null";
        return 0;
    }
}
UInt32 *EbuParser::parseUInt32(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "UInt32 is null";
        return 0;
    }
}
UInt64 *EbuParser::parseUInt64(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "UInt64 is null";
        return 0;
    }
}
Boolean *EbuParser::parseBoolean(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "Boolean is null";
        return 0;
    }
}
Float *EbuParser::parseFloat(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "Float is null";
        return 0;
    }
}
TechnicalAttributeRationalType *EbuParser::parseTechnicalAttributeRationalType(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "TechnicalAttributeRationalType is null";
        return 0;
    }
}
TechnicalAttributeUriType *EbuParser::parseTechnicalAttributeUriType(const QDomElement &element)
{
    if(element.isNull())
    {
        m_errorMsg = "TechnicalAttributeUriType is null";
        return 0;
    }
}


