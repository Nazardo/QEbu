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

#include "entitytypeform.h"
#include "../model/entitytype.h"
#include "../model/typeconverter.h"
#include "listview.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "typegroupform.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QEvent>
#include <QTextBrowser>

EntityTypeForm::EntityTypeForm(EntityType *entity, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (entity) ? Edit : Add;
    if (!entity)
        m_entity = new EntityType;
    else
        m_entity = entity;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Entity ID:")));
        m_editEntityId = new QLineEdit;
        m_editEntityId->setValidator(TypeConverter::getUriValidator());
        hl->addWidget(m_editEntityId);
        l->addLayout(hl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonContactDetails = new QPushButton(">>");
        fl->addRow(tr("Contact details"), m_buttonContactDetails);
        QObject::connect(m_buttonContactDetails, SIGNAL(toggled(bool)),
                         this, SLOT(contactDetailsChecked(bool)));
        m_buttonOrganisationDetails = new QPushButton(">>");
        fl->addRow(tr("Organisation details"), m_buttonOrganisationDetails);
        QObject::connect(m_buttonOrganisationDetails, SIGNAL(toggled(bool)),
                         this, SLOT(organisationDetailsChecked(bool)));
        m_buttonRole = new QPushButton(">>");
        fl->addRow(tr("Roles"), m_buttonRole);
        QObject::connect(m_buttonRole, SIGNAL(toggled(bool)),
                         this, SLOT(roleChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonContactDetails->setCheckable(true);
        group->addButton(m_buttonContactDetails);
        m_buttonOrganisationDetails->setCheckable(true);
        group->addButton(m_buttonOrganisationDetails);
        m_buttonRole->setCheckable(true);
        group->addButton(m_buttonRole);
    }
    mainHLayout->addLayout(l);
    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    mainHLayout->addWidget(m_listView);
    this->setLayout(mainHLayout);

    //Event filter
    m_textDocumentation->setText(tr("Provides detailed information about a person, a group of persons, or organisation."));
    m_editEntityId->installEventFilter(this);
    m_buttonContactDetails->installEventFilter(this);
    m_buttonOrganisationDetails->installEventFilter(this);
    m_buttonRole->installEventFilter(this);

    // Set data fields...
    m_editEntityId->setText(m_entity->entityId());
    m_buttonContactDetails->setChecked(true);
    m_title = QString(tr("Entity"));
}

QString EntityTypeForm::toString()
{
    return m_title;
}

void EntityTypeForm::setTitle(const QString &title)
{
    m_title = title;
}

void EntityTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_entity;
        m_entity = 0;
    }
    emit closed(m_op, QVarPtr<EntityType>::asQVariant(m_entity));
}

void EntityTypeForm::applyClicked()
{
    m_entity->setEntityId(m_editEntityId->text());
    emit closed(m_op, QVarPtr<EntityType>::asQVariant(m_entity));
}

void EntityTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case ContactDetails:
    {
        ContactDetailsTypeForm *contactDetailsForm = new ContactDetailsTypeForm(0, this->mainWindow());
        QObject::connect(contactDetailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contactDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contactDetailsForm);
    }
        break;
    case OrganisationDetails:
    {
        OrganisationDetailsTypeForm *organisationDetailForm = new OrganisationDetailsTypeForm(0, this->mainWindow());
        QObject::connect(organisationDetailForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(organisationDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(organisationDetailForm);
    }
        break;
    case Roles:
    {
        TypeGroupForm *rolesForm = new TypeGroupForm(0, this->mainWindow());
        rolesForm->addLinksMap(mainWindow()->getMap("ebu_RoleCodeCS"));
        rolesForm->setTitle(tr("Role"));
        rolesForm->setGeneralDoc(tr("Used to define the type of role."));
        rolesForm->setDefinitionDoc(tr("An optional definition of the type.\nExample: 'the terms and conditions under which the resource can be used'."));
        rolesForm->setLinkDoc(tr("A link to a term or only identify a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_RoleCodeCS_p.xml.htm\">ebu_RoleCodeCS</a>"));
        rolesForm->setLabelDoc(tr("Free text definition of the type or rights expressed in dc:rights.\nExample: 'Director'."));
        QObject::connect(rolesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(roleFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rolesForm);
    }
        break;
    }
}

void EntityTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case ContactDetails:
    {
        ContactDetailsTypeForm *contactDetailsForm = new ContactDetailsTypeForm(
                    m_entity->contactDetails().at(index), this->mainWindow());
        QObject::connect(contactDetailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contactDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contactDetailsForm);
    }
        break;
    case OrganisationDetails:
    {
        OrganisationDetailsTypeForm *organisationDetailsForm = new OrganisationDetailsTypeForm(
                    m_entity->organisationDetails(), this->mainWindow());
        QObject::connect(organisationDetailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(organisationDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(organisationDetailsForm);
    }
        break;
    case Roles:
    {
        TypeGroupForm *rolesForm = new TypeGroupForm(
                    m_entity->roles().at(index), this->mainWindow());
        rolesForm->addLinksMap(mainWindow()->getMap("ebu_RoleCodeCS"));
        rolesForm->setTitle(tr("Role"));
        rolesForm->setGeneralDoc(tr("Used to define the type of role."));
        rolesForm->setDefinitionDoc(tr("An optional definition of the type.\nExample: 'the terms and conditions under which the resource can be used'."));
        rolesForm->setLinkDoc(tr("A link to a term or only identify a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_RoleCodeCS_p.xml.htm\">ebu_RoleCodeCS</a>"));
        rolesForm->setLabelDoc(tr("Free text definition of the type or rights expressed in dc:rights.\nExample: 'Director'."));
        QObject::connect(rolesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(roleFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(rolesForm);
    }
        break;
    }
}

void EntityTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case ContactDetails:
    {
        delete(m_entity->contactDetails().takeAt(row));
    }
        break;
    case OrganisationDetails:
    {
        m_entity->setOrganisationDetails(0);
        m_listView->enableAdd(true);
    }
        break;
    case Roles:
    {
        delete(m_entity->roles().takeAt(row));
    }
        break;
    }
}

void EntityTypeForm::contactDetailsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = ContactDetails;
    updateListAndButtons();
    int s = m_entity->contactDetails().size();
    for (int i=0; i < s; ++i) {
        ContactDetailsType *cdt = m_entity->contactDetails().at(i);
        if (!cdt)
            continue;
        m_listView->addItem(cdt->toString());
    }
}

void EntityTypeForm::organisationDetailsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = OrganisationDetails;
    updateListAndButtons();
    OrganisationDetailsType *odt = m_entity->organisationDetails();
    if (odt) {
        m_listView->addItem(odt->toString());
        m_listView->enableAdd(false);
    }
}

void EntityTypeForm::roleChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Roles;
    updateListAndButtons();
    int s = m_entity->roles().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *tg = m_entity->roles().at(i);
        if (!tg)
            continue;
        m_listView->addItem(tg->toString());
    }
}

void EntityTypeForm::contactDetailsFormClosed(Operation op, QVariant value)
{
    ContactDetailsType *contactDetails = QVarPtr<ContactDetailsType>::asPointer(value);
    if(!contactDetails)
        return;
    if(op == Add) {
        m_listView->addItem(contactDetails->toString());
        m_entity->contactDetails().append(contactDetails);
    } else if(op == Edit) {
        int row = m_entity->contactDetails().indexOf(contactDetails);
        m_listView->setItem(row, contactDetails->toString());
    }
}

void EntityTypeForm::organisationDetailsFormClosed(StackableWidget::Operation op, QVariant value)
{
    OrganisationDetailsType *organisationDetails = QVarPtr<OrganisationDetailsType>::asPointer(value);
    if(!organisationDetails)
        return;
    if(op == Add) {
        m_listView->addItem(organisationDetails->toString());
        m_entity->setOrganisationDetails(organisationDetails);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, organisationDetails->toString());
    }
}

void EntityTypeForm::roleFormClosed(Operation op, QVariant value)
{
    TypeGroup *typeGroup = QVarPtr<TypeGroup>::asPointer(value);
    if (!typeGroup)
        return;
    if (op == Add) {
        m_listView->addItem(typeGroup->toString());
        m_entity->roles().append(typeGroup);
    } else if (op == Edit) {
        int row = m_entity->roles().indexOf(typeGroup);
        m_listView->setItem(row, typeGroup->toString());
    }
}

void EntityTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == ContactDetails)
        title = tr("Contact Details");
    else if (m_currentEditMode == OrganisationDetails)
        title = tr("Organisation Details");
    else if (m_currentEditMode == Roles)
        title = tr("Roles");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool EntityTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editEntityId )
            m_textDocumentation->setText(tr("An attribute to uniquely identify the person or organisation."));
        else if  (obj == (QObject*) m_buttonContactDetails )
            m_textDocumentation->setText(tr("Minimum information providing means to further identify and contact the entity."));
        else if  (obj == (QObject*) m_buttonOrganisationDetails )
            m_textDocumentation->setText(tr("Minimum information providing means to further identify and contact the entity as an organisation. Cardinality is '1'. Only one organisation is acting as an entity or only one organisation is associated to a person in relation to is occupation in the context of the current content description."));
        else if (obj == (QObject*) m_buttonRole )
            m_textDocumentation->setText(tr("Used to identify the function fulfilled by the person, group or organisation described as an entity. It can be used for example to detail the role of a 'contributor' or a 'creator', as several functions can be seen as participating to the creative process."));
    }
    return QObject::eventFilter(obj, event);
}
