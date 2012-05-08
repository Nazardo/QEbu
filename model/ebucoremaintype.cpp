#include "ebucoremaintype.h"

EbuCoreMainType::EbuCoreMainType()
{
    m_lang = "en";
    m_coreMetadata = new CoreMetadataType();
    m_metadataProvider = 0;
}

QDateTime EbuCoreMainType::dateLastModified() const
{
    return m_dateLastModified;
}

void EbuCoreMainType::setDateLastModified(const QDateTime &dateLastModified)
{
    m_dateLastModified = dateLastModified;
}

QString EbuCoreMainType::documentId() const
{
    return m_documentId;
}

void EbuCoreMainType::setDocumentId(const QString &documentId)
{
    m_documentId = documentId;
}

QString EbuCoreMainType::lang() const
{
    return m_lang;
}

void EbuCoreMainType::setLang(const QString &lang)
{
    m_lang = lang;
}

CoreMetadataType *EbuCoreMainType::coreMetadata() const
{
    return m_coreMetadata;
}

void EbuCoreMainType::setCoreMetadata(CoreMetadataType *coreMetadata)
{
    m_coreMetadata = coreMetadata;
}

EntityType *EbuCoreMainType::metadataProvider() const
{
    return m_metadataProvider;
}

void EbuCoreMainType::setMetadataProvider(EntityType *metadataProvider)
{
    m_metadataProvider = metadataProvider;
}
