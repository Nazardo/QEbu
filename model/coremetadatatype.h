#ifndef COREMETADATATYPE_H
#define COREMETADATATYPE_H

#include <QList>
#include <QDateTime>
#include <QString>
#include "entitytype.h"
#include "elementtype.h"
#include "contactdetailstype.h"
#include "timetype.h"
#include "formattype.h"
#include "typegroup.h"
#include "statusgroup.h"
#include "dategroup.h"
#include "formatgroup.h"

class TitleType;
class AlternativeTitleType;
class SubjectType;
class DescriptionType;
class DateType;
class TypeType;
class IdentifierType;
class LanguageType;
class RelationType;
class HasTrackPartType;
class CoverageType;
class RightsType;
class PublicationHistoryType;
class RatingType;
class PartType;

class CoreMetadataType
{
public:
    CoreMetadataType();
    ~CoreMetadataType();
    QList<TitleType *> &title();
    QList<AlternativeTitleType *> &alternativeTitle();
    QList<EntityType *> &creator();
    QList<SubjectType *> &subject();
    QList<DescriptionType *> &description();
    QList<EntityType *> &publisher();
    QList<EntityType *> &contributor();
    QList<DateType *> &date();
    QList<TypeType *> &type();
    QList<FormatType *> &format();
    QList<IdentifierType *> &identifier();
    QList<ElementType *> &source();
    QList<LanguageType *> &language();
    QList<RelationType *> &relation();
    QList<RelationType *> &isVersionOf();
    QList<RelationType *> &hasVersion();
    QList<RelationType *> &isReplacedBy();
    QList<RelationType *> &replaces();
    QList<RelationType *> &isRequiredBy();
    QList<RelationType *> &requires();
    QList<RelationType *> &isPartOf();
    QList<RelationType *> &hasPart();
    QList<HasTrackPartType *> &hasTrackPart();
    QList<RelationType *> &isReferencedBy();
    QList<RelationType *> &references();
    QList<RelationType *> &isFormatOf();
    QList<RelationType *> &hasFormat();
    QList<RelationType *> &isEpisodeOf();
    QList<RelationType *> &isMemberOf();
    QList<CoverageType *> &coverage();
    QList<RightsType *> &rights();
    QList<RatingType *> &rating();
    QList<PartType *> &part();
    ElementType *version() const;
    void setVersion(ElementType *version);
    PublicationHistoryType *publicationHistory() const;
    void setPubblicationHistory(PublicationHistoryType *pubblicationHistory);

private:
    // Attributes
    QList<TitleType *> m_title;
    QList<AlternativeTitleType *> m_alternativeTitle;
    QList<EntityType *> m_creator;
    QList<SubjectType *> m_subject;
    QList<DescriptionType *> m_description;
    QList<EntityType *> m_publisher;
    QList<EntityType *> m_contributor;
    QList<DateType *> m_date;
    QList<TypeType *> m_type;
    QList<FormatType *> m_format;
    QList<IdentifierType *> m_identifier;
    QList<ElementType *> m_source;
    QList<LanguageType *> m_language;
    QList<RelationType *> m_relation;
    QList<RelationType *> m_isVersionOf;
    QList<RelationType *> m_hasVersion;
    QList<RelationType *> m_isReplacedBy;
    QList<RelationType *> m_replaces;
    QList<RelationType *> m_isRequiredBy;
    QList<RelationType *> m_requires;
    QList<RelationType *> m_isPartOf;
    QList<RelationType *> m_hasPart;
    QList<HasTrackPartType *> m_hasTrackPart;
    QList<RelationType *> m_isReferencedBy;
    QList<RelationType *> m_references;
    QList<RelationType *> m_isFormatOf;
    QList<RelationType *> m_hasFormat;
    QList<RelationType *> m_isEpisodeOf;
    QList<RelationType *> m_isMemberOf;
    QList<CoverageType *> m_coverage;
    QList<RightsType *> m_rights;
    ElementType * m_version;
    PublicationHistoryType * m_publicationHistory;
    QList<RatingType *> m_rating;
    QList<PartType *> m_part;
};

class TitleType
{
public:
    TitleType();
    ~TitleType();
    QDateTime attributionDate() const;
    void setAttributionDate (const QDateTime &attributionDate);
    QString note() const;
    void setNote(const QString &note);
    ElementType *title() const;
    void setTitle(ElementType *title);
private:
    QDateTime m_attributionDate;
    QString m_note;
    ElementType *m_title;
};

class AlternativeTitleType : public TypeGroup, public StatusGroup, public DateGroup
{
public:
    AlternativeTitleType();
    ~AlternativeTitleType();
    QString note() const;
    void setNote(const QString &note);
    ElementType *title() const;
    void setTitle(ElementType *title);
private:
    QString m_note;
    ElementType *m_title;
};

class SubjectType : public TypeGroup
{
public:
    SubjectType();
    ~SubjectType();
    QString note() const;
    void setNote(const QString &note);
    ElementType *subject() const;
    void setSubject(ElementType *subject);
    QString subjectCode();
    void setSubjectCode(const QString &subjectCode);
    QString subjectDefinition();
    void setSubjectDefinition(const QString &subjectDefinition);
    EntityType *attributor() const;
    void setAttributor (EntityType *attributor);
private:
    QString m_note;
    ElementType *m_subject;
    QString m_subjectCode; // anyURI
    QString m_subjectDefinition;
    EntityType *m_attributor;
};

class DescriptionType : public TypeGroup
{
public:
    DescriptionType();
    ~DescriptionType();
    QString note() const;
    void setNote(const QString &note);
    ElementType *description() const;
    void setDescription(ElementType *description);
private:
    QString m_note;
    ElementType *m_description;
};

class AlternativeType : public DateGroup, public TypeGroup { };

class DateType
{
public:
    DateType();
    ~DateType();
    QList<ElementType *> &date();
    DateGroup *created() const;
    void setCreated (DateGroup *created);
    DateGroup *issued() const;
    void setIssued (DateGroup *issued);
    DateGroup *modified() const;
    void setModified (DateGroup *modified);
    DateGroup *digitised() const;
    void setDigitised (DateGroup *digitised);
    QList<AlternativeType *> &alternative();
private:
    QList<ElementType *> m_date;
    DateGroup *m_created;
    DateGroup *m_issued;
    DateGroup *m_modified;
    DateGroup *m_digitised;
    QList<AlternativeType *> m_alternative;
};

class TypeType
{
public:
    ~TypeType();
    QString note() const;
    void setNote(const QString &note);
    QList<ElementType *> &type();
    QList<TypeGroup *> &genre();
    QList<TypeGroup *> &objectType();
    QList<TypeGroup *> &targetAudience();
private:
    QString m_note;
    QList<ElementType *> m_type;
    QList<TypeGroup *> m_genre;
    QList<TypeGroup *> m_objectType;
    QList<TypeGroup *> m_targetAudience;

};

class IdentifierType : public TypeGroup, public FormatGroup
{
public:
    IdentifierType();
    ~IdentifierType();
    QString note() const;
    void setNote(const QString &note);
    ElementType *identifier() const;
    void setIdentifier(ElementType *identifier);
    EntityType *attributor() const;
    void setAttributor(EntityType *attributor);
private:
    QString m_note;
    ElementType *m_identifier;
    EntityType *m_attributor;
};

class LanguageType : public TypeGroup
{
public:
    LanguageType();
    ~LanguageType();
    QString note() const;
    void setNote(const QString &note);
    ElementType *language() const;
    void setLanguage(ElementType *language);
private:
    QString m_note;
    ElementType *m_language;
};

class RelationType : public TypeGroup
{
public:
    RelationType();
    ~RelationType();
    int runningOrderNumber() const;
    void setRunningOrderNumber(int runningOrderNumber);
    QString note() const;
    void setNote(const QString &note);
    ElementType *relation() const;
    void setRelation(ElementType *relation);
    IdentifierType *relationIdentifier() const;
    void setRelationIdentifier(IdentifierType *relationIdentifier);
    QString relationLink() const;
    void setRelationLink(const QString &relationLink);
private:
    int m_runningOrderNumber;
    QString m_note;
    ElementType *m_relation;
    IdentifierType *m_relationIdentifier;
    QString m_relationLink; // anyURI
};

class HasTrackPartType : public RelationType
{
public:
    HasTrackPartType();
    ~HasTrackPartType();
    AlternativeTitleType *trackPartTitle() const;
    void setTrackPartTitle(AlternativeTitleType *trackPartTitle);
    TimeType *destinationStart() const;
    void setDestinationStart(TimeType *destinationStart);
    TimeType *destinationEnd() const;
    void setDestinationEnd(TimeType *destinationEnd);
    TimeType *sourceStart() const;
    void setSourceStart(TimeType *sourceStart);
    TimeType *sourceEnd() const;
    void setSourceEnd(TimeType *sourceEnd);
private:
    AlternativeTitleType *m_trackPartTitle;
    TimeType *m_destinationStart;
    TimeType *m_destinationEnd;
    TimeType *m_sourceStart;
    TimeType *m_sourceEnd;
};

class TemporalType : public TypeGroup
{
public:
    TemporalType();
    ~TemporalType();
    QString note() const;
    void setNote(const QString &note);
    QString periodId() const;
    void setPeriodId(const QString &periodId);
    DateGroup *periodOfTime() const;
    void setPeriodOfTime(DateGroup *periodOfTime);
private:
    QString m_note;
    QString m_periodId; // anyURI
    DateGroup *m_periodOfTime;
};

class CoordinatesType : public FormatGroup
{
public:
    float posy() const;
    void setPosy(float posy);
    float posx() const;
    void setPosx(float posx);
private:
    float m_posy;
    float m_posx;
};

class LocationType : public TypeGroup
{
public:
    LocationType();
    ~LocationType();
    QString note() const;
    void setNote(const QString &note);
    QString locationId() const;
    void setLocationId(const QString &locationId);
    QString name() const;
    void setName(const QString &name);
    CoordinatesType *coordinates() const;
    void setCoordinates(CoordinatesType *coordinates);
    QString code() const;
    void setCode(const QString &code);
private:
    QString m_note;
    QString m_locationId; // anyURI
    QString m_name;
    CoordinatesType *m_coordinates;
    QString m_code; // anyURI
};

class CoverageType
{
public:
    CoverageType();
    ~CoverageType();
    ElementType *coverage() const;
    void setCoverage(ElementType *coverage);
    TemporalType *temporal() const;
    void setTemporal(TemporalType *temporal);
    QList<LocationType *> &location();
private:
    ElementType *m_coverage;
    TemporalType *m_temporal;
    QList<LocationType *> m_location;
};

class RightsType : public TypeGroup
{
public:
    RightsType();
    ~RightsType();
    QString note() const;
    void setNote(const QString &note);
    QList<FormatType *> &formats();
    ElementType *rights() const;
    void setRights(ElementType *rights);
    QString rightsLink() const;
    void setRightsLink(const QString &rightsLink);
    EntityType *rightsHolder() const;
    void setRightsHolder(EntityType *rightsHolder);
    ElementType *exploitationIssues() const;
    void setExploitationIssues(ElementType *exploitationIssues);
    CoverageType *coverage() const;
    void setCoverage(CoverageType *coverage);
    bool isRightsClearanceFlagSet() const;
    void setRightsClearanceFlagSet(bool rightsClearanceFlag);
    QList<ElementType *> &disclaimer();
    QList<IdentifierType *> &rightsID();
    QList<ContactDetailsType *> &contactDetails();
private:
    QString m_note;
    QList<FormatType *> m_formats;
    ElementType *m_rights;
    QString m_rightsLink; // anyURI
    EntityType *m_rightsHolder;
    ElementType *m_exploitationIssues;
    CoverageType *m_coverage;
    bool m_rightsClearanceFlag;
    QList<ElementType *> m_disclaimer;
    QList<IdentifierType *> m_rightsId;
    QList<ContactDetailsType *> m_contactDetails;
};

class PublicationType
{
public:
    PublicationType();
    ~PublicationType();
    QDateTime date() const;
    void setDate (const QDateTime &date);
    QDateTime time() const;
    void setTime (const QDateTime &time);
    FormatType *channel() const;
    void setChannel(FormatType *channel);
private:
    QDateTime m_date;
    QDateTime m_time;
    FormatType *m_channel;
};

class PublicationHistoryType
{
public:
    PublicationHistoryType();
    ~PublicationHistoryType();
    PublicationType *firstPublication() const;
    void setFirstPublication(PublicationType *firstPublication);
    QList<PublicationType *> &repetitions();
private:
    PublicationType *m_firstPublication;
    QList<PublicationType *> m_repetitions;
};

class RatingType : public TypeGroup, public FormatGroup
{
public:
    RatingType();
    ~RatingType();
    QString ratingValue() const;
    void setRatingValue(const QString &ratingValue);
    QString ratingScaleMaxValue() const;
    void setRatingScaleMaxValue(const QString &ratingScaleMaxValue);
    QString ratingScaleMinValue() const;
    void setRatingScaleMinValue(const QString &ratingScaleMinValue);
    EntityType *ratingProvider() const;
    void setRatingProvider(EntityType *ratingProvider);
private:
    QString m_ratingValue;
    QString m_ratingScaleMaxValue;
    QString m_ratingScaleMinValue;
    EntityType *m_ratingProvider;
};

class PartType : public CoreMetadataType
{
public:
    QString partId() const;
    void setPartId(const QString &partId);
    QString partName() const;
    void setPartName(const QString &partName);
private:
    QString m_partId;
    QString m_partName;
};


#endif // COREMETADATATYPE_H
