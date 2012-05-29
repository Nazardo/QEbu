#include "identifiertypeform.h"
#include "qvarptr.h"
#include "entitytypeform.h"
#include <QtGui>

IdentifierTypeForm::IdentifierTypeForm(IdentifierType *identifier, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (identifier) ? Edit : Add;
    if (!identifier)
        m_identifier = new IdentifierType;
    else
        m_identifier = identifier;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox;
        vl->addWidget(m_editTypeGroup);
        m_editFormatGroup = new FormatGroupEditBox;
        vl->addWidget(m_editFormatGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    {
        m_editElementIdentifier = new ElementTypeEditBox;
        m_editElementIdentifier->setLabel(tr("Identifier"));
        vl->addWidget(m_editElementIdentifier);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Attributor")));
        m_editAttributor = new QLineEdit;
        m_editAttributor->setEnabled(false);
        hl->addWidget(m_editAttributor);
        QPushButton *buttomAttributorAdd = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttomAttributorAdd, SIGNAL(clicked()),
                         this, SLOT(attributorClicked()));
        hl->addWidget(buttomAttributorAdd);
        QPushButton *buttonAttributorRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonAttributorRemove, SIGNAL(clicked()),
                         this, SLOT(attributorRemoveClicked()));
        hl->addWidget(buttonAttributorRemove);
        vl->addLayout(hl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        QPushButton *buttonClose = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        QObject::connect(buttonClose, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        hl->addWidget(buttonClose);
        hl->addWidget(buttonCancel);
        vl->addLayout(hl);
    }
    this->setLayout(vl);
    // Set text fields...
    m_editTypeGroup->typeDefinition()->setText(m_identifier->typeDefinition());
    m_editTypeGroup->typeLabel()->setText(m_identifier->typeLabel());
    m_editTypeGroup->typeLink()->setText(m_identifier->typeLink());
    m_editFormatGroup->formatDefinition()->setText(m_identifier->formatDefinition());
    m_editFormatGroup->formatLabel()->setText(m_identifier->formatLabel());
    m_editFormatGroup->formatLink()->setText(m_identifier->formatLink());
    m_textNote->setText(m_identifier->note());
    if (m_identifier->identifier()) {
        m_editElementIdentifier->editLang()->setText(m_identifier->identifier()->lang());
        m_editElementIdentifier->editValue()->setText(m_identifier->identifier()->value());
    }
    if (m_identifier->attributor()) {
        m_editAttributor->setText(m_identifier->attributor()->toString());
    }
}

QString IdentifierTypeForm::toString()
{
    return QString(tr("Identifier Type"));
}

void IdentifierTypeForm::attributorRemoveClicked()
{
    if (!m_identifier->attributor())
        return;
    m_identifier->setAttributor(0);
    m_editAttributor->setText(tr("(none)"));
}

void IdentifierTypeForm::attributorClicked()
{
    EntityTypeForm *attributorForm = new EntityTypeForm(
                m_identifier->attributor(),this->mainWindow());
    QObject::connect(attributorForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(attributorClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(attributorForm);
}

void IdentifierTypeForm::attributorClosed(Operation op, QVariant value)
{
    EntityType *attributor = QVarPtr<EntityType>::asPointer(value);
    if (!attributor)
        return;
    if (op == Add)
        m_identifier->setAttributor(attributor);
    m_editAttributor->setText(attributor->toString());
}

void IdentifierTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_identifier;
        m_identifier = 0;
    }
    emit closed(m_op, QVarPtr<IdentifierType>::asQVariant(m_identifier));
}

void IdentifierTypeForm::applyClicked()
{
    if(!checkCompliance())
        return;
    m_identifier->setNote(m_textNote->toPlainText());
    m_identifier->setTypeDefinition(m_editTypeGroup->typeDefinition()->text());
    m_identifier->setTypeLabel(m_editTypeGroup->typeLabel()->text());
    m_identifier->setTypeLink(m_editTypeGroup->typeLink()->text());
    m_identifier->setFormatDefinition(m_editFormatGroup->formatDefinition()->text());
    m_identifier->setFormatLabel(m_editFormatGroup->formatLabel()->text());
    m_identifier->setFormatLink(m_editFormatGroup->formatLink()->text());
    m_identifier->setIdentifier(new ElementType(
                                m_editElementIdentifier->editValue()->text(),
                                m_editElementIdentifier->editLang()->text()));
    emit closed(m_op, QVarPtr<IdentifierType>::asQVariant(m_identifier));
}

bool IdentifierTypeForm::checkCompliance()
{
    bool ok = true;
    return ok;
}
