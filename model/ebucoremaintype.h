#ifndef EBUCOREMAINTYPE_H
#define EBUCOREMAINTYPE_H

#include <QDateTime>
#include "coremetadatatype.h"
#include "entitytype.h"

class EbuCoreMainType
{
public:
    EbuCoreMainType();
    // Attributes
    QDateTime dateLastModified() const;
    void setDateLastModified(const QDateTime &dateLastModified);
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
    QDateTime m_dateLastModified;
    QString m_documentId;
    QString m_lang;
    // Elements
    CoreMetadataType *m_coreMetadata; // (required)
    EntityType *m_metadataProvider; // (optional)
};

#endif // EBUCOREMAINTYPE_H
