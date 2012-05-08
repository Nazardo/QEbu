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
    void parseTypeGroup(const QDomElement &element, TypeGroup* const typeGroup);
    EbuCoreMainType *m_root;
    QString m_errorMsg;
};

#endif // EBUPARSER_H
