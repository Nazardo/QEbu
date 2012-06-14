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
