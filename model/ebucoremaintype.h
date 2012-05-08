#ifndef EBUCOREMAINTYPE_H
#define EBUCOREMAINTYPE_H

#include <QDate>
#include "coremetadatatype.h"
#include "entitytype.h"

class EbuCoreMainType
{
public:
    EbuCoreMainType();
    // Attributes
    QDate dateLastModified() const;
    void setDateLastModified(const QDate &dateLastModified);
    QString documentId() const;
    void setDocumentId(const QString &documentId);
    QString lang() const;
    void setLang(const QString &lang);
    // Elements
    CoreMetadataType *coreMetadata() const;
    void setCoreMetadata(CoreMetadataType *coreMetadata);
    EntityType *metadataProvider() const;
    void setMetadataProvider(EntityType *metadataProvider);
private:
    // Attributes
    QDate m_dateLastModified;
    QString m_documentId;
    QString m_lang;
    // Elements
    CoreMetadataType *m_coreMetadata; // (required)
    EntityType *m_metadataProvider; // (optional)
};

#endif // EBUCOREMAINTYPE_H
