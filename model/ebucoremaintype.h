#ifndef EBUCOREMAINTYPE_H
#define EBUCOREMAINTYPE_H

#include <QDateTime>
#include <QList>
#include <QStringList>
#include <QMap>
#include "coremetadatatype.h"
#include "entitytype.h"

class FormatUpdateListener;

class EbuCoreMainType
{
public:
    EbuCoreMainType();
    ~EbuCoreMainType();
    // Attributes
    QString schema() const;
    QString version() const;
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
    QString toString() const;
    // Global format collection access and management
    QStringList formatIdRefs() const;
    bool addFormat(const FormatType *format);
    bool updateFormatId(const QString &oldId, const QString &newId, const FormatType *format);
    bool removeFormat(const QString &formatId);
    void unlinkListener(const QString &formatId, FormatUpdateListener *listener);
    const FormatType *formatById(const QString &formatId, FormatUpdateListener *listener = 0);
private:
    static const QString SCHEMA;
    static const QString VERSION;
    // Attributes
    QDateTime m_dateLastModified;
    QString m_documentId;
    QString m_lang;
    // Elements
    CoreMetadataType *m_coreMetadata; // (required)
    EntityType *m_metadataProvider; // (optional)
    // FormatMap
    struct FormatMapEntry {
        FormatMapEntry(const FormatType *formatPointer) {
            this->formatPointer = formatPointer;
        }
        const FormatType *formatPointer;
        QList<FormatUpdateListener*> listeners;
    };
    QMap<QString, FormatMapEntry*> m_formatMap;
};

#endif // EBUCOREMAINTYPE_H
