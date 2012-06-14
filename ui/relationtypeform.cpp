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

#include "relationtypeform.h"
#include "../model/coremetadatatype.h"
#include "../model/qebulimits.h"
#include "../model/typeconverter.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include "identifiertypeform.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextBrowser>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QEvent>
#include <QComboBox>
#include <QRadioButton>

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

        m_radioRelation = new QRadioButton(tr("Relation"));
        m_radioRelation->setCheckable(true);
        vl->addWidget(m_radioRelation);

        m_editElementRelation = new ElementTypeEditBox;
        m_editElementRelation->setLabel(tr("Relation"));
        vl->addWidget(m_editElementRelation);
    }
    {
        m_radioRelationLink = new QRadioButton(tr("Relation Link"));
        m_radioRelationLink->setCheckable(true);
        vl->addWidget(m_radioRelationLink);

        QFormLayout *fl = new QFormLayout;
        m_editRelationLink = new QLineEdit;
        m_editRelationLink->setValidator(TypeConverter::getUriValidator());
        m_labelRelationLink = new QLabel(tr("Relation Link"));
        fl->addRow(m_labelRelationLink, m_editRelationLink);
        vl->addLayout(fl);
    }
    {
        m_radioRelationIdentifier = new QRadioButton(tr("Relation Identifier"));
        m_radioRelationIdentifier->setCheckable(true);
        vl->addWidget(m_radioRelationIdentifier);

        QHBoxLayout *hl = new QHBoxLayout;
        m_labelRelationIdentifier = new QLabel(tr("Relation Link"));
        hl->addWidget(m_labelRelationIdentifier);
        m_editRelationIdentifier = new QLineEdit;
        m_editRelationIdentifier->setReadOnly(true);
        hl->addWidget(m_editRelationIdentifier);
        m_buttonRelationIdentifierAdd = new QPushButton(tr("Add/Edit"));
        QObject::connect(m_buttonRelationIdentifierAdd, SIGNAL(clicked()),
                         this, SLOT(relationIdentifierClicked()));
        hl->addWidget(m_buttonRelationIdentifierAdd);
        m_buttonRelationIdentifierRemove = new QPushButton(tr("Remove"));
        QObject::connect(m_buttonRelationIdentifierRemove, SIGNAL(clicked()),
                         this, SLOT(relationIdentifierRemoveClicked()));
        hl->addWidget(m_buttonRelationIdentifierRemove);
        vl->addLayout(hl);
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
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    this->setLayout(vl);

    QObject::connect(m_radioRelation, SIGNAL(toggled(bool)),
                     this, SLOT(radioRelationChecked(bool)));
    QObject::connect(m_radioRelationLink, SIGNAL(toggled(bool)),
                     this, SLOT(radioRelationLinkChecked(bool)));
    QObject::connect(m_radioRelationIdentifier, SIGNAL(toggled(bool)),
                     this, SLOT(radioRelationIdentifierChecked(bool)));

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

    switch(m_relation->relationTypeRepresentation()) {
    case RelationType::enumRelation:
        m_radioRelation->setChecked(true);
        m_editElementRelation->setEnabled(true);
        m_labelRelationLink->setEnabled(false);
        m_editRelationLink->setEnabled(false);
        m_labelRelationIdentifier->setEnabled(false);
        m_editRelationIdentifier->setEnabled(false);
        m_buttonRelationIdentifierAdd->setEnabled(false);
        m_buttonRelationIdentifierRemove->setEnabled(false);

        break;
    case RelationType::enumRelationLink:
        m_radioRelationLink->setChecked(true);
        m_editElementRelation->setEnabled(false);
        m_labelRelationLink->setEnabled(true);
        m_editRelationLink->setEnabled(true);
        m_labelRelationIdentifier->setEnabled(false);
        m_editRelationIdentifier->setEnabled(false);
        m_buttonRelationIdentifierAdd->setEnabled(false);
        m_buttonRelationIdentifierRemove->setEnabled(false);

        break;
    case RelationType::enumRelationIdentifier:
        m_radioRelationIdentifier->setChecked(true);
        m_editElementRelation->setEnabled(false);
        m_labelRelationLink->setEnabled(false);
        m_editRelationLink->setEnabled(false);
        m_labelRelationIdentifier->setEnabled(true);
        m_editRelationIdentifier->setEnabled(true);
        m_buttonRelationIdentifierAdd->setEnabled(true);
        m_buttonRelationIdentifierRemove->setEnabled(true);

        break;
    }

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
    if (m_radioRelation->isChecked() && m_editElementRelation->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Relation");
    }
    if (m_radioRelationLink->isChecked() && m_editRelationLink->text().isEmpty())
    {
        ok = false;
        fields += tr("Relation Link");
    }
    if (m_radioRelationIdentifier->isChecked() && m_editRelationIdentifier->text().isEmpty())
    {
        ok = false;
        fields += tr("Relation Identifier");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required field:</b><br>")
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


    if (m_checkRunningOrderNumber->isChecked())
        m_relation->setRunningOrderNumber(m_spinRunningOrderNumber->value());
    else
        m_relation->clearRunningOrderNumber();

    if (m_radioRelation->isChecked()) {
        m_relation->setRelation(new ElementType(
                                    m_editElementRelation->editValue()->text(),
                                    m_editElementRelation->editLang()->text()));
    }
    if (m_radioRelationLink->isChecked()) {
        m_relation->setRelationLink(m_editRelationLink->text());
    }
    if (m_radioRelationIdentifier->isChecked()) {
        m_editTypeGroup->updateExistingTypeGroup(m_relation);
    }
    emit closed(m_op, QVarPtr<RelationType>::asQVariant(m_relation));
}

void RelationTypeForm::runningOrderNumberChanged()
{
    m_checkRunningOrderNumber->setChecked(true);
}

void RelationTypeForm::radioRelationChecked(bool checked)
{
    if (!checked)
        return;

    m_editElementRelation->setEnabled(true);
    m_labelRelationLink->setEnabled(false);
    m_editRelationLink->setEnabled(false);
    m_labelRelationIdentifier->setEnabled(false);
    m_editRelationIdentifier->setEnabled(false);
    m_buttonRelationIdentifierAdd->setEnabled(false);
    m_buttonRelationIdentifierRemove->setEnabled(false);
}

void RelationTypeForm::radioRelationLinkChecked(bool checked)
{
    if (!checked)
        return;

    m_editElementRelation->setEnabled(false);
    m_labelRelationLink->setEnabled(true);
    m_editRelationLink->setEnabled(true);
    m_labelRelationIdentifier->setEnabled(false);
    m_editRelationIdentifier->setEnabled(false);
    m_buttonRelationIdentifierAdd->setEnabled(false);
    m_buttonRelationIdentifierRemove->setEnabled(false);
}

void RelationTypeForm::radioRelationIdentifierChecked(bool checked)
{
    if (!checked)
        return;

    m_editElementRelation->setEnabled(false);
    m_labelRelationLink->setEnabled(false);
    m_editRelationLink->setEnabled(false);
    m_labelRelationIdentifier->setEnabled(true);
    m_editRelationIdentifier->setEnabled(true);
    m_buttonRelationIdentifierAdd->setEnabled(true);
    m_buttonRelationIdentifierRemove->setEnabled(true);
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
            m_textDocumentation->setHtml(tr("A link to a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/tva_HowRelatedCS_p.xml.htm\">tva_HowRelatedCS</a><br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_HowRelatedCS_p.xml.htm\">ebu_HowrelatedCS</a>"));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text to show the type of relation to another resource, i.e. identifies ways in which the resource is related by intellectual content to some other resource."));
    }
    return QObject::eventFilter(obj, event);
}
