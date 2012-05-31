#include "relationtypeform.h"
#include "qvarptr.h"
#include "typegroupform.h"
#include "identifiertypeform.h"
#include <QtGui>

RelationTypeForm::RelationTypeForm(RelationType *relation, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (relation) ? Edit : Add;
    if (!relation)
		m_relation = new RelationType;
	else
		m_relation = relation;
		
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(relation);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QGridLayout *gl = new QGridLayout;
        m_spinRunningOrderNumber = new QSpinBox;
        m_checkRunningOrderNumber = new QCheckBox(tr("Value"));
        QObject::connect(m_spinRunningOrderNumber, SIGNAL(valueChanged(int)),
                         this, SLOT(runningOrderNumberChanged()));
        gl->addWidget(m_checkRunningOrderNumber, 0, 0);
        gl->addWidget(m_spinRunningOrderNumber, 0, 1);
        vl->addLayout(gl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_spinRunningOrderNumber = new QSpinBox;
        fl->addRow(tr("Order number"), m_spinRunningOrderNumber);
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    {
        m_editElementRelation = new ElementTypeEditBox;
        m_editElementRelation->setLabel(tr("Relation"));
        vl->addWidget(m_editElementRelation);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_editRelationLink = new QLineEdit;
        fl->addRow(tr("Relation link"), m_editRelationLink);
        vl->addLayout(fl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Relation Identifier")));
        m_editRelationIdentifier = new QLineEdit;
        m_editRelationIdentifier->setEnabled(false);
        hl->addWidget(m_editRelationIdentifier);
        QPushButton *buttonRelationIdentifierAdd = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonRelationIdentifierAdd, SIGNAL(clicked()),
                         this, SLOT(relationIdentifierClicked()));
        hl->addWidget(buttonRelationIdentifierAdd);
        QPushButton *buttonRelationIdentifierRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonRelationIdentifierRemove, SIGNAL(clicked()),
                         this, SLOT(relationIdentifierRemoveClicked()));
        hl->addWidget(buttonRelationIdentifierRemove);
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
    if (m_relation->runningOrderNumber()) {
        m_spinRunningOrderNumber->setValue(*(m_relation->runningOrderNumber()));
        m_checkRunningOrderNumber->setChecked(true);
    }
    m_textNote->setText(m_relation->note());
    if (m_relation->relation()) {
        m_editElementRelation->editLang()->setText(m_relation->relation()->lang());
        m_editElementRelation->editValue()->setText(m_relation->relation()->value());
    }
    m_editRelationLink->setText(m_relation->relationLink());
    if (m_relation->relationIdentifier()) {
        m_editRelationIdentifier->setText(m_relation->relationIdentifier()->toString());
    }
}

QString RelationTypeForm::toString()
{
    return QString(tr("Relation Type"));
}

void RelationTypeForm::relationIdentifierRemoveClicked()
{
    if (!m_relation->relationIdentifier())
        return;
    m_relation->setRelationIdentifier(0);
    m_editRelationIdentifier->setText(tr("(none)"));
}

void RelationTypeForm::relationIdentifierClicked()
{
    IdentifierTypeForm *identifierTypeForm = new IdentifierTypeForm(
                m_relation->relationIdentifier(),this->mainWindow());
    QObject::connect(identifierTypeForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(relationIdentifierClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(identifierTypeForm);
}

void RelationTypeForm::relationIdentifierClosed(Operation op, QVariant value)
{
    IdentifierType *identifier = QVarPtr<IdentifierType>::asPointer(value);
    if (!identifier)
        return;
    if (op == Add)
        m_relation->setRelationIdentifier(identifier);
    m_editRelationIdentifier->setText(identifier->toString());
}

void RelationTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_relation;
        m_relation = 0;
    }
    emit closed(m_op, QVarPtr<RelationType>::asQVariant(m_relation));
}

void RelationTypeForm::applyClicked()
{
    if(!checkCompliance())
        return;
    m_relation->setNote(m_textNote->toPlainText());

    m_editTypeGroup->updateExistingTypeGroup(m_relation);
    if (m_checkRunningOrderNumber->isChecked())
        m_relation->setRunningOrderNumber(m_spinRunningOrderNumber->value());
    m_relation->setRelation(new ElementType(
                                m_editElementRelation->editValue()->text(),
                                m_editElementRelation->editLang()->text()));
    m_relation->setRelationLink(m_editRelationLink->text());
    emit closed(m_op, QVarPtr<RelationType>::asQVariant(m_relation));
}

void RelationTypeForm::runningOrderNumberChanged()
{
    m_checkRunningOrderNumber->setChecked(true);
}

bool RelationTypeForm::checkCompliance()
{
    bool ok = true;
    return ok;
}
