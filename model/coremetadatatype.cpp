#include "coremetadatatype.h"

CoreMetadataType::CoreMetadataType()
{
    m_version = 0;
    m_publicationHistory = 0;
}

TitleType::TitleType()
{
    m_title = 0;
}

QDateTime TitleType::attributionDate() const
{
    return m_attributionDate;
}

void TitleType::setAttributionDate(const QDateTime &attributionDate)
{
    m_attributionDate = attributionDate;
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
    m_title = title;
}

AlternativeTitleType::AlternativeTitleType()
{
    m_title = 0;
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
    m_title = title;
}

SubjectType::SubjectType()
{
    m_subject = 0;
    m_attributor = 0;
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
    m_attributor = attributor;
}

DescriptionType::DescriptionType()
{
    m_description = 0;
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
    m_description = description;
}

DateType::DateType()
{
    m_created = 0;
    m_issued = 0;
    m_modified = 0;
    m_digitised = 0;
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
    m_created = created;
}

DateGroup *DateType::issued() const
{
    return m_issued;
}

void DateType::setIssued(DateGroup *issued)
{
    m_issued = issued;
}

DateGroup *DateType::modified() const
{
    return m_modified;
}

void DateType::setModified(DateGroup *modified)
{
    m_modified = modified;
}

DateGroup *DateType::digitised() const
{
    return m_digitised;
}

void DateType::setDigitised(DateGroup *digitised)
{
    m_digitised = digitised;
}

QList<AlternativeType *> &DateType::alternative()
{
    return m_alternative;
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
    m_identifier = identifier;
}

EntityType *IdentifierType::attributor() const
{
    return m_attributor;
}

void IdentifierType::setAttributor(EntityType *attributor)
{
    m_attributor = attributor;
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
    m_language = language;
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
    m_relation = relation;
}

IdentifierType *RelationType::relationIdentifier() const
{
    return m_relationIdentifier;
}

void RelationType::setRelationIdentifier(IdentifierType *relationIdentifier)
{
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

AlternativeTitleType *HasTrackPartType::trackPartTitle() const
{
    return m_trackPartTitle;
}

void HasTrackPartType::setTrackPartTitle(AlternativeTitleType *trackPartTitle)
{
    m_trackPartTitle = trackPartTitle;
}

TimeType *HasTrackPartType::destinationStart() const
{
    return m_destinationStart;
}

void HasTrackPartType::setDestinationStart(TimeType *destinationStart)
{
    m_destinationStart = destinationStart;
}

TimeType *HasTrackPartType::destinationEnd() const
{
    return m_destinationEnd;
}

void HasTrackPartType::setDestinationEnd(TimeType *destinationEnd)
{
    m_destinationEnd = destinationEnd;
}

TimeType *HasTrackPartType::sourceStart() const
{
    return m_sourceStart;
}

void HasTrackPartType::setSourceStart(TimeType *sourceStart)
{
    m_sourceStart = sourceStart;
}

TimeType *HasTrackPartType::sourceEnd() const
{
    return m_sourceEnd;
}

void HasTrackPartType::setSourceEnd(TimeType *sourceEnd)
{
    m_sourceEnd = sourceEnd;
}

int RelationType::runningOrderNumber() const
{
    return m_runningOrderNumber;
}

void RelationType::setRunningOrderNumber(int runningOrderNumber)
{
    m_runningOrderNumber = runningOrderNumber;
}

QString TemporalType::note() const
{
    return m_note;
}

void TemporalType::setNote(const QString &note)
{
    m_note = note;
}

QString TemporalType::periodID() const
{
    return m_periodId;
}

void TemporalType::setPeriodID(const QString &periodID)
{
    m_periodId = periodID;
}

DateGroup *TemporalType::periodOfTime() const
{
    return m_periodOfTime;
}

void TemporalType::setPeriodOfTime(DateGroup *periodOfTime)
{
    m_periodOfTime = periodOfTime;
}

float CoordinatesType::posy() const
{
    return m_posy;
}

void CoordinatesType::setPosy(float posy)
{
    m_posy = posy;
}

float CoordinatesType::posx() const
{
    return m_posx;
}

void CoordinatesType::setPosx(float posx)
{
    m_posx = posx;
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

ElementType *CoverageType::coverage() const
{
    return m_coverage;
}

void CoverageType::setCoverage(ElementType *coverage)
{
    m_coverage = coverage;
}

TemporalType *CoverageType::temporal() const
{
    return m_temporal;
}

void CoverageType::setTemporal(TemporalType *temporal)
{
    m_temporal = temporal;
}

QList<LocationType *> &CoverageType::location()
{
    return m_location;
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
    m_rightsHolder = rightsHolder;
}

ElementType *RightsType::exploitationIssues() const
{
    return m_exploitationIssues;
}

void RightsType::setExploitationIssues(ElementType *exploitationIssues)
{
    m_exploitationIssues = exploitationIssues;
}

CoverageType *RightsType::coverage() const
{
    return m_coverage;
}

void RightsType::setCoverage(CoverageType *coverage)
{
    m_coverage = coverage;
}

bool RightsType::isRightsClearanceFlagSet() const
{
    return m_rightsClearanceFlag;
}

void RightsType::setRightsClearanceFlagSet(bool rightsClearanceFlag)
{
    m_rightsClearanceFlag = rightsClearanceFlag;
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

QDateTime PublicationType::date() const
{
    return m_date;
}

void PublicationType::setDate(const QDateTime &date)
{
    m_date = date;
}

QTime PublicationType::time() const
{
    return m_time;
}

void PublicationType::setTime(const QTime &time)
{
    m_time = time;
}

FormatType *PublicationType::channel() const
{
    return m_channel;
}

void PublicationType::setChannel(FormatType *channel)
{
    m_channel = channel;
}

PublicationType *PublicationHistoryType::firstPublication() const
{
    return m_firstPublication;
}

void PublicationHistoryType::setFirstPublication(PublicationType *firstPublication)
{
    m_firstPublication = firstPublication;
}

QList<PublicationType *> &PublicationHistoryType::repetitions()
{
    return m_repetitions;
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
    m_ratingProvider = ratingProvider;
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
    m_version = version;
}

PublicationHistoryType *CoreMetadataType::publicationHistory() const
{
    return m_publicationHistory;
}

void CoreMetadataType::setPubblicationHistory(PublicationHistoryType *publicationHistory)
{
    m_publicationHistory = publicationHistory;
}



















