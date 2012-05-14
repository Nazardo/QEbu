#include "ebuserializer.h"
#include "../model/typeconverter.h"

#include <QtXml>


EbuSerializer::EbuSerializer(EbuCoreMainType *root)
{
    m_root = root;
}

bool EbuSerializer::serializeToFile(QFile &file)
{
    QDomDocument doc("ebuCoreMain");
    m_doc = doc;

    QDomElement rootNode = doc.createElement("ebuCoreMain");
    if(m_root->dateLastModified().isValid())
        rootNode.setAttribute("dateLastModified", TypeConverter::dateToString(m_root->dateLastModified()));
    if(!m_root->lang().isEmpty())
        rootNode.setAttribute("lang", m_root->lang());
    if(!m_root->documentId().isEmpty())
        rootNode.setAttribute("documentId", m_root->documentId());
    doc.appendChild(rootNode);

    QDomElement core = serializeCoreMetadata(m_root->coreMetadata());
    core.setTagName("coreMetadata");
    QDomElement provider = serializeEntity(m_root->metadataProvider());
    provider.setTagName("metadataProvider");

    rootNode.appendChild(core);
    rootNode.appendChild(provider);

    QTextStream out(&file);
    QDomNode xmlNode = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"ISO-8859-1\"");
    doc.insertBefore(xmlNode, doc.firstChild());
    doc.save(out, 4);

    return true;
}

QDomElement EbuSerializer::serializeCoreMetadata(CoreMetadataType *coreMetadata)
{
    QDomElement core = m_doc.createElement(" ");

    // title [0..*]
    QList<TitleType *> titles = coreMetadata->title();
    for (int i=0; i < titles.size(); ++i) {
        QDomElement e = serializeTitle(titles.at(i));
        e.setTagName("title");
        core.appendChild(e);
    }

    // alternativeTitle [0..*]
    QList<AlternativeTitleType *> aTitles = coreMetadata->alternativeTitle();
    for (int i=0; i < aTitles.size(); ++i) {
        QDomElement e = serializeAlternativeTitle(aTitles.at(i));
        e.setTagName("alternativeTitle");
        core.appendChild(e);
    }

    // creator [0..*]
    QList<EntityType *> creator = coreMetadata->creator();
    for (int i=0; i < creator.size(); ++i) {
        QDomElement e = serializeEntity(creator.at(i));
        e.setTagName("creator");
        core.appendChild(e);
    }

    // subject [0..*]
    QList<SubjectType *> subject = coreMetadata->subject();
    for (int i=0; i < subject.size(); ++i) {
        QDomElement e = serializeSubject(subject.at(i));
        e.setTagName("subject");
        core.appendChild(e);
    }

    // description [0..*]
    QList<DescriptionType *> description = coreMetadata->description();
    for (int i=0; i < description.size(); ++i) {
        QDomElement e = serializeDescription(description.at(i));
        e.setTagName("description");
        core.appendChild(e);
    }

    // publisher [0..*]
    QList<EntityType *> publisher = coreMetadata->publisher();
    for (int i=0; i < publisher.size(); ++i) {
        QDomElement e = serializeEntity(publisher.at(i));
        e.setTagName("publisher");
        core.appendChild(e);
    }

    // contributor [0..*]
    QList<EntityType *> contributor = coreMetadata->contributor();
    for (int i=0; i < contributor.size(); ++i) {
        QDomElement e = serializeEntity(contributor.at(i));
        e.setTagName("contributor");
        core.appendChild(e);
    }

    // date [0..*]
    QList<DateType *> date = coreMetadata->date();
    for (int i=0; i < date.size(); ++i) {
        QDomElement e = serializeDate(date.at(i));
        e.setTagName("date");
        core.appendChild(e);
    }

    // type [0..*]
    QList<TypeType *> type = coreMetadata->type();
    for (int i=0; i < type.size(); ++i) {
        QDomElement e = serializeType(type.at(i));
        e.setTagName("type");
        core.appendChild(e);
    }

    // format [0..*]
    QList<FormatType *> format = coreMetadata->format();
    for (int i=0; i < format.size(); ++i) {
        QDomElement e = serializeFormat(format.at(i));
        e.setTagName("format");
        core.appendChild(e);
    }

    // identifier [0..*]
    QList<IdentifierType *> identifier = coreMetadata->identifier();
    for (int i=0; i < identifier.size(); ++i) {
        QDomElement e = serializeIdentifier(identifier.at(i));
        e.setTagName("identifier");
        core.appendChild(e);
    }

    // source [0..*]
    QList<ElementType *> source = coreMetadata->source();
    for (int i=0; i < source.size(); ++i) {
        QDomElement e = serializeElement(source.at(i));
        e.setTagName("source");
        core.appendChild(e);
    }

    // language [0..*]
    QList<LanguageType *> language = coreMetadata->language();
    for (int i=0; i < language.size(); ++i) {
        QDomElement e = serializeLanguage(language.at(i));
        e.setTagName("language");
        core.appendChild(e);
    }

    // relation [0..*]
    QList<RelationType *> relation = coreMetadata->relation();
    for (int i=0; i < relation.size(); ++i) {
        QDomElement e = serializeRelation(relation.at(i));
        e.setTagName("relation");
        core.appendChild(e);
    }

    // isVersionOf [0..*]
    QList<RelationType *> isVersionOf = coreMetadata->isVersionOf();
    for (int i=0; i < isVersionOf.size(); ++i) {
        QDomElement e = serializeRelation(isVersionOf.at(i));
        e.setTagName("isVersionOf");
        core.appendChild(e);
    }

    // hasVersion [0..*]
    QList<RelationType *> hasVersion = coreMetadata->hasVersion();
    for (int i=0; i < hasVersion.size(); ++i) {
        QDomElement e = serializeRelation(hasVersion.at(i));
        e.setTagName("hasVersion");
        core.appendChild(e);
    }

    // isReplacedBy [0..*]
    QList<RelationType *> isReplacedBy = coreMetadata->isReplacedBy();
    for (int i=0; i < isReplacedBy.size(); ++i) {
        QDomElement e = serializeRelation(isReplacedBy.at(i));
        e.setTagName("isReplacedBy");
        core.appendChild(e);
    }

    // replaces [0..*]
    QList<RelationType *> replaces = coreMetadata->replaces();
    for (int i=0; i < replaces.size(); ++i) {
        QDomElement e = serializeRelation(replaces.at(i));
        e.setTagName("replaces");
        core.appendChild(e);
    }

    // isRequiredBy [0..*]
    QList<RelationType *> isRequiredBy = coreMetadata->isRequiredBy();
    for (int i=0; i < isRequiredBy.size(); ++i) {
        QDomElement e = serializeRelation(isRequiredBy.at(i));
        e.setTagName("isRequiredBy");
        core.appendChild(e);
    }

    // requires [0..*]
    QList<RelationType *> requires = coreMetadata->requires();
    for (int i=0; i < requires.size(); ++i) {
        QDomElement e = serializeRelation(requires.at(i));
        e.setTagName("requires");
        core.appendChild(e);
    }

    // isPartOf [0..*]
    QList<RelationType *> isPartOf = coreMetadata->isPartOf();
    for (int i=0; i < isPartOf.size(); ++i) {
        QDomElement e = serializeRelation(isPartOf.at(i));
        e.setTagName("isPartOf");
        core.appendChild(e);
    }

    // hasPart [0..*]
    QList<RelationType *> hasPart = coreMetadata->hasPart();
    for (int i=0; i < hasPart.size(); ++i) {
        QDomElement e = serializeRelation(hasPart.at(i));
        e.setTagName("hasPart");
        core.appendChild(e);
    }

    // isReferencedBy [0..*]
    QList<RelationType *> isReferencedBy = coreMetadata->isReferencedBy();
    for (int i=0; i < isReferencedBy.size(); ++i) {
        QDomElement e = serializeRelation(isReferencedBy.at(i));
        e.setTagName("isReferencedBy");
        core.appendChild(e);
    }

    // references [0..*]
    QList<RelationType *> references = coreMetadata->references();
    for (int i=0; i < references.size(); ++i) {
        QDomElement e = serializeRelation(references.at(i));
        e.setTagName("references");
        core.appendChild(e);
    }

    // isFormatOf [0..*]
    QList<RelationType *> isFormatOf = coreMetadata->isFormatOf();
    for (int i=0; i < isFormatOf.size(); ++i) {
        QDomElement e = serializeRelation(isFormatOf.at(i));
        e.setTagName("isFormatOf");
        core.appendChild(e);
    }

    // hasFormat [0..*]
    QList<RelationType *> hasFormat = coreMetadata->hasFormat();
    for (int i=0; i < hasFormat.size(); ++i) {
        QDomElement e = serializeRelation(hasFormat.at(i));
        e.setTagName("hasFormat");
        core.appendChild(e);
    }

    // isEpisodeOf [0..*]
    QList<RelationType *> isEpisodeOf = coreMetadata->isEpisodeOf();
    for (int i=0; i < isEpisodeOf.size(); ++i) {
        QDomElement e = serializeRelation(isEpisodeOf.at(i));
        e.setTagName("isEpisodeOf");
        core.appendChild(e);
    }

    // isMemberOf [0..*]
    QList<RelationType *> isMemberOf = coreMetadata->isMemberOf();
    for (int i=0; i < isMemberOf.size(); ++i) {
        QDomElement e = serializeRelation(isMemberOf.at(i));
        e.setTagName("isMemberOf");
        core.appendChild(e);
    }

    // hasTrackPart [0..*]
    QList<HasTrackPartType *> hasTrackPart = coreMetadata->hasTrackPart();
    for (int i=0; i < hasTrackPart.size(); ++i) {
        QDomElement e = serializeHasTrackPart(hasTrackPart.at(i));
        e.setTagName("hasTrackPart");
        core.appendChild(e);
    }

    // coverage [0..*]
    QList<CoverageType *> coverage = coreMetadata->coverage();
    for (int i=0; i < coverage.size(); ++i) {
        QDomElement e = serializeCoverage(coverage.at(i));
        e.setTagName("coverage");
        core.appendChild(e);
    }

    // rights [0..*]
    QList<RightsType *> rights = coreMetadata->rights();
    for (int i=0; i < rights.size(); ++i) {
        QDomElement e = serializeRights(rights.at(i));
        e.setTagName("rights");
        core.appendChild(e);
    }

    // version [0..1]
    if(coreMetadata->version())
    {
        QDomElement e = serializeElement(coreMetadata->version());
        e.setTagName("version");
        core.appendChild(e);
    }

    // publicationHistory [0..1]
    if(coreMetadata->publicationHistory())
    {
        QDomElement e = serializePublicationHistory(coreMetadata->publicationHistory());
        e.setTagName("publicationHistory");
        core.appendChild(e);
    }

    // rating [0..*]
    QList<RatingType *> ratings = coreMetadata->rating();
    for (int i=0; i < ratings.size(); ++i) {
        QDomElement e = serializeRating(ratings.at(i));
        e.setTagName("ratings");
        core.appendChild(e);
    }

    // part [0..*]
    QList<PartType *> part = coreMetadata->part();
    for (int i=0; i < part.size(); ++i) {
        QDomElement e = serializePart(part.at(i));
        e.setTagName("part");
        core.appendChild(e);
    }

    return core;
}

QDomElement EbuSerializer::serializeAlternative(AlternativeType *alternative)
{
    QDomElement a = m_doc.createElement(" ");

    serializeDateGroup(alternative, &a);
    serializeTypeGroup(alternative, &a);

    return a;
}

QDomElement EbuSerializer::serializeAudioTrack(AudioTrackType *track)
{
    QDomElement a = m_doc.createElement(" ");

    if(!track->trackLanguage().isEmpty())
        a.setAttribute("trackLanguage", track->trackLanguage());
    if(!track->trackId().isEmpty())
        a.setAttribute("trackId", track->trackId());
    if(!track->trackName().isEmpty())
        a.setAttribute("trackName", track->trackName());
    serializeTypeGroup(track, &a);

    return a;
}

QDomElement EbuSerializer::serializeDocumentFormat(DocumentFormatType *format)
{
    QDomElement f = m_doc.createElement(" ");

    serializeFormatGroup(format, &f);
    serializeTypeGroup(format, &f);
    if(!format->documentFormatId().isEmpty())
        f.setAttribute("documentFormatId",format->documentFormatId());
    if(!format->documentFormatName().isEmpty())
        f.setAttribute("documentFormatName",format->documentFormatName());
    if(!format->documentFormatDefinition().isEmpty())
        f.setAttribute("documentFormatDefinition",format->documentFormatDefinition());
    if(format->wordCount() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("wordCount");
        QDomText textNode = m_doc.createTextNode(QString::number(format->wordCount(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->regionDelimX() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimX");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimX(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->regionDelimY() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimY");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimY(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->width()) {
        QDomElement e = serializeLength(format->width());
        e.setTagName("width");
        f.appendChild(e);
    }
    if(format->height()) {
        QDomElement e = serializeLength(format->height());
        e.setTagName("height");
        f.appendChild(e);
    }
    serializeTechnicalAttributes(format->technicalAttributes(), &f);

    return f;
}

QDomElement EbuSerializer::serializeTime(TimeType *time)
{
    QDomElement t = m_doc.createElement(" ");

    if(!time->timecode().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(time->timecode());
        e.appendChild(textNode);
        e.setTagName("timecode");
        t.appendChild(e);
    }
    if(!time->normalPlayTime().isValid()) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(time->timecode());
        e.appendChild(textNode);
        e.setTagName("normalPlayTime");
        t.appendChild(e);
    }
    if(true) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("editUnitNumber");
        e.setAttribute("editRate", time->editRate());
        e.setAttribute("factorNumerator", time->factorNumerator());
        e.setAttribute("factorDenominator", time->factorDenominator());
        t.appendChild(e);
    }
    if(!time->time()) {
        QDomElement e = m_doc.createElement(" ");
        serializeFormatGroup(time->time(), &e);
        e.setTagName("time");
        t.appendChild(e);
    }
    return t;
}

QDomElement EbuSerializer::serializeTemporal(TemporalType *temporal)
{
    QDomElement t = m_doc.createElement(" ");

    serializeTypeGroup(temporal, &t);
    if(!temporal->note().isEmpty())
        t.setAttribute("note", temporal->note());
    if(!temporal->periodId().isEmpty())
        t.setAttribute("periodId", temporal->periodId());
    if(temporal->periodOfTime()) {
        QDomElement e = m_doc.createElement(" ");
        serializeDateGroup(temporal->periodOfTime(), &e);
        e.setTagName("periodOfTime");
        t.appendChild(e);
    }

    return t;
}

QDomElement EbuSerializer::serializeLocation(LocationType *location)
{
    QDomElement l = m_doc.createElement(" ");

    serializeTypeGroup(location, &l);
    if(!location->note().isEmpty())
        l.setAttribute("note", location->note());
    if(!location->locationId().isEmpty())
        l.setAttribute("locationId", location->locationId());
    if(!location->name().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("name");
        QDomText textNode = m_doc.createTextNode(location->name());
        e.appendChild(textNode);
        l.appendChild(e);
    }
    if(location->coordinates()) {
        QDomElement e = serializeCoordinates(location->coordinates());
        e.setTagName("coordinates");
        l.appendChild(e);
    }
    if(!location->code().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("code");
        QDomText textNode = m_doc.createTextNode(location->code());
        e.appendChild(textNode);
        l.appendChild(e);
    }
    return l;
}

QDomElement EbuSerializer::serializeCoordinates(CoordinatesType *coordinates)
{
    QDomElement c = m_doc.createElement(" ");
    serializeFormatGroup(coordinates, &c);
    if(true)
        c.setAttribute("posx", coordinates->posx());
    if(true)
        c.setAttribute("posy", coordinates->posy());

    return c;
}

QDomElement EbuSerializer::serializeEntity(EntityType *entity)
{
    QDomElement e = m_doc.createElement(" ");

    if(!entity->entityId().isEmpty())
        e.setAttribute("entityId", entity->entityId());

    QList<ContactDetailsType *> contacts = entity->contactDetails();
    for(int i=0; i<contacts.size(); ++i)
    {
        QDomElement c = serializeContactDetails(contacts.at(i));
        c.setTagName("contactDetails");
        e.appendChild(c);
    }

    OrganisationDetailsType * organisationDetails = entity->organisationDetails();
    if(organisationDetails) {
        QDomElement o = serializeOrganisationDetails(organisationDetails);
        o.setTagName("organisationDetails");
        e.appendChild(o);
    }

    QList<TypeGroup *> roles = entity->roles();
    for(int i=0; i<roles.size(); ++i)
    {
        QDomElement r = m_doc.createElement(" ");
        serializeTypeGroup(roles.at(i), &r);
        r.setTagName("role");
        e.appendChild(r);
    }

    return e;
}

QDomElement EbuSerializer::serializeContactDetails(ContactDetailsType *contactDetails)
{
    QDomElement c = m_doc.createElement(" ");
    if(!contactDetails->contactId().isEmpty())
        c.setAttribute("contactId", contactDetails->contactId());
    Name n = contactDetails->name();

    if(!n.isComplexName()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("name");
        QDomText textNode = m_doc.createTextNode(n.getName());
        e.appendChild(textNode);
        c.appendChild(e);
    } else {
        if(!n.getFamilyName().isEmpty()) {
            QDomElement e = m_doc.createElement(" ");
            e.setTagName("familyName");
            QDomText textNode = m_doc.createTextNode(n.getFamilyName());
            e.appendChild(textNode);
            c.appendChild(e);
        }
        if(!n.getGivenName().isEmpty()) {
            QDomElement e = m_doc.createElement(" ");
            e.setTagName("givenName");
            QDomText textNode = m_doc.createTextNode(n.getGivenName());
            e.appendChild(textNode);
            c.appendChild(e);
        }
    }

    if(!contactDetails->username().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("username");
        QDomText textNode = m_doc.createTextNode(contactDetails->username());
        e.appendChild(textNode);
        c.appendChild(e);
    }
    if(!contactDetails->occupation().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("occupation");
        QDomText textNode = m_doc.createTextNode(contactDetails->occupation());
        e.appendChild(textNode);
        c.appendChild(e);
    }
    QList<DetailsType *> details = contactDetails->details();
    for(int i=0; i<details.size(); ++i)
    {
        QDomElement d = serializeDetails(details.at(i));
        d.setTagName("details");
        c.appendChild(d);
    }
    QList<QString> stageNames = contactDetails->stageNames();
    for(int i=0; i<stageNames.size(); ++i)
    {
        QDomElement s = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(stageNames.at(i));
        s.appendChild(textNode);
        s.setTagName("stageName");
        c.appendChild(s);
    }
    QList<EntityType *> related = contactDetails->relatedContacts();
    for(int i=0; i<related.size(); ++i)
    {
        QDomElement r = serializeEntity(related.at(i));
        r.setTagName("relatedContacts");
        c.appendChild(r);
    }

    return c;
}

QDomElement EbuSerializer::serializeVideoTrack(VideoTrackType *track)
{
    QDomElement t = m_doc.createElement(" ");

    if(!track->trackId().isEmpty())
        t.setAttribute("trackId",track->trackId());
    if(!track->trackName().isEmpty())
        t.setAttribute("trackName",track->trackName());
    serializeTypeGroup(track, &t);

    return t;
}

QDomElement EbuSerializer::serializeAspectRatio(AspectRatioType *ratio)
{
    QDomElement r = m_doc.createElement(" ");

    serializeFormatGroup(ratio, &r);
    if(!ratio->note().isEmpty())
        r.setAttribute("note",ratio->note());

    return r;
}

QDomElement EbuSerializer::serializeCaptioningFormat(CaptioningFormatType *caption)
{
    QDomElement c = m_doc.createElement(" ");

    if(!caption->trackId().isEmpty())
        c.setAttribute("trackId",caption->trackId());
    if(!caption->trackLanguage().isEmpty())
        c.setAttribute("trackLanguage",caption->trackLanguage());
    if(!caption->trackName().isEmpty())
        c.setAttribute("trackName",caption->trackName());
    serializeTypeGroup(caption, &c);
    serializeFormatGroup(caption, &c);
    if(!caption->captioningSourceUri().isEmpty())
        c.setAttribute("captioningSourceUri",caption->captioningSourceUri());
    if(!caption->captioningFormatId().isEmpty())
        c.setAttribute("captioningFormatId",caption->captioningFormatId());
    if(!caption->captioningFormatName().isEmpty())
        c.setAttribute("captioningFormatName",caption->captioningFormatName());

    return c;
}

QDomElement EbuSerializer::serializeAncillarityDataFormat(AncillarityDataFormatType *ancillary)
{
    QDomElement a = m_doc.createElement(" ");

    if(!ancillary->ancillaryDataFormatId().isEmpty())
        a.setAttribute("ancillaryDataFormatId", ancillary->ancillaryDataFormatId());
    if(!ancillary->ancillaryDataFormatName().isEmpty())
        a.setAttribute("ancillaryDataFormatName", ancillary->ancillaryDataFormatName());
    if(true) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(QString::number(ancillary->DID(), 10));
        e.appendChild(textNode);
        e.setTagName("DID");
        a.appendChild(e);
    }
    if(true) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(QString::number(ancillary->SDID(), 10));
        e.appendChild(textNode);
        e.setTagName("SDID");
        a.appendChild(e);
    }
    QList<int> lines = ancillary->lineNumber();
    for(int i=0; i<lines.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(QString::number(lines.at(i), 10));
        e.appendChild(textNode);
        e.setTagName("lineNumber");
        a.appendChild(e);
    }
    if(true) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(QString::number(ancillary->wrappingType(), 10));
        e.appendChild(textNode);
        e.setTagName("wrappingType");
        a.appendChild(e);
    }
    return a;
}

QDomElement EbuSerializer::serializeOrganisationDetails(OrganisationDetailsType *organisationDetails)
{
    QDomElement o = m_doc.createElement(" ");

    if(!organisationDetails->organisationId().isEmpty()) {
        o.setAttribute("organisationId", organisationDetails->organisationId());
    }
    if(organisationDetails->organisationDepartment()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("organisationDepartment");
        e.setAttribute("lang", organisationDetails->organisationDepartment()->lang());
        e.setAttribute("departmentId", organisationDetails->organisationDepartment()->departmentId());
        QDomText textNode = m_doc.createTextNode(organisationDetails->organisationDepartment()->value());
        e.appendChild(textNode);
    }
    if(organisationDetails->organisationName()) {
        QDomElement e = serializeElement(organisationDetails->organisationName());
        e.setTagName("organisationName");
        o.appendChild(e);
    }
    QList<DetailsType *> details = organisationDetails->details();
    for(int i=0; i<details.size(); ++i)
    {
        QDomElement d = serializeDetails(details.at(i));
        d.setTagName("details");
        o.appendChild(d);
    }
    QList<EntityType *> contacts = organisationDetails->contacts();
    for(int i=0; i<contacts.size(); ++i)
    {
        QDomElement c = serializeEntity(contacts.at(i));
        c.setTagName("contacts");
        o.appendChild(c);
    }

    return o;
}

QDomElement EbuSerializer::serializeElement(ElementType *element)
{
    QDomElement e = m_doc.createElement(" ");

    e.setAttribute("lang", element->lang());
    QDomText textNode = m_doc.createTextNode(element->value());
    e.appendChild(textNode);

    return e;
}

QDomElement EbuSerializer::serializeRelation(RelationType *rel)
{
    QDomElement r = m_doc.createElement(" ");

    serializeTypeGroup(rel, &r);
    if(!rel->note().isEmpty())
        r.setAttribute("note", rel->note());
    r.setAttribute("runningOrderNumber", rel->runningOrderNumber());
    if(rel->relation()) {
        QDomElement e = serializeElement(rel->relation());
        e.setTagName("relation");
        r.appendChild(e);
    }
    if(rel->relationIdentifier()) {
        QDomElement e = serializeIdentifier(rel->relationIdentifier());
        e.setTagName("relationIdentifier");
        r.appendChild(e);
    }
    if(!rel->relationLink().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(rel->relationLink());
        e.appendChild(textNode);
        e.setTagName("relationLink");
        r.appendChild(e);
    }

    return r;

}

QDomElement EbuSerializer::serializeIdentifier(IdentifierType *identifier)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(identifier, &i);
    serializeFormatGroup(identifier, &i);
    if(!identifier->note().isEmpty())
        i.setAttribute("note", identifier->note());
    if(identifier->identifier()) {
        QDomElement e = serializeElement(identifier->identifier());
        e.setTagName("identifier");
        i.appendChild(e);
    }
    if(identifier->attributor()) {
        QDomElement e = serializeEntity(identifier->attributor());
        e.setTagName("attributor");
        i.appendChild(e);
    }

    return i;
}

QDomElement EbuSerializer::serializeSigningFormat(SigningFormatType *sign)
{
    QDomElement s = m_doc.createElement(" ");

    if(!sign->trackId().isEmpty())
        s.setAttribute("trackId", sign->trackId());
    if(!sign->trackName().isEmpty())
        s.setAttribute("trackName", sign->trackName());
    if(!sign->language().isEmpty())
        s.setAttribute("language", sign->language());
    serializeTypeGroup(sign, &s);
    serializeFormatGroup(sign, &s);
    if(!sign->signingSourceUri().isEmpty())
        s.setAttribute("signingSourceUri", sign->signingSourceUri());
    if(!sign->signingFormatId().isEmpty())
        s.setAttribute("signingFormatId", sign->signingFormatId());
    if(!sign->signingFormatName().isEmpty())
        s.setAttribute("signingFormatName", sign->signingFormatName());
    if(!sign->signingFormatDefinition().isEmpty())
        s.setAttribute("signingFormatDefinition", sign->signingFormatDefinition());

    return s;
}

QDomElement EbuSerializer::serializeTitle(TitleType *title)
{
    QDomElement t = m_doc.createElement(" ");

    if(title->attributionDate().isValid())
        t.setAttribute("attributionDate", TypeConverter::dateToString(title->attributionDate()));
    if(!title->note().isEmpty())
        t.setAttribute("note", title->note());
    if(title->title()) {
        QDomElement e = serializeElement(title->title());
        e.setTagName("title");
        t.appendChild(e);
    }

    return t;
}

QDomElement EbuSerializer::serializeAlternativeTitle(AlternativeTitleType *title)
{
    QDomElement a = m_doc.createElement(" ");

    serializeTypeGroup(title, &a);
    serializeStatusGroup(title, &a);
    serializeDateGroup(title, &a);
    if(!title->note().isEmpty())
        a.setAttribute("note", title->note());
    if(title->title()) {
        QDomElement e = serializeElement(title->title());
        e.setTagName("title");
        a.appendChild(e);
    }

    return a;
}

QDomElement EbuSerializer::serializeSubject(SubjectType *subject)
{
    QDomElement s = m_doc.createElement(" ");

    serializeTypeGroup(subject, &s);
    if(!subject->note().isEmpty())
        s.setAttribute("note", subject->note());
    if(subject->subject()) {
        QDomElement e = serializeElement(subject->subject());
        e.setTagName("subject");
        s.appendChild(e);
    }
    if(subject->attributor()) {
        QDomElement e = serializeEntity(subject->attributor());
        e.setTagName("attributor");
        s.appendChild(e);
    }
    if(!subject->subjectCode().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("subjectCode");
        QDomText textNode = m_doc.createTextNode(subject->subjectCode());
        e.appendChild(textNode);
        s.appendChild(e);
    }
    if(!subject->subjectDefinition().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("subjectDefinition");
        QDomText textNode = m_doc.createTextNode(subject->subjectDefinition());
        e.appendChild(textNode);
        s.appendChild(e);
    }

    return s;
}

QDomElement EbuSerializer::serializeDate(DateType *date)
{
    QDomElement d = m_doc.createElement(" ");

    QList<ElementType *> dates = date->date();
    for(int i=0; i<dates.size(); i++) {
        QDomElement e = serializeElement(dates.at(i));
        e.setTagName("date");
        d.appendChild(e);
    }
    if(date->created()) {
        QDomElement e = m_doc.createElement(" ");
        serializeDateGroup(date->created(), &e);
        e.setTagName("created");
        d.appendChild(e);
    }
    if(date->issued()) {
        QDomElement e = m_doc.createElement(" ");
        serializeDateGroup(date->issued(), &e);
        e.setTagName("issued");
        d.appendChild(e);
    }
    if(date->modified()) {
        QDomElement e = m_doc.createElement(" ");
        serializeDateGroup(date->modified(), &e);
        e.setTagName("modified");
        d.appendChild(e);
    }
    if(date->digitised()) {
        QDomElement e = m_doc.createElement(" ");
        serializeDateGroup(date->digitised(), &e);
        e.setTagName("digitised");
        d.appendChild(e);
    }
    QList<AlternativeType *> alternative = date->alternative();
    for(int i=0; i<alternative.size(); i++) {
        QDomElement e = serializeAlternative(alternative.at(i));
        e.setTagName("alternative");
        d.appendChild(e);
    }

    return d;
}

QDomElement EbuSerializer::serializeType(TypeType *type)
{
    QDomElement t = m_doc.createElement(" ");

    if(!type->note().isEmpty()) {
        t.setAttribute("note", type->note());
    }

    QList<ElementType *> types = type->type();
    for(int i=0; i<types.size(); ++i)
    {
        QDomElement e = serializeElement(types.at(i));
        e.setTagName("type");
        t.appendChild(e);
    }
    QList<TypeGroup *> genre = type->genre();
    for(int i=0; i<genre.size(); ++i)
    {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(genre.at(i), &e);
        e.setTagName("type");
        t.appendChild(e);
    }
    QList<TypeGroup *> objectType = type->objectType();
    for(int i=0; i<genre.size(); ++i)
    {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(objectType.at(i), &e);
        e.setTagName("objectType");
        t.appendChild(e);
    }
    QList<TypeGroup *> targetAudience = type->targetAudience();
    for(int i=0; i<targetAudience.size(); ++i)
    {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(targetAudience.at(i), &e);
        e.setTagName("targetAudience");
        t.appendChild(e);
    }

    return t;
}

QDomElement EbuSerializer::serializeFormat(FormatType *format)
{
    QDomElement f = m_doc.createElement(" ");

    if(!format->formatId().isEmpty())
        f.setAttribute("formatId", format->formatId());
    if(!format->formatName().isEmpty())
        f.setAttribute("formatName", format->formatName());
    if(!format->formatDefinition().isEmpty())
        f.setAttribute("formatDefinition", format->formatDefinition());
    if(format->format()) {
        QDomElement e = serializeElement(format->format());
        e.setTagName("format");
        f.appendChild(e);
    }
    if(format->regionDelimX() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimX");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimX(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->regionDelimY() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimY");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimY(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->width()) {
        QDomElement e = serializeLength(format->width());
        e.setTagName("width");
        f.appendChild(e);
    }
    if(format->height()) {
        QDomElement e = serializeLength(format->height());
        e.setTagName("height");
        f.appendChild(e);
    }
    QList<TypeGroup *> mediums = format->medium();
    for(int i=0; i<mediums.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(mediums.at(i), &e);
        e.setTagName("medium");
        f.appendChild(e);
    }
    QList<TypeGroup *> mimes = format->mimeType();
    for(int i=0; i<mimes.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(mimes.at(i), &e);
        e.setTagName("mimeType");
        f.appendChild(e);
    }
    QList<ImageFormatType *> imageFormats = format->imageFormat();
    for(int i=0; i<imageFormats.size(); ++i) {
        QDomElement e = serializeImageFormat(imageFormats.at(i));
        e.setTagName("imageFormat");
        f.appendChild(e);
    }
    QList<VideoFormatType *> videoFormats = format->videoFormat();
    for(int i=0; i<videoFormats.size(); ++i) {
        QDomElement e = serializeVideoFormat(videoFormats.at(i));
        e.setTagName("videoFormat");
        f.appendChild(e);
    }
    QList<AudioFormatType *> audioFormats = format->audioFormat();
    for(int i=0; i<audioFormats.size(); ++i) {
        QDomElement e = serializeAudioFormat(audioFormats.at(i));
        e.setTagName("audioFormat");
        f.appendChild(e);
    }
    QList<FormatGroup *> containers = format->containerFormat();
    for(int i=0; i<containers.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        serializeFormatGroup(containers.at(i), &e);
        e.setTagName("containerFormat");
        f.appendChild(e);
    }
    QList<DataFormatType *> dataFormats = format->dataFormat();
    for(int i=0; i<dataFormats.size(); ++i) {
        QDomElement e = serializeDataFormat(dataFormats.at(i));
        e.setTagName("dataFormat");
        f.appendChild(e);
    }
    QList<SigningFormatType *> signingFormats = format->signingFormat();
    for(int i=0; i<signingFormats.size(); ++i) {
        QDomElement e = serializeSigningFormat(signingFormats.at(i));
        e.setTagName("signingFormat");
        f.appendChild(e);
    }
    if(format->start()) {
        QDomElement e = serializeTime(format->start());
        e.setTagName("start");
        f.appendChild(e);
    }
    if(format->end()) {
        QDomElement e = serializeTime(format->end());
        e.setTagName("end");
        f.appendChild(e);
    }
    if(format->duration()) {
        QDomElement e = serializeTime(format->duration());
        e.setTagName("duration");
        f.appendChild(e);
    }
    if(format->fileSize() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("fileSize");
        QDomText textNode = m_doc.createTextNode(QString::number(format->fileSize(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(!format->fileName().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("fileName");
        QDomText textNode = m_doc.createTextNode(format->fileName());
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->locator()) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(format->locator(), &e);
        e.setTagName("locator");
        f.appendChild(e);
    }
    if(format->documentFormat()) {
        QDomElement e = serializeDocumentFormat(format->documentFormat());
        e.setTagName("documentFormat");
        f.appendChild(e);
    }
    if(format->technicalAttributes()) {
        serializeTechnicalAttributes(format->technicalAttributes(), &f);
    }
    if(format->dateCreated()) {
        QDomElement e = m_doc.createElement(" ");
        serializeDateGroup(format->dateCreated(), &e);
        e.setTagName("dataCreated");
        f.appendChild(e);
    }
    if(format->dateModified()) {
        QDomElement e = m_doc.createElement(" ");
        serializeDateGroup(format->dateModified(), &e);
        e.setTagName("dateModified");
        f.appendChild(e);
    }

    return f;
}

QDomElement EbuSerializer::serializeLanguage(LanguageType *lang)
{
    QDomElement l = m_doc.createElement(" ");

    serializeTypeGroup(lang, &l);
    if(!lang->note().isEmpty())
        l.setAttribute("note", lang->note());
    if(lang->language()) {
        QDomElement e = serializeElement(lang->language());
        e.setTagName("language");
        l.appendChild(e);
    }

    return l;
}

QDomElement EbuSerializer::serializeHasTrackPart(HasTrackPartType *part)
{
    QDomElement p = m_doc.createElement(" ");

    if(part->trackPartTitle()) {
        QDomElement e = serializeAlternativeTitle(part->trackPartTitle());
        e.setTagName("trackPartTitle");
        p.appendChild(e);
    }
    if(part->destinationStart()) {
        QDomElement e = serializeTime(part->destinationStart());
        e.setTagName("destinationStart");
        p.appendChild(e);
    }
    if(part->destinationEnd()) {
        QDomElement e = serializeTime(part->destinationEnd());
        e.setTagName("destinationEnd");
        p.appendChild(e);
    }
    if(part->sourceStart()) {
        QDomElement e = serializeTime(part->sourceStart());
        e.setTagName("sourceStart");
        p.appendChild(e);
    }
    if(part->sourceEnd()) {
        QDomElement e = serializeTime(part->sourceEnd());
        e.setTagName("sourceEnd");
        p.appendChild(e);
    }

    return p;
}

QDomElement EbuSerializer::serializeCoverage(CoverageType *coverage)
{
    QDomElement c = m_doc.createElement(" ");

    if(coverage->coverage()) {
        QDomElement e = serializeElement(coverage->coverage());
        e.setTagName("coverage");
        c.appendChild(e);
    }
    if(coverage->temporal()) {
        QDomElement e = serializeTemporal(coverage->temporal());
        e.setTagName("coverage");
        c.appendChild(e);
    }
    QList<LocationType *> locations = coverage->location();
    if(locations.size() > 0)
    {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("spatial");
        for(int i=0; i<locations.size(); ++i) {
            QDomElement l = serializeLocation(locations.at(i));
            l.setTagName("location");
            e.appendChild(l);
        }
        c.appendChild(e);
    }

    return c;
}

QDomElement EbuSerializer::serializeRights(RightsType *right)
{
    QDomElement r = m_doc.createElement(" ");

    serializeTypeGroup(right, &r);
    if(!right->note().isEmpty())
        r.setAttribute("note", right->note());
    QString idRefs = "";
    QList<FormatType *> refs = right->formats();
    for(int i=0; i<refs.size(); ++i) {
        QString r = refs.at(i)->formatId();
        idRefs += i ? " "+r : r;
    }
    if(!idRefs.isEmpty())
        r.setAttribute("formatIDRefs", idRefs);
    if(right->rights()) {
        QDomElement e = serializeElement(right->rights());
        e.setTagName("right");
        r.appendChild(e);
    }
    if(!right->rightsLink().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        QDomText textNode = m_doc.createTextNode(right->rightsLink());
        e.appendChild(textNode);
        e.setTagName("rightsLink");
        r.appendChild(e);
    }
    if(right->rightsHolder()) {
        QDomElement e = serializeEntity(right->rightsHolder());
        e.setTagName("rightsHolder");
        r.appendChild(e);
    }
    if(right->exploitationIssues()) {
        QDomElement e = serializeElement(right->exploitationIssues());
        e.setTagName("exploitationIssues");
        r.appendChild(e);
    }
    if(right->coverage()) {
        QDomElement e = serializeCoverage(right->coverage());
        e.setTagName("coverage");
        r.appendChild(e);
    }
    if(true) {
        QDomElement e = m_doc.createElement(" ");
        QString value = right->isRightsClearanceFlagSet() ? "true" : "false";
        QDomText textNode = m_doc.createTextNode(value);
        e.appendChild(textNode);
        e.setTagName("rightsClearanceFlag");
        r.appendChild(e);
    }
    QList<ElementType *> disclaimers = right->disclaimer();
    for(int i=0; i<disclaimers.size(); ++i) {
        QDomElement e = serializeElement(disclaimers.at(i));
        e.setTagName("disclaimer");
        r.appendChild(e);
    }
    QList<IdentifierType *> rightsIds = right->rightsID();
    for(int i=0; i<rightsIds.size(); ++i) {
        QDomElement e = serializeIdentifier(rightsIds.at(i));
        e.setTagName("rightsId");
        r.appendChild(e);
    }
    QList<ContactDetailsType *> contactDetails = right->contactDetails();
    for(int i=0; i<contactDetails.size(); ++i) {
        QDomElement e = serializeContactDetails(contactDetails.at(i));
        e.setTagName("contactDetails");
        r.appendChild(e);
    }

    return r;
}

QDomElement EbuSerializer::serializePublicationHistory(PublicationHistoryType *pub)
{
    QDomElement p = m_doc.createElement(" ");
    PublicationType *first = pub->firstPublication();
    if(first) {
        if(first->date().isValid()) {
            QDomElement e = m_doc.createElement(" ");
            e.setTagName("firstPublicationDate");
            QDomText textNode = m_doc.createTextNode(TypeConverter::dateToString(first->date()));
            e.appendChild(textNode);
            p.appendChild(e);
        }
        if(first->time().isValid()) {
            QDomElement e = m_doc.createElement(" ");
            e.setTagName("firstPublicationTime");
            QDomText textNode = m_doc.createTextNode(TypeConverter::timeToString(first->time()));
            e.appendChild(textNode);
            p.appendChild(e);
        }
        if(!first->channel()->formatId().isEmpty()) {
            QDomElement e = m_doc.createElement(" ");
            e.setTagName("firstPublicationChannel");
            QDomText textNode = m_doc.createTextNode(first->channel()->formatId());
            e.appendChild(textNode);
            p.appendChild(e);
        }
    }
    QList<PublicationType *> reps = pub->repetitions();
    for(int i=0; i<reps.size(); ++i) {
        PublicationType * rep = reps.at(i);
        if(rep) {
            if(rep->date().isValid()) {
                QDomElement e = m_doc.createElement(" ");
                e.setTagName("repeatDate");
                QDomText textNode = m_doc.createTextNode(TypeConverter::dateToString(rep->date()));
                e.appendChild(textNode);
                p.appendChild(e);
            }
            if(rep->time().isValid()) {
                QDomElement e = m_doc.createElement(" ");
                e.setTagName("repeatTime");
                QDomText textNode = m_doc.createTextNode(TypeConverter::timeToString(rep->time()));
                e.appendChild(textNode);
                p.appendChild(e);
            }
            if(!rep->channel()->formatId().isEmpty()) {
                QDomElement e = m_doc.createElement(" ");
                e.setTagName("repeatChannel");
                QDomText textNode = m_doc.createTextNode(rep->channel()->formatId());
                e.appendChild(textNode);
                p.appendChild(e);
            }
        }
    }

    return p;
}

QDomElement EbuSerializer::serializeRating(RatingType * rating)
{
    QDomElement r = m_doc.createElement(" ");

    serializeTypeGroup(rating, &r);
    serializeFormatGroup(rating, &r);
    if(!rating->ratingValue().isEmpty())
        r.setAttribute("ratingValue", rating->ratingValue());
    if(!rating->ratingScaleMaxValue().isEmpty())
        r.setAttribute("ratingScaleMaxValue", rating->ratingScaleMaxValue());
    if(!rating->ratingScaleMinValue().isEmpty())
        r.setAttribute("ratingScaleMinValue", rating->ratingScaleMinValue());
    if(rating->ratingProvider()) {
        QDomElement e = serializeEntity(rating->ratingProvider());
        e.setTagName("ratingProvider");
        r.appendChild(e);
    }

    return r;
}

QDomElement EbuSerializer::serializePart(PartType *part)
{
    QDomElement p = m_doc.createElement(" ");

    if(!part->partId().isEmpty())
        p.setAttribute("partId", part->partId());
    if(!part->partName().isEmpty())
        p.setAttribute("partName", part->partName());

    return p;
}

QDomElement EbuSerializer::serializeDescription(DescriptionType *description)
{
    QDomElement d = m_doc.createElement(" ");

    serializeTypeGroup(description, &d);
    if(!description->note().isEmpty())
        d.setAttribute("note", description->note());
    if(description->description()) {
        QDomElement e = serializeElement(description->description());
        e.setTagName("description");
        d.appendChild(e);
    }

    return d;
}

QDomElement EbuSerializer::serializeLength(LengthType *len)
{
    QDomElement l = m_doc.createElement(" ");

    if(!len->unit().isEmpty())
        l.setAttribute("unit", len->unit());
    if(len->value() >= 0) {
        QDomText textNode = m_doc.createTextNode(QString::number(len->value(), 10));
        l.appendChild(textNode);
    }

    return l;
}

QDomElement EbuSerializer::serializeAudioFormat(AudioFormatType *format)
{
    QDomElement f = m_doc.createElement(" ");

    if(!format->audioFormatId().isEmpty())
        f.setAttribute("audioFormatId",format->audioFormatId());
    if(!format->audioFormatName().isEmpty())
        f.setAttribute("audioFormatName",format->audioFormatName());
    if(!format->audioFormatDefinition().isEmpty())
        f.setAttribute("audioFormatDefinition",format->audioFormatDefinition());
    QList<TypeGroup *> encodings = format->audioEncoding();
    for(int i=0; i<encodings.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(encodings.at(i), &e);
        e.setTagName("audioEncoding");
        f.appendChild(e);
    }
    if(format->audioTrackConfiguration()) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(format->audioTrackConfiguration(), &e);
        e.setTagName("audioTrackConfiguration");
        f.appendChild(e);
    }
    QList<AudioTrackType *> tracks = format->audioTrack();
    for(int i=0; i<tracks.size(); ++i) {
        QDomElement e = serializeAudioTrack(tracks.at(i));
        e.setTagName("audioTrack");
        f.appendChild(e);
    }
    serializeTechnicalAttributes(format->technicalAttributes(), &f);

    return f;
}

QDomElement EbuSerializer::serializeDataFormat(DataFormatType *format)
{
    QDomElement f = m_doc.createElement(" ");

    if(!format->dataFormatId().isEmpty())
        f.setAttribute("dataFormatId",format->dataFormatId());
    if(!format->dataFormatName().isEmpty())
        f.setAttribute("dataFormatName",format->dataFormatName());
    if(!format->dataFormatDefinition().isEmpty())
        f.setAttribute("dataFormatDefinition",format->dataFormatDefinition());
    QList<CaptioningFormatType *> captions = format->captioningFormat();
    for(int i=0; i<captions.size(); ++i) {
        QDomElement e = serializeCaptioningFormat(captions.at(i));
        e.setTagName("captioningFormat");
        f.appendChild(e);
    }
    QList<AncillarityDataFormatType *> ancillary = format->ancillarityDataFormat();
    for(int i=0; i<ancillary.size(); ++i) {
        QDomElement e = serializeAncillarityDataFormat(ancillary.at(i));
        e.setTagName("ancillarityDataFormat");
        f.appendChild(e);
    }
    serializeTechnicalAttributes(format->technicalAttributes(), &f);

    return f;
}

QDomElement EbuSerializer::serializeImageFormat(ImageFormatType *format)
{
    QDomElement f = m_doc.createElement(" ");

    if(!format->imageFormatId().isEmpty())
        f.setAttribute("imageFormatId",format->imageFormatId());
    if(!format->imageFormatName().isEmpty())
        f.setAttribute("imageFormatName",format->imageFormatName());
    if(!format->imageFormatDefinition().isEmpty())
        f.setAttribute("imageFormatDefinition",format->imageFormatDefinition());
    if(format->regionDelimX() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimX");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimX(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->regionDelimY() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimY");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimY(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->width()) {
        QDomElement e = serializeLength(format->width());
        e.setTagName("width");
        f.appendChild(e);
    }
    if(format->height()) {
        QDomElement e = serializeLength(format->height());
        e.setTagName("height");
        f.appendChild(e);
    }
    if(format->orientation()) {
        QDomElement e = m_doc.createElement(" ");
        QString value = (format->orientation() == ImageFormatType::Landscape) ? "landscape" : "portrait";
        QDomText textNode = m_doc.createTextNode(value);
        e.appendChild(textNode);
        e.setTagName("orientation");
        f.appendChild(e);
    }
    QList<TypeGroup *> encodings = format->imageEncoding();
    for(int i=0; i<encodings.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(encodings.at(i), &e);
        e.setTagName("imageEncoding");
        f.appendChild(e);
    }
    serializeTechnicalAttributes(format->technicalAttributes(), &f);

    return f;
}

QDomElement EbuSerializer::serializeVideoFormat(VideoFormatType *format)
{
    QDomElement f = m_doc.createElement(" ");

    if(!format->videoFormatId().isEmpty())
        f.setAttribute("videoFormatId",format->videoFormatId());
    if(!format->videoFormatName().isEmpty())
        f.setAttribute("videoFormatName",format->videoFormatName());
    if(!format->videoFormatDefinition().isEmpty())
        f.setAttribute("videoFormatDefinition",format->videoFormatDefinition());
    if(format->regionDelimX() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimX");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimX(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->regionDelimY() >= 0) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("regionDelimY");
        QDomText textNode = m_doc.createTextNode(QString::number(format->regionDelimY(), 10));
        e.appendChild(textNode);
        f.appendChild(e);
    }
    if(format->width()) {
        QDomElement e = serializeLength(format->width());
        e.setTagName("width");
        f.appendChild(e);
    }
    if(format->height()) {
        QDomElement e = serializeLength(format->height());
        e.setTagName("height");
        f.appendChild(e);
    }
    if(format->aspectRatio()) {
        QDomElement e = serializeAspectRatio(format->aspectRatio());
        e.setTagName("aspectRatio");
        f.appendChild(e);
    }
    QList<TypeGroup *> encodings = format->videoEncoding();
    for(int i=0; i<encodings.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(encodings.at(i), &e);
        e.setTagName("videoEncoding");
        f.appendChild(e);
    }
    QList<VideoTrackType *> tracks = format->videoTrack();
    for(int i=0; i<tracks.size(); ++i) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(tracks.at(i), &e);
        e.setTagName("videoTrack");
        f.appendChild(e);
    }
    serializeTechnicalAttributes(format->technicalAttributes(), &f);

    return f;
}

QDomElement EbuSerializer::serializeString(String *string)
{
    QDomElement s = m_doc.createElement(" ");

    serializeTypeGroup(string, &s);
    serializeFormatGroup(string, &s);
    if(!string->value().isEmpty()) {
        QDomText textNode = m_doc.createTextNode(string->value());
        s.appendChild(textNode);
    }
    return s;
}

QDomElement EbuSerializer::serializeInt8(Int8 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);

    return i;
}

QDomElement EbuSerializer::serializeInt16(Int16 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeInt32(Int32 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeInt64(Int64 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeUInt8(UInt8 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeUInt16(UInt16 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeUInt32(UInt32 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeUInt64(UInt64 *integer)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(integer, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(integer->value(), 10));
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeBoolean(Boolean *boolean)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(boolean, &i);
    QString value = boolean->value() ? "true" : "false";
    QDomText textNode = m_doc.createTextNode(value);
    i.appendChild(textNode);
    return i;
}

QDomElement EbuSerializer::serializeFloat(Float *f)
{
    QDomElement i = m_doc.createElement(" ");

    serializeTypeGroup(f, &i);
    QDomText textNode = m_doc.createTextNode(QString::number(f->value(),'g',3));
    i.appendChild(textNode);

    return i;
}

QDomElement EbuSerializer::serializeTechnicalAttributeRational(TechnicalAttributeRationalType *ratio)
{
    QDomElement r = m_doc.createElement(" ");

    serializeTypeGroup(ratio, &r);
    r.setAttribute("factorNumerator", ratio->factorNumerator());
    r.setAttribute("factorDenominator", ratio->factorDenominator());
    QDomText textNode = m_doc.createTextNode(QString::number(ratio->value(), 10));
    r.appendChild(textNode);

    return r;
}

QDomElement EbuSerializer::serializeTechnicalAttributeUri(TechnicalAttributeUriType *uri)
{
    QDomElement u = m_doc.createElement(" ");

    serializeTypeGroup(uri, &u);
    if(!uri->value().isEmpty()) {
        QDomText textNode = m_doc.createTextNode(uri->value());
        u.appendChild(textNode);
    }

    return u;
}

QDomElement EbuSerializer::serializeDetails(DetailsType *details)
{
    QDomElement d = m_doc.createElement(" ");

    serializeTypeGroup(details, &d);
    if(!details->emailAddress().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("emailAddress");
        QDomText textNode = m_doc.createTextNode(details->emailAddress());
        e.appendChild(textNode);
        d.appendChild(e);
    }
    if(!details->webAddress().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("webAddress");
        QDomText textNode = m_doc.createTextNode(details->webAddress());
        e.appendChild(textNode);
        d.appendChild(e);
    }
    if(!details->telephoneNumber().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("telephoneNumber");
        QDomText textNode = m_doc.createTextNode(details->telephoneNumber());
        e.appendChild(textNode);
        d.appendChild(e);
    }
    if(!details->mobileTelephoneNumber().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("mobileTelephoneNumber");
        QDomText textNode = m_doc.createTextNode(details->mobileTelephoneNumber());
        e.appendChild(textNode);
        d.appendChild(e);
    }
    if(details->address()) {
        QDomElement e = serializeAddress(details->address());
        e.setTagName("address");
        d.appendChild(e);
    }

    return d;
}

QDomElement EbuSerializer::serializeAddress(AddressType *address)
{
    QDomElement a = m_doc.createElement(" ");

    QList<QString> lines = address->lines();
    for(int i=0; i<lines.size(); ++i)
    {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("addressLines");
        QDomText textNode = m_doc.createTextNode(lines.at(i));
        e.appendChild(textNode);
        a.appendChild(e);
    }
    if(!address->townCity().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("addressTownCity");
        QDomText textNode = m_doc.createTextNode(address->townCity());
        e.appendChild(textNode);
        a.appendChild(e);
    }
    if(!address->countyState().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("addressCountyState");
        QDomText textNode = m_doc.createTextNode(address->countyState());
        e.appendChild(textNode);
        a.appendChild(e);
    }
    if(!address->deliveryCode().isEmpty()) {
        QDomElement e = m_doc.createElement(" ");
        e.setTagName("addressDeliveryCode");
        QDomText textNode = m_doc.createTextNode(address->deliveryCode());
        e.appendChild(textNode);
        a.appendChild(e);
    }
    if(address->country()) {
        QDomElement e = m_doc.createElement(" ");
        serializeTypeGroup(address->country(), &e);
        e.setTagName("country");
        a.appendChild(e);
    }

    return a;
}

void EbuSerializer::serializeTechnicalAttributes(TechnicalAttributes *tech, QDomElement *t)
{
    if(t->isNull())
        t = new QDomElement;
    QList<String *> strings = tech->technicalAttributeString();
    for(int i=0; i<strings.length(); ++i) {
        QDomElement e = serializeString(strings.at(i));
        e.setTagName("technicalAttributeString");
        t->appendChild(e);
    }
    QList<Int8 *> bytes = tech->technicalAttributeByte();
    for(int i=0; i<bytes.length(); ++i) {
        QDomElement e = serializeInt8(bytes.at(i));
        e.setTagName("technicalAttributeByte");
        t->appendChild(e);
    }
    QList<Int16 *> shorts = tech->technicalAttributeShort();
    for(int i=0; i<shorts.length(); ++i) {
        QDomElement e = serializeInt16(shorts.at(i));
        e.setTagName("technicalAttributeShort");
        t->appendChild(e);
    }
    QList<Int32 *> ints = tech->technicalAttributeInteger();
    for(int i=0; i<ints.length(); ++i) {
        QDomElement e = serializeInt32(ints.at(i));
        e.setTagName("technicalAttributeInteger");
        t->appendChild(e);
    }
    QList<Int64 *> longs = tech->technicalAttributeLong();
    for(int i=0; i<longs.length(); ++i) {
        QDomElement e = serializeInt64(longs.at(i));
        e.setTagName("technicalAttributeLong");
        t->appendChild(e);
    }
    QList<UInt8 *> ubytes = tech->technicalAttributeUnsignedByte();
    for(int i=0; i<ubytes.length(); ++i) {
        QDomElement e = serializeUInt8(ubytes.at(i));
        e.setTagName("technicalAttributeUnsignedByte");
        t->appendChild(e);
    }
    QList<UInt16 *> ushorts = tech->technicalAttributeUnsignedShort();
    for(int i=0; i<ushorts.length(); ++i) {
        QDomElement e = serializeUInt16(ushorts.at(i));
        e.setTagName("technicalAttributeUnsignedShort");
        t->appendChild(e);
    }
    QList<UInt32 *> uints = tech->technicalAttributeUnsignedInteger();
    for(int i=0; i<uints.length(); ++i) {
        QDomElement e = serializeUInt32(uints.at(i));
        e.setTagName("technicalAttributeUnisgnedInteger");
        t->appendChild(e);
    }
    QList<UInt64 *> ulongs = tech->technicalAttributeUnsignedLong();
    for(int i=0; i<ulongs.length(); ++i) {
        QDomElement e = serializeUInt64(ulongs.at(i));
        e.setTagName("technicalAttributeUnsignedLong");
        t->appendChild(e);
    }
    QList<Boolean *> bools = tech->technicalAttributeBoolean();
    for(int i=0; i<bools.length(); ++i) {
        QDomElement e = serializeBoolean(bools.at(i));
        e.setTagName("technicalAttributeBoolean");
        t->appendChild(e);
    }
    QList<Float *> floats = tech->technicalAttributeFloat();
    for(int i=0; i<floats.length(); ++i) {
        QDomElement e = serializeFloat(floats.at(i));
        e.setTagName("technicalAttributeFloat");
        t->appendChild(e);
    }
    QList<TechnicalAttributeUriType *> uris = tech->technicalAttributeUri();
    for(int i=0; i<uris.length(); ++i) {
        QDomElement e = serializeTechnicalAttributeUri(uris.at(i));
        e.setTagName("technicalAttributeUri");
        t->appendChild(e);
    }
    QList<TechnicalAttributeRationalType *> rationals = tech->technicalAttributeRational();
    for(int i=0; i<rationals.length(); ++i) {
        QDomElement e = serializeTechnicalAttributeRational(rationals.at(i));
        e.setTagName("technicalAttributeRational");
        t->appendChild(e);
    }
}


void EbuSerializer::serializeTypeGroup(TypeGroup *typeGroup, QDomElement *t)
{
    if(t->isNull())
        t = new QDomElement();
    if(!typeGroup->typeDefinition().isEmpty())
        t->setAttribute("typeDefinition", typeGroup->typeDefinition());
    if(!typeGroup->typeLabel().isEmpty())
        t->setAttribute("typeLabel", typeGroup->typeLabel());
    if(!typeGroup->typeLink().isEmpty())
        t->setAttribute("typeLink", typeGroup->typeLink());
}

void EbuSerializer::serializeFormatGroup(FormatGroup *formatGroup, QDomElement *f)
{
    if(f->isNull())
        f = new QDomElement();
    if(!formatGroup->formatDefinition().isEmpty())
        f->setAttribute("formatDefinition", formatGroup->formatDefinition());
    if(!formatGroup->formatLabel().isEmpty())
        f->setAttribute("formatLabel", formatGroup->formatLabel());
    if(!formatGroup->formatLink().isEmpty())
        f->setAttribute("formatLink", formatGroup->formatLink());
}

void EbuSerializer::serializeStatusGroup(StatusGroup *statusGroup, QDomElement *s)
{
    if(s->isNull())
        s = new QDomElement();
    if(!statusGroup->statusDefinition().isEmpty())
        s->setAttribute("statusDefinition", statusGroup->statusDefinition());
    if(!statusGroup->statusLabel().isEmpty())
        s->setAttribute("statusLabel", statusGroup->statusLabel());
    if(!statusGroup->statusLink().isEmpty())
        s->setAttribute("statusLink", statusGroup->statusLink());
}

void EbuSerializer::serializeDateGroup(DateGroup *dateGroup, QDomElement *d)
{
    if(d->isNull())
        d = new QDomElement();
    if (!dateGroup->period().isNull())
        d->setAttribute("period", dateGroup->period());
    if (dateGroup->startYear())
        d->setAttribute("startYear", dateGroup->startYear());
    if (dateGroup->endYear())
        d->setAttribute("endYear", dateGroup->endYear());
    if (dateGroup->startDate().isValid())
        d->setAttribute("startDate", TypeConverter::dateToString(dateGroup->startDate()));
    if (dateGroup->endDate().isValid())
        d->setAttribute("endDate", TypeConverter::dateToString(dateGroup->endDate()));
    if (dateGroup->startTime().isValid())
        d->setAttribute("startTime", TypeConverter::timeToString(dateGroup->startTime()));
    if (dateGroup->endTime().isValid())
        d->setAttribute("endTime", TypeConverter::timeToString(dateGroup->endTime()));
}
