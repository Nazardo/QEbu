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

EbuCoreMainForm::EbuCoreMainForm(EbuCoreMainType *ebuCoreMain,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
    StackableWidget(mainWindow, parent, None)
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
        m_editSchema->setReadOnly(true);

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
        QPushButton *buttonCoreMetadata = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonCoreMetadata, SIGNAL(clicked()),
                         this, SLOT(coreMetadataClicked()));
        gl->addWidget(buttonCoreMetadata, 0, 2);
        QPushButton *buttonCoreMetadataRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonCoreMetadataRemove, SIGNAL(clicked()),
                         this, SLOT(coreMetadataRemoveClicked()));
        gl->addWidget(buttonCoreMetadataRemove, 0, 3);

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

