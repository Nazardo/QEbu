#ifndef EBUSERIALIZER_H
#define EBUSERIALIZER_H

#include <QFile>
#include <QtXml/QDomElement>
#include <QString>
#include "../model/ebucoremaintype.h"

class EbuSerializer
{
public:
    EbuSerializer(EbuCoreMainType *root);
    bool serializeToFile(QFile &file);
    QString errorMsg();
private:
    QDomElement serializeCoreMetadata(CoreMetadataType *);
    QDomElement serializeAlternative(AlternativeType *);
    QDomElement serializeAudioTrack(AudioTrackType *);
    QDomElement serializeDocumentFormat(DocumentFormatType *);
    QDomElement serializeTime(TimeType *);
    QDomElement serializeDuration(DurationType *duration);
    QDomElement serializeTemporal(TemporalType *);
    QDomElement serializeLocation(LocationType *);
    QDomElement serializeCoordinates(CoordinatesType *);
    QDomElement serializeEntity(EntityType *);
    QDomElement serializeContactDetails(ContactDetailsType *);
    QDomElement serializeVideoTrack(VideoTrackType *);
    QDomElement serializeAspectRatio(AspectRatioType *);
    QDomElement serializeCaptioningFormat(CaptioningFormatType *);
    QDomElement serializeAncillarityDataFormat(AncillarityDataFormatType *);
    QDomElement serializeDetails(DetailsType *);
    QDomElement serializeAddress(AddressType *);
    QDomElement serializeOrganisationDetails(OrganisationDetailsType *);
    QDomElement serializeElement(ElementType *);
    QDomElement serializeRelation(RelationType *);
    QDomElement serializeIdentifier(IdentifierType *);
    QDomElement serializeSigningFormat(SigningFormatType *);
    QDomElement serializeTitle(TitleType *);
    QDomElement serializeAlternativeTitle(AlternativeTitleType *);
    QDomElement serializeSubject(SubjectType *);
    QDomElement serializeDate(DateType *);
    QDomElement serializeType(TypeType *);
    QDomElement serializeFormat(FormatType *);
    QDomElement serializeLanguage(LanguageType *);
    QDomElement serializeHasTrackPart(HasTrackPartType *);
    QDomElement serializeCoverage(CoverageType *);
    QDomElement serializeRights(RightsType *);
    QDomElement serializePublicationHistory(PublicationHistoryType *);
    QDomElement serializeRating(RatingType *);
    QDomElement serializePart(PartType *);
    QDomElement serializeDescription(DescriptionType *);
    QDomElement serializeLength(LengthType *);
    QDomElement serializeAudioFormat(AudioFormatType *);
    QDomElement serializeDataFormat(DataFormatType *);
    QDomElement serializeImageFormat(ImageFormatType *);
    QDomElement serializeVideoFormat(VideoFormatType *);
    QDomElement serializeString(String *);
    QDomElement serializeInt8(Int8 *);
    QDomElement serializeInt16(Int16 *);
    QDomElement serializeInt32(Int32 *);
    QDomElement serializeInt64(Int64 *);
    QDomElement serializeUInt8(UInt8 *);
    QDomElement serializeUInt16(UInt16 *);
    QDomElement serializeUInt32(UInt32 *);
    QDomElement serializeUInt64(UInt64 *);
    QDomElement serializeBoolean(Boolean *);
    QDomElement serializeFloat(Float *);
    QDomElement serializeTechnicalAttributeRational(TechnicalAttributeRationalType *);
    QDomElement serializeTechnicalAttributeUri(TechnicalAttributeUriType *);

    void serializeTypeGroup(TypeGroup *, QDomElement *);
    void serializeDateGroup(DateGroup *, QDomElement *);
    void serializeFormatGroup(FormatGroup *, QDomElement *);
    void serializeStatusGroup(StatusGroup *, QDomElement *);
    void serializeTechnicalAttributes(TechnicalAttributes *, QDomElement *);

    EbuCoreMainType *m_root;
    QDomDocument m_doc;
    QString m_errorMsg;
};

#endif // EBUSERIALIZER_H
