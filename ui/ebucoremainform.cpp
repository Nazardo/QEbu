#include "ebucoremainform.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QtGui>

// just for test
#include "timetypeform.h"
#include "publicationhistorytypeform.h"
#include "relationtypeform.h"
#include "stringform.h"
#include "booleanform.h"
#include "technicalattributerationaltypeform.h"
#include "technicalattributeuritypeform.h"
#include "floatform.h"
#include "dategroupform.h"
#include "../model/qebulimits.h"

EbuCoreMainForm::EbuCoreMainForm(EbuCoreMainType *ebuCoreMain, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_ebuCoreMain = ebuCoreMain;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Metadata Provider")));
        m_editMetadataProvider = new QLineEdit;
        m_editMetadataProvider->setEnabled(false);
        hl->addWidget(m_editMetadataProvider);
        QPushButton *buttonMetadataProvider = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonMetadataProvider, SIGNAL(clicked()),
                         this, SLOT(metadataProviderClicked()));
        hl->addWidget(buttonMetadataProvider);
        QPushButton *buttonMetadataProviderRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonMetadataProviderRemove, SIGNAL(clicked()),
                         this, SLOT(metadataProviderRemoveClicked()));
        hl->addWidget(buttonMetadataProviderRemove);

        // TEST JUNK

        QPushButton *buttonTest = new QPushButton("TEST");
        QObject::connect(buttonTest, SIGNAL(clicked()), this, SLOT(testClicked()));
        hl->addWidget(buttonTest);

        // EOT

        vl->addLayout(hl);
    }
    this->setLayout(vl);
    // Set text fields...
    if (m_ebuCoreMain->metadataProvider()) {
        m_editMetadataProvider->setText(m_ebuCoreMain->metadataProvider()->toString());
    }
}


QString EbuCoreMainForm::toString()
{
    return QString(tr("EbuCoreMain"));
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

void EbuCoreMainForm::testClicked()
{
    // TEST PURPOSES!
    qEbuLimits::getMaxInt8();
    DateGroupForm *ttf = new DateGroupForm(0, this->mainWindow());
    this->mainWindow()->pushWidget(ttf);
}
