#include "identifiertypeform.h"
#include "../model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "formatgroupeditbox.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include "entitytypeform.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>

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
        m_editTypeGroup = new TypeGroupEditBox(identifier);
        vl->addWidget(m_editTypeGroup);
        m_editFormatGroup = new FormatGroupEditBox(identifier);
        m_editFormatGroup->addLinksMap(mainWindow->getMap("ebu_IdentifierTypeCodeCS"));
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
        m_editAttributor->setReadOnly(true);
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
    this->setLayout(vl);
    // Set text fields...
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
    return QString(tr("Identifier"));
}

bool IdentifierTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_editElementIdentifier->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Identifier");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
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
    if (!checkCompliance())
        return;
    EntityTypeForm *attributorForm = new EntityTypeForm(
                m_identifier->attributor(),this->mainWindow());
    attributorForm->setTitle(tr("Attributor"));
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
    m_identifier->setNote(m_textNote->toPlainText());
    m_editTypeGroup->updateExistingTypeGroup(m_identifier);
    m_editFormatGroup->updateExistingFormatGroup(m_identifier);
    m_identifier->setIdentifier(new ElementType(
                                m_editElementIdentifier->editValue()->text(),
                                m_editElementIdentifier->editLang()->text()));
    emit closed(m_op, QVarPtr<IdentifierType>::asQVariant(m_identifier));
}
