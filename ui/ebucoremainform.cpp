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

#include "ebucoremainform.h"
#include "../model/ebucoremaintype.h"
#include "coremetadatatypeform.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QTextBrowser>

EbuCoreMainForm::EbuCoreMainForm(EbuCoreMainType *ebuCoreMain,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
    StackableWidget(mainWindow, parent, DocText)
{
    m_ebuCoreMain = ebuCoreMain;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;

        m_editSchema = new QLineEdit;
        QLabel *schema = new QLabel(tr("Schema"));
        gl->addWidget(schema, 0, 0, 1, 1);
        gl->addWidget(m_editSchema, 0, 1, 1, 3);
        m_editSchema->setReadOnly(true);

        m_editVersion = new QLineEdit;
        QLabel *version = new QLabel(tr("Version"));
        gl->addWidget(version, 1, 0, 1, 1);
        gl->addWidget(m_editVersion, 1, 1, 1, 3);
        m_editVersion->setReadOnly(true);

        m_editDateLastModified = new QDateEdit;
        m_editDateLastModified->setCalendarPopup(true);
        m_checkDateLastModified = new QCheckBox(tr("Date Last Modified"));
        QObject::connect(m_editDateLastModified, SIGNAL(dateChanged(QDate)),
                         this, SLOT(dateLastModifiedChanged()));
        QObject::connect(m_checkDateLastModified, SIGNAL(toggled(bool)),
                         this, SLOT(dateLastModifiedToggled(bool)));
        gl->addWidget(m_checkDateLastModified, 2, 0, 1, 1);
        gl->addWidget(m_editDateLastModified, 2, 1, 1, 3);

        m_editDocumentId = new QLineEdit;
        QLabel *id = new QLabel(tr("Document ID"));
        gl->addWidget(id, 3, 0, 1, 1);
        gl->addWidget(m_editDocumentId, 3, 1, 1, 3);
        QObject::connect(m_editDocumentId, SIGNAL(textEdited(QString)),
                         this, SLOT(documentIdChanged(QString)));

        m_editLang = new QLineEdit;
        QLabel *lang = new QLabel(tr("Language"));
        gl->addWidget(lang, 4, 0, 1, 1);
        gl->addWidget(m_editLang, 4, 1, 1, 3);
        QObject::connect(m_editLang, SIGNAL(textEdited(QString)),
                         this, SLOT(langChanged(QString)));

        vl->addLayout(gl);
    }
    {
        QGridLayout *gl = new QGridLayout;
        gl->addWidget(new QLabel(tr("CoreMetadata")), 0, 0);
        m_editCoreMetadata = new QLineEdit;
        m_editCoreMetadata->setReadOnly(true);
        gl->addWidget(m_editCoreMetadata, 0, 1);
        QPushButton *buttonCoreMetadata = new QPushButton(tr("Edit"));
        QObject::connect(buttonCoreMetadata, SIGNAL(clicked()),
                         this, SLOT(coreMetadataClicked()));
        gl->addWidget(buttonCoreMetadata, 0, 2);

        gl->addWidget(new QLabel(tr("Metadata Provider")), 1, 0);
        m_editMetadataProvider = new QLineEdit;
        m_editMetadataProvider->setReadOnly(true);
        gl->addWidget(m_editMetadataProvider, 1, 1);
        QPushButton *buttonMetadataProvider = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonMetadataProvider, SIGNAL(clicked()),
                         this, SLOT(metadataProviderClicked()));
        gl->addWidget(buttonMetadataProvider, 1, 2);
        QPushButton *buttonMetadataProviderRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonMetadataProviderRemove, SIGNAL(clicked()),
                         this, SLOT(metadataProviderRemoveClicked()));
        gl->addWidget(buttonMetadataProviderRemove, 1, 3);
        vl->addLayout(gl);
    }

    this->setLayout(vl);

    // Install Events filters
    m_textDocumentation->setText(tr("EbuCoreMain is the root of a document using the EBU Core metadata set."));
    m_editSchema->installEventFilter(this);
    m_editVersion->installEventFilter(this);
    m_editDateLastModified->installEventFilter(this);
    m_editDocumentId->installEventFilter(this);
    m_editLang->installEventFilter(this);
    m_editCoreMetadata->installEventFilter(this);
    m_editMetadataProvider->installEventFilter(this);

    // Set text fields...
    m_editSchema->setText(m_ebuCoreMain->schema());
    m_editVersion->setText(m_ebuCoreMain->version());
    m_editDocumentId->setText(m_ebuCoreMain->documentId());
    if (m_ebuCoreMain->dateLastModified().isValid()) {
        m_editDateLastModified->setDate(m_ebuCoreMain->dateLastModified().date());
        m_checkDateLastModified->setChecked(true);
    }
    m_editLang->setText(m_ebuCoreMain->lang());
    if (m_ebuCoreMain->coreMetadata()) {
        m_editCoreMetadata->setText("CoreMetadata");
    }
    if (m_ebuCoreMain->metadataProvider()) {
        m_editMetadataProvider->setText(m_ebuCoreMain->metadataProvider()->toString());
    }
}


QString EbuCoreMainForm::toString()
{
    return QString(tr("EbuCoreMain"));
}

void EbuCoreMainForm::coreMetadataRemoveClicked()
{
    if (!m_ebuCoreMain->coreMetadata())
        return;
    m_ebuCoreMain->setCoreMetadata(0);
    m_editCoreMetadata->setText(tr("(none)"));
}

void EbuCoreMainForm::coreMetadataClicked()
{
    CoreMetadataTypeForm *coreMetadataForm = new CoreMetadataTypeForm(
                m_ebuCoreMain->coreMetadata(), this->mainWindow());
    QObject::connect(coreMetadataForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(coreMetadataClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(coreMetadataForm);
}

void EbuCoreMainForm::coreMetadataClosed(Operation op, QVariant value)
{
    CoreMetadataType *coreMetadata = QVarPtr<CoreMetadataType>::asPointer(value);
    if (!coreMetadata)
        return;
    if (op == Add)
        m_ebuCoreMain->setCoreMetadata(coreMetadata);
    m_editCoreMetadata->setText("CoreMetadata");
}

void EbuCoreMainForm::dateLastModifiedChanged()
{
    if (m_checkDateLastModified->isChecked())
        m_ebuCoreMain->setDateLastModified(m_editDateLastModified->dateTime());
    else
        m_checkDateLastModified->setChecked(true);
}

void EbuCoreMainForm::dateLastModifiedToggled(bool checked)
{
    if (checked)
        m_ebuCoreMain->setDateLastModified(m_editDateLastModified->dateTime());
    else
        m_ebuCoreMain->setDateLastModified(QDateTime());
}

void EbuCoreMainForm::documentIdChanged(QString documentId)
{
    m_ebuCoreMain->setDocumentId(documentId);
}

void EbuCoreMainForm::langChanged(QString lang)
{
    m_ebuCoreMain->setLang(lang);
}

bool EbuCoreMainForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editSchema)
            m_textDocumentation->setText(tr("The name of the schema."));
        else if (obj == (QObject*) m_editVersion)
            m_textDocumentation->setText(tr("The version of the schema."));
        else if (obj == (QObject*) m_editDateLastModified)
            m_textDocumentation->setText(tr("The date of edition of the metadata instance."));
        else if (obj == (QObject*) m_editDocumentId)
            m_textDocumentation->setText(tr("The unique Identifier of the metadata instance."));
        else if (obj == (QObject*) m_editLang)
            m_textDocumentation->setText(tr("An attribute to specify the dominant language used to express"
                                            "metadata information in the document, which can be superceded each time an"
                                            "language attribute or element is available at a different level of description"
                                            "granularity."));
        else if (obj == (QObject*) m_editCoreMetadata)
            m_textDocumentation->setText(tr("The body of ebucore descriptive metadata."));
        else if (obj == (QObject*) m_editMetadataProvider)
            m_textDocumentation->setText(tr("Identifies the metadata provider, e.g. the contributing archive."
                                            "The organisation Id or name provide the archive ID or name required for e.g."
                                            "OAI metadata harvesting operation."));
    }
    return QObject::eventFilter(obj, event);
}

void EbuCoreMainForm::metadataProviderRemoveClicked()
{
    if (!m_ebuCoreMain->metadataProvider())
        return;
    m_ebuCoreMain->setMetadataProvider(0);
    m_editMetadataProvider->setText(tr("(none)"));
}

void EbuCoreMainForm::metadataProviderClicked()
{
    EntityTypeForm *metadataProviderForm = new EntityTypeForm(
                m_ebuCoreMain->metadataProvider(),this->mainWindow());
    metadataProviderForm->setTitle(tr("Metadata Provider"));
    QObject::connect(metadataProviderForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(metadataProviderClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(metadataProviderForm);
}

void EbuCoreMainForm::metadataProviderClosed(Operation op, QVariant value)
{
    EntityType *entityType = QVarPtr<EntityType>::asPointer(value);
    if (!entityType)
        return;
    if (op == Add)
        m_ebuCoreMain->setMetadataProvider(entityType);
    m_editMetadataProvider->setText(entityType->toString());
}

