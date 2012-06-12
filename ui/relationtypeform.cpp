#include "relationtypeform.h"
#include "../model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include "typegroupform.h"
#include "identifiertypeform.h"
#include "../model/qebulimits.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QEvent>
#include <QComboBox>

RelationTypeForm::RelationTypeForm(RelationType *relation,
                                   QEbuMainWindow *mainWindow,
                                   QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (relation) ? Edit : Add;
    if (!relation)
		m_relation = new RelationType;
	else
		m_relation = relation;
		
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editElementRelation = new ElementTypeEditBox;
        m_editElementRelation->setLabel(tr("Relation"));
        vl->addWidget(m_editElementRelation);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(relation);
        m_editTypeGroup->addLinksMap(mainWindow->getMap("tva_HowRelatedCS"));
        m_editTypeGroup->addLinksMap(mainWindow->getMap("ebu_HowrelatedCS"));
        vl->addWidget(m_editTypeGroup);
    }
    {
        QGridLayout *gl = new QGridLayout;
        m_spinRunningOrderNumber = new QSpinBox;
        m_checkRunningOrderNumber = new QCheckBox(tr("Running Order Number"));
        m_spinRunningOrderNumber->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
        QObject::connect(m_spinRunningOrderNumber, SIGNAL(valueChanged(int)),
                         this, SLOT(runningOrderNumberChanged()));
        gl->addWidget(m_checkRunningOrderNumber, 0, 0);
        gl->addWidget(m_spinRunningOrderNumber, 0, 1);
        vl->addLayout(gl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_editRelationLink = new QLineEdit;
        fl->addRow(tr("Relation Link"), m_editRelationLink);
        vl->addLayout(fl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Relation Identifier")));
        m_editRelationIdentifier = new QLineEdit;
        m_editRelationIdentifier->setReadOnly(true);
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
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    this->setLayout(vl);

    //Event filter
    m_textDocumentation->setText(tr("Relation is used to show the relation in content to another resource."));
    m_editElementRelation->editLang()->installEventFilter(this);
    m_editElementRelation->editValue()->installEventFilter(this);
    m_textNote->installEventFilter(this);
    m_editRelationIdentifier->installEventFilter(this);
    m_editRelationLink->installEventFilter(this);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_spinRunningOrderNumber->installEventFilter(this);

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
    m_title = QString(tr("Relation"));
}

QString RelationTypeForm::toString()
{
    return m_title;
}

void RelationTypeForm::setTitle(const QString &title)
{
    m_title = title;
}

bool RelationTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_editElementRelation->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Relation");
    }
    if (m_editRelationLink->text().isEmpty())
    {
        ok = false;
        fields += tr("Relation Link");
    }
    if (m_editRelationIdentifier->text().isEmpty())
    {
        ok = false;
        fields += tr("Relation Identifier");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
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
    if (!checkCompliance())
        return;
    m_relation->setNote(m_textNote->toPlainText());

    m_editTypeGroup->updateExistingTypeGroup(m_relation);
    if (m_checkRunningOrderNumber->isChecked())
        m_relation->setRunningOrderNumber(m_spinRunningOrderNumber->value());
    else
        m_relation->clearRunningOrderNumber();
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

bool RelationTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if  (obj == (QObject*) m_editElementRelation->editValue())
            m_textDocumentation->setText(tr("Free-text to provide a title for the relation."));
        else if  (obj == (QObject*) m_editElementRelation->editLang())
            m_textDocumentation->setText(tr("The language in which the title is provided."));
        else if (obj == (QObject*) m_textNote)
            m_textDocumentation->setText(tr("A note element to provide additional contextual information."));
        else if (obj == (QObject*) m_spinRunningOrderNumber)
            m_textDocumentation->setText(tr("An optional element that provides the ranking or the running order within an ordered list."));
        else if  (obj == (QObject* ) m_editRelationLink)
            m_textDocumentation->setText(tr("A link related to material."));
        else if  (obj == (QObject* ) m_editRelationIdentifier)
            m_textDocumentation->setText(tr("An element to specify an identifier."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text to show the type of relation to another resource, i.e. identifies ways in which the resource is related by intellectual content to some other resource."));
    }
    return QObject::eventFilter(obj, event);
}
