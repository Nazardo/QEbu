/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#ifndef EBUPARSER_H
#define EBUPARSER_H

#include <QFile>
#include <QtXml/QDomElement>
#include <QString>
#include "../model/ebucoremaintype.h"

class EbuParser
{
public:
    EbuParser();
    bool parseFromFile(QFile &file);
    QString errorMsg();
    EbuCoreMainType *root();

private:
    CoreMetadataType *parseCoreMetadataType(CoreMetadataType *coreMetadata, const QDomElement &element);
    AlternativeType *parseAlternativeType(const QDomElement &element);
    TechnicalAttributes *parseTechnicalAttributes(const QDomElement &element);
    AudioTrackType *parseAudioTrackType(const QDomElement &element);
    DocumentFormatType *parseDocumentFormatType(const QDomElement &element);
    TimeType *parseTimeType(const QDomElement &element);
    DurationType *parseDurationType(const QDomElement &element);
    TemporalType *parseTemporalType(const QDomElement &element);
    LocationType *parseLocationType(const QDomElement &element);
    CoordinatesType *parseCoordinatesType(const QDomElement &element);
    EntityType *parseEntityType(const QDomElement &element);
    ContactDetailsType *parseContactDetailsType(const QDomElement &element);
    VideoTrackType *parseVideoTrackType(const QDomElement &element);
    AspectRatioType *parseAspectRatioType(const QDomElement &element);
    CaptioningFormatType *parseCaptioningFormatType(const QDomElement &element);
    AncillaryDataFormatType *parseAncillaryDataFormatType(const QDomElement &element);
    DetailsType *parseDetailsType(const QDomElement &element);
    AddressType *parseAddressType(const QDomElement &element);
    OrganisationDetailsType *parseOrganisationDetailsType(const QDomElement &element);
    ElementType *parseElementType(const QDomElement &element);
    RelationType *parseRelationType(const QDomElement &element);
    RelationType *parseRelationType(RelationType *relation, const QDomElement &element);
    IdentifierType *parseIdentifierType(const QDomElement &element);
    SigningFormatType *parseSigningFormatType(const QDomElement &element);
    TitleType *parseTitleType(const QDomElement &element);
    AlternativeTitleType *parseAlternativeTitleType(const QDomElement &element);
    SubjectType *parseSubjectType(const QDomElement &element);
    DateType *parseDateType(const QDomElement &element);
    TypeType *parseTypeType(const QDomElement &element);
    FormatType *parseFormatType(const QDomElement &element);
    LanguageType *parseLanguageType(const QDomElement &element);
    HasTrackPartType *parseHasTrackPartType(const QDomElement &element);
    CoverageType *parseCoverageType(const QDomElement &element);
    RightsType *parseRightsType(const QDomElement &element);
    PublicationHistoryType *parsePublicationHistoryType(const QDomElement &element);
    RatingType *parseRatingType(const QDomElement &element);
    PartType *parsePartType(const QDomElement &element);
    DescriptionType *parseDescriptionType(const QDomElement &element);
    LengthType *parseLengthType(const QDomElement &element);
    AudioFormatType *parseAudioFormatType(const QDomElement &element);
    DataFormatType *parseDataFormatType(const QDomElement &element);
    ImageFormatType *parseImageFormatType(const QDomElement &element);
    VideoFormatType *parseVideoFormatType(const QDomElement &element);
    String *parseString(const QDomElement &element);
    Int8 *parseInt8(const QDomElement &element);
    Int16 *parseInt16(const QDomElement &element);
    Int32 *parseInt32(const QDomElement &element);
    Int64 *parseInt64(const QDomElement &element);
    UInt8 *parseUInt8(const QDomElement &element);
    UInt16 *parseUInt16(const QDomElement &element);
    UInt32 *parseUInt32(const QDomElement &element);
    UInt64 *parseUInt64(const QDomElement &element);
    Boolean *parseBoolean(const QDomElement &element);
    Float *parseFloat(const QDomElement &element);
    TechnicalAttributeRationalType *parseTechnicalAttributeRationalType(const QDomElement &element);
    TechnicalAttributeUriType *parseTechnicalAttributeUriType(const QDomElement &element);
    void parseTypeGroup(const QDomElement &element, TypeGroup* const typeGroup);
    void parseStatusGroup(const QDomElement &element, StatusGroup* const statusGroup);
    void parseFormatGroup(const QDomElement &element, FormatGroup* const formatGroup);
    void parseDateGroup(const QDomElement &element, DateGroup* const dateGroup);


    EbuCoreMainType *m_root;
    QString m_errorMsg;
};

#endif // EBUPARSER_H
