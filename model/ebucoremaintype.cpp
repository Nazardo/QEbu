#include "ebucoremaintype.h"
#include "formatupdatelistener.h"

const QString EbuCoreMainType::SCHEMA = "EBU_CORE_20110531.xsd";
const QString EbuCoreMainType::VERSION = "1.3";

EbuCoreMainType::EbuCoreMainType()
{
    m_lang = "en";
    m_coreMetadata = new CoreMetadataType();
    m_metadataProvider = 0;
}

EbuCoreMainType::~EbuCoreMainType()
{
    delete m_coreMetadata;
    delete m_metadataProvider;
}

QString EbuCoreMainType::schema() const
{
    return SCHEMA;
}

QString EbuCoreMainType::version() const
{
    return VERSION;
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
    if (coreMetadata != m_coreMetadata)
        delete m_coreMetadata;
    m_coreMetadata = coreMetadata;
    // CoreMetadata is mandatory, should never be null
    if (!m_coreMetadata)
        m_coreMetadata = new CoreMetadataType;
}

EntityType *EbuCoreMainType::metadataProvider() const
{
    return m_metadataProvider;
}

void EbuCoreMainType::setMetadataProvider(EntityType *metadataProvider)
{
    if (metadataProvider != m_metadataProvider)
        delete m_metadataProvider;
    m_metadataProvider = metadataProvider;
}

QString EbuCoreMainType::toString() const
{
    if (m_documentId.isEmpty())
        return QObject::tr("Unnamed document");
    return m_documentId;
}

QStringList EbuCoreMainType::formatIdRefs() const
{
    return QStringList(m_formatMap.keys());
}

bool EbuCoreMainType::addFormat(const FormatType *format)
{
    if (!format || format->formatId().isEmpty())
        return false;
    if (m_formatMap.contains(format->formatId()))
        return false;
    m_formatMap.insert(format->formatId(), new FormatMapEntry(format));
    return true;
}

bool EbuCoreMainType::updateFormatId(const QString &oldId, const QString &newId, const FormatType *format)
{
    bool newIdEmpty = newId.isEmpty();
    bool oldIdEmpty = oldId.isEmpty();
    if (newIdEmpty && oldIdEmpty)
        return true;

    if (newIdEmpty && !oldIdEmpty) {
        // The format has no longer an Id, we should remove it from the map.
        removeFormat(oldId);
        return true;
    }
    if (!newIdEmpty && oldIdEmpty) {
        // The format had no Id, but now it has one: we should try to insert it in the map.
        return addFormat(format);
    }
    if (!newIdEmpty && !oldIdEmpty && newId != oldId) {
        // The format had an Id and it has changed: we should update the map.
        if (m_formatMap.contains(newId))
            return false;
        FormatMapEntry *entry = m_formatMap.take(oldId);
        if (!entry)
            return false; // Impossible, but better safe than SIGSEG
        m_formatMap.insert(newId, entry);
    }
    return true;
}

bool EbuCoreMainType::removeFormat(const QString &formatId)
{
    if (formatId.isEmpty() || !m_formatMap.contains(formatId))
        return false;
    FormatMapEntry *entry = m_formatMap.take(formatId);
    // Iterate on all listeners
    foreach (FormatUpdateListener *listener, entry->listeners)
        listener->onFormatDelete(formatId);
    entry->listeners.clear();
    entry->formatPointer = 0;
    delete entry;
    return true;
}

void EbuCoreMainType::unlinkListener(const QString &formatId, FormatUpdateListener *listener)
{
    if (formatId.isEmpty() || !listener)
        return;
    FormatMapEntry *entry = m_formatMap.value(formatId, 0);
    if (entry) {
        entry->listeners.removeOne(listener);
    }
}

const FormatType *EbuCoreMainType::formatById(const QString &formatId, FormatUpdateListener *listener)
{
    FormatMapEntry *mapEntry = m_formatMap.value(formatId, 0);
    if (!mapEntry)
        return 0; // null is returned when no format is found with such Id
    if (listener)
        mapEntry->listeners.append(listener);
    return mapEntry->formatPointer;
}
