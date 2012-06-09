#include "coremetadatatype.h"
#include <QObject>
#include <QStringList>

CoreMetadataType::CoreMetadataType()
{
    m_version = 0;
    m_publicationHistory = 0;
}

CoreMetadataType::~CoreMetadataType()
{
    int s = m_title.size();
    for (int i=0; i < s; ++i) {
        delete (m_title.takeAt(0));
    }
    s = m_alternativeTitle.size();
    for (int i=0; i < s; ++i) {
        delete (m_alternativeTitle.takeAt(0));
    }
    s = m_creator.size();
    for (int i=0; i < s; ++i) {
        delete (m_creator.takeAt(0));
    }
    s = m_subject.size();
    for (int i=0; i < s; ++i) {
        delete (m_subject.takeAt(0));
    }
    s = m_description.size();
    for (int i=0; i < s; ++i) {
        delete (m_description.takeAt(0));
    }
    s = m_publisher.size();
    for (int i=0; i < s; ++i) {
        delete (m_publisher.takeAt(0));
    }
    s = m_contributor.size();
    for (int i=0; i < s; ++i) {
        delete (m_contributor.takeAt(0));
    }
    s = m_date.size();
    for (int i=0; i < s; ++i) {
        delete (m_date.takeAt(0));
    }
    s = m_type.size();
    for (int i=0; i < s; ++i) {
        delete (m_type.takeAt(0));
    }
    s = m_format.size();
    for (int i=0; i < s; ++i) {
        delete (m_format.takeAt(0));
    }
    s = m_identifier.size();
    for (int i=0; i < s; ++i) {
        delete (m_identifier.takeAt(0));
    }
    s = m_source.size();
    for (int i=0; i < s; ++i) {
        delete (m_source.takeAt(0));
    }
    s = m_language.size();
    for (int i=0; i < s; ++i) {
        delete (m_language.takeAt(0));
    }
    s = m_relation.size();
    for (int i=0; i < s; ++i) {
        delete (m_relation.takeAt(0));
    }
    s = m_isVersionOf.size();
    for (int i=0; i < s; ++i) {
        delete (m_isVersionOf.takeAt(0));
    }
    s = m_hasVersion.size();
    for (int i=0; i < s; ++i) {
        delete (m_hasVersion.takeAt(0));
    }
    s = m_isReplacedBy.size();
    for (int i=0; i < s; ++i) {
        delete (m_isReplacedBy.takeAt(0));
    }
    s = m_replaces.size();
    for (int i=0; i < s; ++i) {
        delete (m_replaces.takeAt(0));
    }
    s = m_isRequiredBy.size();
    for (int i=0; i < s; ++i) {
        delete (m_isRequiredBy.takeAt(0));
    }
    s = m_requires.size();
    for (int i=0; i < s; ++i) {
        delete (m_requires.takeAt(0));
    }
    s = m_isPartOf.size();
    for (int i=0; i < s; ++i) {
        delete (m_isPartOf.takeAt(0));
    }
    s = m_hasPart.size();
    for (int i=0; i < s; ++i) {
        delete (m_hasPart.takeAt(0));
    }
    s = m_hasTrackPart.size();
    for (int i=0; i < s; ++i) {
        delete (m_hasTrackPart.takeAt(0));
    }
    s = m_isReferencedBy.size();
    for (int i=0; i < s; ++i) {
        delete (m_isReferencedBy.takeAt(0));
    }
    s = m_references.size();
    for (int i=0; i < s; ++i) {
        delete (m_references.takeAt(0));
    }
    s = m_isFormatOf.size();
    for (int i=0; i < s; ++i) {
        delete (m_isFormatOf.takeAt(0));
    }
    s = m_hasFormat.size();
    for (int i=0; i < s; ++i) {
        delete (m_hasFormat.takeAt(0));
    }
    s = m_isEpisodeOf.size();
    for (int i=0; i < s; ++i) {
        delete (m_isEpisodeOf.takeAt(0));
    }
    s = m_isMemberOf.size();
    for (int i=0; i < s; ++i) {
        delete (m_isMemberOf.takeAt(0));
    }
    s = m_coverage.size();
    for (int i=0; i < s; ++i) {
        delete (m_coverage.takeAt(0));
    }
    s = m_rights.size();
    for (int i=0; i < s; ++i) {
        delete (m_rights.takeAt(0));
    }
    delete m_version;
    delete m_publicationHistory;
    s = m_rating.size();
    for (int i=0; i < s; ++i) {
        delete (m_rating.takeAt(0));
    }
    s = m_part.size();
    for (int i=0; i < s; ++i) {
        delete (m_part.takeAt(0));
    }
}

TitleType::TitleType()
{
    m_title = 0;
}

TitleType::~TitleType()
{
    delete m_title;
}

QDateTime TitleType::attributionDate() const
{
    return m_attributionDate;
}

void TitleType::setAttributionDate(const QDateTime &attributionDate)
{
    m_attributionDate = attributionDate;
}

void TitleType::clearAttributionDate()
{
    m_attributionDate.setDate(QDate());
}

QString TitleType::note() const
{
    return m_note;
}

void TitleType::setNote(const QString &note)
{
    m_note = note;
}

ElementType *TitleType::title() const
{
    return m_title;
}

void TitleType::setTitle(ElementType *title)
{
    if (title != m_title)
        delete m_title;
    m_title = title;
}

QString TitleType::toString() const
{
    if (m_title)
        return m_title->toString();
    return QObject::tr("Untitled core metadata");
}

AlternativeTitleType::AlternativeTitleType()
{
    m_title = 0;
}

AlternativeTitleType::~AlternativeTitleType()
{
    delete m_title;
}

QString AlternativeTitleType::note() const
{
    return m_note;
}

void AlternativeTitleType::setNote(const QString &note)
{
    m_note = note;
}

ElementType *AlternativeTitleType::title() const
{
    return m_title;
}

void AlternativeTitleType::setTitle(ElementType *title)
{
    if (title != m_title)
        delete m_title;
    m_title = title;
}

QString AlternativeTitleType::toString() const
{
    if (m_title)
        return m_title->toString();
    return QObject::tr("Untitled title");
}

SubjectType::SubjectType()
{
    m_subject = 0;
    m_attributor = 0;
}

SubjectType::~SubjectType()
{
    delete m_subject;
    delete m_attributor;
}

QString SubjectType::note() const
{
    return m_note;
}

void SubjectType::setNote(const QString &note)
{
    m_note = note;
}

ElementType *SubjectType::subject() const
{
    return m_subject;
}

void SubjectType::setSubject(ElementType *subject)
{
    if (subject != m_subject)
        delete m_subject;
    m_subject = subject;
}

QString SubjectType::subjectCode()
{
    return m_subjectCode;
}

void SubjectType::setSubjectCode(const QString &subjectCode)
{
    m_subjectCode = subjectCode;
}

QString SubjectType::subjectDefinition()
{
    return m_subjectDefinition;
}

void SubjectType::setSubjectDefinition(const QString &subjectDefinition)
{
    m_subjectDefinition = subjectDefinition;
}

EntityType *SubjectType::attributor() const
{
    return m_attributor;
}

void SubjectType::setAttributor(EntityType *attributor)
{
    if (attributor != m_attributor)
        delete m_attributor;
    m_attributor = attributor;
}

QString SubjectType::toString() const
{
    if (m_subject)
        return m_subject->toString();
    return QObject::tr("Unnamed subject");
}

DescriptionType::DescriptionType()
{
    m_description = 0;
}

DescriptionType::~DescriptionType()
{
    delete m_description;
}

QString DescriptionType::note() const
{
    return m_note;
}

void DescriptionType::setNote(const QString &note)
{
    m_note = note;
}

ElementType *DescriptionType::description() const
{
    return m_description;
}

void DescriptionType::setDescription(ElementType *description)
{
    if (description != m_description)
        delete m_description;
    m_description = description;
}

QString DescriptionType::toString() const
{
    if (m_description)
        return m_description->toString();
    return QObject::tr("Unnamed description");
}

DateType::DateType()
{
    m_created = 0;
    m_issued = 0;
    m_modified = 0;
    m_digitised = 0;
}

DateType::~DateType()
{
    int s = m_date.size();
    for (int i=0; i < s; ++i) {
        delete (m_date.takeAt(0));
    }
    delete m_created;
    delete m_issued;
    delete m_modified;
    delete m_digitised;
    s = m_alternative.size();
    for (int i=0; i < s; ++i) {
        delete (m_alternative.takeAt(0));
    }
}

QList<ElementType *> &DateType::date()
{
    return m_date;
}

DateGroup *DateType::created() const
{
    return m_created;
}

void DateType::setCreated(DateGroup *created)
{
    if (created != m_created)
        delete m_created;
    m_created = created;
}

DateGroup *DateType::issued() const
{
    return m_issued;
}

void DateType::setIssued(DateGroup *issued)
{
    if (issued != m_issued)
        delete m_issued;
    m_issued = issued;
}

DateGroup *DateType::modified() const
{
    return m_modified;
}

void DateType::setModified(DateGroup *modified)
{
    if (modified != m_modified)
        delete m_modified;
    m_modified = modified;
}

DateGroup *DateType::digitised() const
{
    return m_digitised;
}

void DateType::setDigitised(DateGroup *digitised)
{
    if (digitised != m_digitised)
        delete m_digitised;
    m_digitised = digitised;
}

QList<AlternativeType *> &DateType::alternative()
{
    return m_alternative;
}

QString DateType::toString() const
{
    QStringList sl;
    if (m_date.size() > 0)
    {
        sl.append("Date:");
        sl.append(m_date.first()->toString());
        return sl.join(" ");
    }
    if (m_created)
    {
        sl.append("Date created:");
        sl.append(m_created->toString());
        return sl.join(" ");
    }
    if (m_issued)
    {
        sl.append("Date issued:");
        sl.append(m_issued->toString());
        return sl.join(" ");
    }
    if (m_modified)
    {
        sl.append("Date modified:");
        sl.append(m_modified->toString());
        return sl.join(" ");
    }
    if (m_digitised)
    {
        sl.append("Date digitised:");
        sl.append(m_digitised->toString());
        return sl.join(" ");
    }
    if (m_alternative.size() > 0)
    {
        sl.append("Alternative:");
        sl.append(m_alternative.first()->toString());
        return sl.join(" ");
    }
    return "Unspecified Date";
}

TypeType::~TypeType()
{
    int s = m_type.size();
    for (int i=0; i < s; ++i) {
        delete (m_type.takeAt(0));
    }
    s = m_genre.size();
    for (int i=0; i < s; ++i) {
        delete (m_genre.takeAt(0));
    }
    s = m_objectType.size();
    for (int i=0; i < s; ++i) {
        delete (m_objectType.takeAt(0));
    }
    s = m_targetAudience.size();
    for (int i=0; i < s; ++i) {
        delete (m_targetAudience.takeAt(0));
    }
}

QString TypeType::note() const
{
    return m_note;
}

void TypeType::setNote(const QString &note)
{
    m_note = note;
}

QList<ElementType *> &TypeType::type()
{
    return m_type;
}

QList<TypeGroup *> &TypeType::genre()
{
    return m_genre;
}

QList<TypeGroup *> &TypeType::objectType()
{
    return m_objectType;
}

QList<TypeGroup *> &TypeType::targetAudience()
{
    return m_targetAudience;
}

QString TypeType::toString() const
{
    QStringList sl;
    if (m_type.size() > 0)
    {
        sl.append("Type:");
        sl.append(m_type.first()->toString());
        return sl.join(" ");
    }
    if (m_genre.size() > 0)
    {
        sl.append("Genre:");
        sl.append(m_genre.first()->toString());
        return sl.join(" ");
    }
    if (m_objectType.size() > 0)
    {
        sl.append("Object Type:");
        sl.append(m_objectType.first()->toString());
        return sl.join(" ");
    }
    if (m_targetAudience.size() > 0)
    {
        sl.append("Target Audience:");
        sl.append(m_targetAudience.first()->toString());
        return sl.join(" ");
    }
    return "Unspecified Type";
}

IdentifierType::IdentifierType()
{
    m_identifier = 0;
    m_attributor = 0;
}

IdentifierType::~IdentifierType()
{
    delete m_identifier;
    delete m_attributor;
}

QString IdentifierType::note() const
{
    return m_note;
}

void IdentifierType::setNote(const QString &note)
{
    m_note = note;
}

ElementType *IdentifierType::identifier() const
{
    return m_identifier;
}

void IdentifierType::setIdentifier(ElementType *identifier)
{
    if (identifier != m_identifier)
        delete m_identifier;
    m_identifier = identifier;
}

EntityType *IdentifierType::attributor() const
{
    return m_attributor;
}

void IdentifierType::setAttributor(EntityType *attributor)
{
    if (attributor != m_attributor)
        delete m_attributor;
    m_attributor = attributor;
}

QString IdentifierType::toString() const
{
    if (m_identifier)
        return m_identifier->toString();
    return QObject::tr("Unnamed identifier");
}

LanguageType::LanguageType()
{
    m_language = 0;
}

LanguageType::~LanguageType()
{
    delete m_language;
}

QString LanguageType::note() const
{
    return m_note;
}

void LanguageType::setNote(const QString &note)
{
    m_note = note;
}

ElementType *LanguageType::language() const
{
    return m_language;
}

void LanguageType::setLanguage(ElementType *language)
{
    if (language != m_language)
        delete m_language;
    m_language = language;
}

QString LanguageType::toString() const
{
    if (m_language)
        return m_language->toString();
    return QObject::tr("Unnamed language");
}

QString RelationType::note() const
{
    return m_note;
}

void RelationType::setNote(const QString &note)
{
    m_note = note;
}

ElementType *RelationType::relation() const
{
    return m_relation;
}

void RelationType::setRelation(ElementType *relation)
{
    if (relation != m_relation)
        delete m_relation;
    m_relation = relation;
}

IdentifierType *RelationType::relationIdentifier() const
{
    return m_relationIdentifier;
}

void RelationType::setRelationIdentifier(IdentifierType *relationIdentifier)
{
    if (relationIdentifier != m_relationIdentifier)
        delete m_relationIdentifier;
    m_relationIdentifier = relationIdentifier;
}

QString RelationType::relationLink() const
{
    return m_relationLink;
}

void RelationType::setRelationLink(const QString &relationLink)
{
    m_relationLink = relationLink;
}

QString RelationType::toString() const
{
    if (m_relation)
        return m_relation->toString();
    return QObject::tr("Unnamed relation");
}

HasTrackPartType::HasTrackPartType()
{
    m_trackPartTitle = 0;
    m_destinationStart = 0;
    m_destinationEnd = 0;
    m_sourceStart = 0;
    m_sourceEnd = 0;
}

HasTrackPartType::~HasTrackPartType()
{
    delete m_trackPartTitle;
    delete m_destinationStart;
    delete m_destinationEnd;
    delete m_sourceStart;
    delete m_sourceEnd;
}

AlternativeTitleType *HasTrackPartType::trackPartTitle() const
{
    return m_trackPartTitle;
}

void HasTrackPartType::setTrackPartTitle(AlternativeTitleType *trackPartTitle)
{
    if (trackPartTitle != m_trackPartTitle)
        delete m_trackPartTitle;
    m_trackPartTitle = trackPartTitle;
}

TimeType *HasTrackPartType::destinationStart() const
{
    return m_destinationStart;
}

void HasTrackPartType::setDestinationStart(TimeType *destinationStart)
{
    if (destinationStart != m_destinationStart)
        delete m_destinationStart;
    m_destinationStart = destinationStart;
}

TimeType *HasTrackPartType::destinationEnd() const
{
    return m_destinationEnd;
}

void HasTrackPartType::setDestinationEnd(TimeType *destinationEnd)
{
    if (destinationEnd != m_destinationEnd)
    delete m_destinationEnd;
    m_destinationEnd = destinationEnd;
}

TimeType *HasTrackPartType::sourceStart() const
{
    return m_sourceStart;
}

void HasTrackPartType::setSourceStart(TimeType *sourceStart)
{
    if (sourceStart != m_sourceStart)
        delete m_sourceStart;
    m_sourceStart = sourceStart;
}

TimeType *HasTrackPartType::sourceEnd() const
{
    return m_sourceEnd;
}

void HasTrackPartType::setSourceEnd(TimeType *sourceEnd)
{
    if (sourceEnd != m_sourceEnd)
        delete m_sourceEnd;
    m_sourceEnd = sourceEnd;
}

QString HasTrackPartType::toString() const
{
    if (m_trackPartTitle)
        return m_trackPartTitle->toString();
    return QObject::tr("Untitled track part");
}

RelationType::RelationType()
{
    m_relation = 0;
    m_relationIdentifier = 0;
    m_runningOrderNumber = 0;
}

RelationType::~RelationType()
{
    delete m_relation;
    delete m_relationIdentifier;
    delete m_runningOrderNumber;
}

int *RelationType::runningOrderNumber() const
{
    return m_runningOrderNumber;
}

void RelationType::setRunningOrderNumber(int runningOrderNumber)
{
    delete m_runningOrderNumber;
    m_runningOrderNumber = new int(runningOrderNumber);
}

void RelationType::clearRunningOrderNumber()
{
    delete m_runningOrderNumber;
    m_runningOrderNumber = 0;
}

TemporalType::TemporalType()
{
    m_periodOfTime = 0;
}

TemporalType::~TemporalType()
{
    delete m_periodOfTime;
}

QString TemporalType::note() const
{
    return m_note;
}

void TemporalType::setNote(const QString &note)
{
    m_note = note;
}

QString TemporalType::periodId() const
{
    return m_periodId;
}

void TemporalType::setPeriodId(const QString &periodID)
{
    m_periodId = periodID;
}

DateGroup *TemporalType::periodOfTime() const
{
    return m_periodOfTime;
}

void TemporalType::setPeriodOfTime(DateGroup *periodOfTime)
{
    if (periodOfTime != m_periodOfTime)
        delete m_periodOfTime;
    m_periodOfTime = periodOfTime;
}

QString TemporalType::toString() const
{
    if (!m_periodId.isEmpty())
        return m_periodId;
    if (!typeLabel().isEmpty())
        return typeLabel();
    return QObject::tr("Unnamed period");
}

CoordinatesType::CoordinatesType()
{
    m_posy = 0;
    m_posx = 0;
}

float CoordinatesType::posy() const
{
    return m_posy;
}

void CoordinatesType::setPosy(float posy)
{
    m_posy = posy;
}

void CoordinatesType::clearPosy()
{
    m_posy = 0;
}

float CoordinatesType::posx() const
{
    return m_posx;
}

void CoordinatesType::setPosx(float posx)
{
    m_posx = posx;
}

void CoordinatesType::clearPosx()
{
    m_posx = 0;
}

QString CoordinatesType::toString() const
{
    return "("+QString::number(m_posx)+","+QString::number(m_posy)+")";
}

LocationType::LocationType()
{
    m_coordinates = 0;
}

LocationType::~LocationType()
{
    delete m_coordinates;
}

QString LocationType::note() const
{
    return m_note;
}

void LocationType::setNote(const QString &note)
{
    m_note = note;
}

QString LocationType::locationId() const
{
    return m_locationId;
}

void LocationType::setLocationId(const QString &locationId)
{
    m_locationId = locationId;
}

QString LocationType::name() const
{
    return m_name;
}

void LocationType::setName(const QString &name)
{
    m_name = name;
}

CoordinatesType *LocationType::coordinates() const
{
    return m_coordinates;
}

void LocationType::setCoordinates(CoordinatesType *coordinates)
{
    if (coordinates != m_coordinates)
        delete m_coordinates;
    m_coordinates = coordinates;
}

QString LocationType::code() const
{
    return m_code;
}

void LocationType::setCode(const QString &code)
{
    m_code = code;
}

QString LocationType::toString() const
{
    if (m_locationId.isEmpty())
        return QObject::tr("Unnamed location");
    return m_locationId;
}

CoverageType::CoverageType()
{
    m_coverage = 0;
    m_temporal = 0;
}

CoverageType::~CoverageType()
{
    delete m_coverage;
    delete m_temporal;
    int s = m_location.size();
    for (int i=0; i < s; ++i) {
        delete (m_location.takeAt(0));
    }
}

ElementType *CoverageType::coverage() const
{
    return m_coverage;
}

void CoverageType::setCoverage(ElementType *coverage)
{
    if (coverage != m_coverage)
        delete m_coverage;
    m_coverage = coverage;
}

TemporalType *CoverageType::temporal() const
{
    return m_temporal;
}

void CoverageType::setTemporal(TemporalType *temporal)
{
    if (temporal != m_temporal)
        delete m_temporal;
    m_temporal = temporal;
}

QList<LocationType *> &CoverageType::location()
{
    return m_location;
}

QString CoverageType::toString() const
{
    if (m_coverage)
        return m_coverage->toString();
    return QObject::tr("Unnamed coverage");
}

RightsType::RightsType()
{
    m_rights = 0;
    m_rightsHolder = 0;
    m_exploitationIssues = 0;
    m_coverage = 0;
    m_rightsClearanceFlag = 0;
}

RightsType::~RightsType()
{
    // Note: m_formats pointer are not owned by this
    // object and thus must not be deleted.
    delete m_rights;
    delete m_rightsHolder;
    delete m_exploitationIssues;
    delete m_coverage;
    delete m_rightsClearanceFlag;
    int s = m_disclaimer.size();
    for (int i=0; i < s; ++i) {
        delete (m_disclaimer.takeAt(0));
    }
    s = m_rightsId.size();
    for (int i=0; i < s; ++i) {
        delete (m_rightsId.takeAt(0));
    }
    s = m_contactDetails.size();
    for (int i=0; i < s; ++i) {
        delete (m_contactDetails.takeAt(0));
    }
}

QString RightsType::note() const
{
    return m_note;
}

void RightsType::setNote(const QString &note)
{
    m_note = note;
}

QList<FormatType *> &RightsType::formats()
{
    return m_formats;
}

ElementType *RightsType::rights() const
{
    return m_rights;
}

void RightsType::setRights(ElementType *rights)
{
    if (rights != m_rights)
        delete m_rights;
    m_rights = rights;
}

QString RightsType::rightsLink() const
{
    return m_rightsLink;
}

void RightsType::setRightsLink(const QString &rightsLink)
{
    m_rightsLink = rightsLink;
}

EntityType *RightsType::rightsHolder() const
{
    return m_rightsHolder;
}

void RightsType::setRightsHolder(EntityType *rightsHolder)
{
    if (rightsHolder != m_rightsHolder)
        delete m_rightsHolder;
    m_rightsHolder = rightsHolder;
}

ElementType *RightsType::exploitationIssues() const
{
    return m_exploitationIssues;
}

void RightsType::setExploitationIssues(ElementType *exploitationIssues)
{
    if (exploitationIssues != m_exploitationIssues)
        delete m_exploitationIssues;
    m_exploitationIssues = exploitationIssues;
}

CoverageType *RightsType::coverage() const
{
    return m_coverage;
}

void RightsType::setCoverage(CoverageType *coverage)
{
    if (coverage != m_coverage)
        delete m_coverage;
    m_coverage = coverage;
}

bool *RightsType::rightsClearanceFlag() const
{
    return m_rightsClearanceFlag;
}

void RightsType::setRightsClearanceFlag(bool rightsClearanceFlag)
{
    delete m_rightsClearanceFlag;
    m_rightsClearanceFlag = new bool(rightsClearanceFlag);
}

void RightsType::clearRightsClearanceFlag()
{
    delete m_rightsClearanceFlag;
    m_rightsClearanceFlag = 0;
}

QList<ElementType *> &RightsType::disclaimer()
{
    return m_disclaimer;
}

QList<IdentifierType *> &RightsType::rightsID()
{
    return m_rightsId;
}

QList<ContactDetailsType *> &RightsType::contactDetails()
{
    return m_contactDetails;
}

QString RightsType::toString() const
{
    if (m_rights)
        return m_rights->toString();
    if (!typeLabel().isEmpty())
        return typeLabel();
    return QObject::tr("Unspecified rights");
}

PublicationType::PublicationType()
{
    m_channel = 0;
}

PublicationType::~PublicationType()
{
    delete m_channel;
}

QDateTime PublicationType::date() const
{
    return m_date;
}

void PublicationType::setDate(const QDateTime &date)
{
    m_date = date;
}

void PublicationType::clearDate()
{
    m_date = QDateTime();
}

QDateTime PublicationType::time() const
{
    return m_time;
}

void PublicationType::setTime(const QDateTime &time)
{
    m_time = time;
}

void PublicationType::clearTime()
{
    m_time = QDateTime();
}

FormatType *PublicationType::channel() const
{
    return m_channel;
}

void PublicationType::setChannel(FormatType *channel)
{
    if (channel != m_channel)
        delete m_channel;
    m_channel = channel;
}

QString PublicationType::channelString() const
{
    return m_channelString;
}

void PublicationType::setChannelString(const QString &channelString)
{
    m_channelString = channelString;
}

QString PublicationType::toString() const
{
    QStringList output;
    if (!m_channelString.isEmpty()) {
        output.append(m_channelString);
    } else if (m_channel) {
        output.append(m_channel->toString());
    }
    if (m_date.isValid())
        output.append(m_date.toString());
    if (m_time.isValid())
        output.append(m_date.toString());
    if (output.isEmpty()) {
        return QObject::tr("Undefined publication");
    } else {
        return output.join(" ");
    }
}

PublicationHistoryType::PublicationHistoryType()
{
    m_firstPublication = 0;
}

PublicationHistoryType::~PublicationHistoryType()
{
    delete m_firstPublication;
    int s = m_repetitions.size();
    for (int i=0; i < s; ++i) {
        delete (m_repetitions.takeAt(0));
    }
}

PublicationType *PublicationHistoryType::firstPublication() const
{
    return m_firstPublication;
}

void PublicationHistoryType::setFirstPublication(PublicationType *firstPublication)
{
    if (firstPublication != m_firstPublication)
        delete m_firstPublication;
    m_firstPublication = firstPublication;
}

QList<PublicationType *> &PublicationHistoryType::repetitions()
{
    return m_repetitions;
}

QString PublicationHistoryType::toString() const
{
    if (m_firstPublication)
        return m_firstPublication->toString();
    else if (!m_repetitions.isEmpty())
        return m_repetitions.at(0)->toString();
    return QObject::tr("Empty publication history");
}

RatingType::RatingType()
{
    m_ratingProvider = 0;
}

RatingType::~RatingType()
{
    delete m_ratingProvider;
}

QString RatingType::ratingValue() const
{
    return m_ratingValue;
}

void RatingType::setRatingValue(const QString &ratingValue)
{
    m_ratingValue = ratingValue;
}

QString RatingType::ratingScaleMaxValue() const
{
    return m_ratingScaleMaxValue;
}

void RatingType::setRatingScaleMaxValue(const QString &ratingScaleMaxValue)
{
    m_ratingScaleMaxValue = ratingScaleMaxValue;
}

QString RatingType::ratingScaleMinValue() const
{
    return m_ratingScaleMinValue;
}

void RatingType::setRatingScaleMinValue(const QString &ratingScaleMinValue)
{
    m_ratingScaleMinValue = ratingScaleMinValue;
}

EntityType *RatingType::ratingProvider() const
{
    return m_ratingProvider;
}

void RatingType::setRatingProvider(EntityType *ratingProvider)
{
    if (ratingProvider != m_ratingProvider)
        delete m_ratingProvider;
    m_ratingProvider = ratingProvider;
}

QString RatingType::toString() const
{
    if (m_ratingValue.isEmpty())
        return QObject::tr("Undefined rating");
    return m_ratingValue;
}

QString PartType::partId() const
{
    return m_partId;
}

void PartType::setPartId(const QString &partId)
{
    m_partId = partId;
}

QString PartType::partName() const
{
    return m_partName;
}

void PartType::setPartName(const QString &partName)
{
    m_partName = partName;
}

QString PartType::toString() const
{
    if (!m_partName.isEmpty())
        return m_partName;
    if (m_partId.isEmpty())
        return QObject::tr("Unnamed part");
    return m_partId;
}

QList<TitleType *> &CoreMetadataType::title()
{
    return m_title;
}

QList<AlternativeTitleType *> &CoreMetadataType::alternativeTitle()
{
    return m_alternativeTitle;
}

QList<EntityType *> &CoreMetadataType::creator()
{
    return m_creator;
}

QList<SubjectType *> &CoreMetadataType::subject()
{
    return m_subject;
}

QList<DescriptionType *> &CoreMetadataType::description()
{
    return m_description;
}

QList<EntityType *> &CoreMetadataType::publisher()
{
    return m_publisher;
}

QList<EntityType *> &CoreMetadataType::contributor()
{
    return m_contributor;
}

QList<DateType *> &CoreMetadataType::date()
{
    return m_date;
}

QList<TypeType *> &CoreMetadataType::type()
{
    return m_type;
}

QList<FormatType *> &CoreMetadataType::format()
{
    return m_format;
}

QList<IdentifierType *> &CoreMetadataType::identifier()
{
    return m_identifier;
}

QList<ElementType *> &CoreMetadataType::source()
{
    return m_source;
}

QList<LanguageType *> &CoreMetadataType::language()
{
    return m_language;
}

QList<RelationType *> &CoreMetadataType::relation()
{
    return m_relation;
}

QList<RelationType *> &CoreMetadataType::isVersionOf()
{
    return m_isVersionOf;
}

QList<RelationType *> &CoreMetadataType::hasVersion()
{
    return m_hasVersion;
}

QList<RelationType *> &CoreMetadataType::isReplacedBy()
{
    return m_isReplacedBy;
}

QList<RelationType *> &CoreMetadataType::replaces()
{
    return m_replaces;
}

QList<RelationType *> &CoreMetadataType::isRequiredBy()
{
    return m_isRequiredBy;
}

QList<RelationType *> &CoreMetadataType::requires()
{
    return m_requires;
}

QList<RelationType *> &CoreMetadataType::isPartOf()
{
    return m_isPartOf;
}

QList<RelationType *> &CoreMetadataType::hasPart()
{
    return m_hasPart;
}

QList<HasTrackPartType *> &CoreMetadataType::hasTrackPart()
{
    return m_hasTrackPart;
}

QList<RelationType *> &CoreMetadataType::isReferencedBy()
{
    return m_isReferencedBy;
}

QList<RelationType *> &CoreMetadataType::references()
{
    return m_references;
}

QList<RelationType *> &CoreMetadataType::isFormatOf()
{
    return m_isFormatOf;
}

QList<RelationType *> &CoreMetadataType::hasFormat()
{
    return m_hasFormat;
}

QList<RelationType *> &CoreMetadataType::isEpisodeOf()
{
    return m_isEpisodeOf;
}

QList<RelationType *> &CoreMetadataType::isMemberOf()
{
    return m_isMemberOf;
}

QList<CoverageType *> &CoreMetadataType::coverage()
{
    return m_coverage;
}

QList<RightsType *> &CoreMetadataType::rights()
{
    return m_rights;
}

QList<RatingType *> &CoreMetadataType::rating()
{
    return m_rating;
}

QList<PartType *> &CoreMetadataType::part()
{
    return m_part;
}

ElementType *CoreMetadataType::version() const
{
    return m_version;
}

void CoreMetadataType::setVersion(ElementType *version)
{
    if (version != m_version)
        delete m_version;
    m_version = version;
}

PublicationHistoryType *CoreMetadataType::publicationHistory() const
{
    return m_publicationHistory;
}

void CoreMetadataType::setPubblicationHistory(PublicationHistoryType *publicationHistory)
{
    if (publicationHistory != m_publicationHistory)
        delete m_publicationHistory;
    m_publicationHistory = publicationHistory;
}

QString AlternativeType::toString() const
{
    return DateGroup::toString();
}
