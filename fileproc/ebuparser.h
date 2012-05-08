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
private:
    CoreMetadataType *parseCoreMetadataType(const QDomElement &element);
    EntityType *parseEntityType(const QDomElement &element);
    ContactDetailsType *parseContactDetailsType(const QDomElement &element);
    DetailsType *parseDetailsType(const QDomElement &element);
    AddressType *parseAddressType(const QDomElement &element);
    OrganisationDetailsType *parseOrganisationDetailsType(const QDomElement &element);
    ElementType *parseElementType(const QDomElement &element);
    RelationType *parseRelationType(const QDomElement &element);
    IdentifierType *parseIdentifierType(const QDomElement &element);
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
    void parseTypeGroup(const QDomElement &element, TypeGroup* const typeGroup);
    void parseStatusGroup(const QDomElement &element, StatusGroup* const statusGroup);
    void parseFormatGroup(const QDomElement &element, FormatGroup* const formatGroup);
    void parseDateGroup(const QDomElement &element, DateGroup* const dateGroup);


    EbuCoreMainType *m_root;
    QString m_errorMsg;
};

#endif // EBUPARSER_H
