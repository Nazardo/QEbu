#include "ebucoremainform.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QtGui>

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
