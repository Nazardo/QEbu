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

#include "organisationdetailstypeform.h"
#include "../model/organisationdetailstype.h"
#include "../model/typeconverter.h"
#include "listview.h"
#include "elementtypeeditbox.h"
#include "elementtypeform.h"
#include "organisationdepartmenttypeform.h"
#include "detailstypeform.h"
#include "entitytypeform.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QEvent>
#include <QTextBrowser>

OrganisationDetailsTypeForm::OrganisationDetailsTypeForm(
        OrganisationDetailsType *organisationDetails,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (organisationDetails) ? Edit : Add;
    if (!organisationDetails)
        m_organisationDetails = new OrganisationDetailsType;
    else
        m_organisationDetails = organisationDetails;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Organisation ID:")));
        m_editOrganisationId = new QLineEdit;
        m_editOrganisationId->setValidator(TypeConverter::getUriValidator());
        hl->addWidget(m_editOrganisationId);
        l->addLayout(hl);
    }
    m_editOrganisationName = new ElementTypeEditBox;
    m_editOrganisationName->setLabel(tr("Organisation name"));
    l->addWidget(m_editOrganisationName);
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonOrganisationDepartment = new QPushButton(">>");
        fl->addRow(tr("Organisation department"), m_buttonOrganisationDepartment);
        QObject::connect(m_buttonOrganisationDepartment, SIGNAL(toggled(bool)),
                         this, SLOT(organisationDepartmentChecked(bool)));
        m_buttonDetails = new QPushButton(">>");
        fl->addRow(tr("Details"), m_buttonDetails);
        QObject::connect(m_buttonDetails, SIGNAL(toggled(bool)),
                         this, SLOT(detailsChecked(bool)));
        m_buttonContacts = new QPushButton(">>");
        fl->addRow(tr("Contacts"), m_buttonContacts);
        QObject::connect(m_buttonContacts, SIGNAL(toggled(bool)),
                         this, SLOT(contactsChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonOrganisationDepartment->setCheckable(true);
        group->addButton(m_buttonOrganisationDepartment);
        m_buttonDetails->setCheckable(true);
        group->addButton(m_buttonDetails);
        m_buttonContacts->setCheckable(true);
        group->addButton(m_buttonContacts);
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

    // Install Event filters
    m_textDocumentation->setText(tr("Minimum information providing means to further identify and contact an organisation."));
    m_editOrganisationId->installEventFilter(this);
    m_editOrganisationName->editValue()->installEventFilter(this);
    m_editOrganisationName->editLang()->installEventFilter(this);
    m_buttonContacts->installEventFilter(this);
    m_buttonDetails->installEventFilter(this);
    m_buttonOrganisationDepartment->installEventFilter(this);

    // Set data fields...
    if(m_organisationDetails->organisationName()) {
        m_editOrganisationName->editLang()->setText(m_organisationDetails->organisationName()->lang());
        m_editOrganisationName->editValue()->setText(m_organisationDetails->organisationName()->value());
    }
    m_editOrganisationId->setText(m_organisationDetails->organisationId());
    m_buttonOrganisationDepartment->setChecked(true);
}

QString OrganisationDetailsTypeForm::toString()
{
    return QString(tr("Organisation Details"));
}

void OrganisationDetailsTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_organisationDetails;
        m_organisationDetails = 0;
    }
    emit closed(m_op, QVarPtr<OrganisationDetailsType>::asQVariant(m_organisationDetails));
}

void OrganisationDetailsTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    m_organisationDetails->setOrganisationId(m_editOrganisationId->text());
    m_organisationDetails->setOrganisationName(new ElementType(
                                                   m_editOrganisationName->editValue()->text(),
                                                   m_editOrganisationName->editLang()->text()));
    emit closed(m_op, QVarPtr<OrganisationDetailsType>::asQVariant(m_organisationDetails));
}

void OrganisationDetailsTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case OrganisationDepartment:
    {
        OrganisationDepartmentTypeForm *organisationDepartmentForm = new OrganisationDepartmentTypeForm(0, this->mainWindow());
        QObject::connect(organisationDepartmentForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(organisationDepartmentFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(organisationDepartmentForm);
    }
        break;
    case Details:
    {
        DetailsTypeForm *detailsForm = new DetailsTypeForm(0, this->mainWindow());
        QObject::connect(detailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(detailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(detailsForm);
    }
        break;
    case Contacts:
    {
        EntityTypeForm *contactsForm = new EntityTypeForm(0, this->mainWindow());
        contactsForm->setTitle(tr("Contacts"));
        QObject::connect(contactsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contactsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contactsForm);
    }
        break;
    }
}

void OrganisationDetailsTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case OrganisationDepartment:
    {
        OrganisationDepartmentTypeForm *organisationDepartmentForm = new OrganisationDepartmentTypeForm(
                    m_organisationDetails->organisationDepartment(), this->mainWindow());
        QObject::connect(organisationDepartmentForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(organisationDepartmentFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(organisationDepartmentForm);
    }
        break;
    case Details:
    {
        DetailsTypeForm *detailsForm = new DetailsTypeForm(
                    m_organisationDetails->details().at(index), this->mainWindow());
        QObject::connect(detailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(detailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(detailsForm);
    }
        break;
    case Contacts:
    {
        EntityTypeForm *contactsForm = new EntityTypeForm(
                    m_organisationDetails->contacts().at(index), this->mainWindow());
        contactsForm->setTitle(tr("Contacts"));
        QObject::connect(contactsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(contactsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(contactsForm);
    }
        break;
    }
}

void OrganisationDetailsTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case OrganisationDepartment:
    {
        m_organisationDetails->setOrganisationDepartment(0);
        m_listView->enableAdd(true);
    }
        break;
    case Details:
    {
        delete(m_organisationDetails->details().takeAt(row));
    }
        break;
    case Contacts:
    {
        delete(m_organisationDetails->contacts().takeAt(row));
    }
        break;
    }
}

void OrganisationDetailsTypeForm::organisationDepartmentChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = OrganisationDepartment;
    updateListAndButtons();
    OrganisationDepartmentType *odt = m_organisationDetails->organisationDepartment();
    if (odt) {
        m_listView->addItem(odt->toString());
        m_listView->enableAdd(false);
    }
}

void OrganisationDetailsTypeForm::detailsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Details;
    updateListAndButtons();
    int s = m_organisationDetails->details().size();
    for (int i=0; i < s; ++i) {
        DetailsType *dt = m_organisationDetails->details().at(i);
        if (!dt)
            continue;
        m_listView->addItem(dt->toString());
    }
}

void OrganisationDetailsTypeForm::contactsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Contacts;
    updateListAndButtons();
    int s = m_organisationDetails->contacts().size();
    for (int i=0; i < s; ++i) {
        EntityType *et = m_organisationDetails->contacts().at(i);
        if (!et)
            continue;
        m_listView->addItem(et->toString());
    }
}

void OrganisationDetailsTypeForm::organisationDepartmentFormClosed(StackableWidget::Operation op, QVariant value)
{
    OrganisationDepartmentType *organisationDepartment = QVarPtr<OrganisationDepartmentType>::asPointer(value);
    if(!organisationDepartment)
        return;
    if(op == Add) {
        m_listView->addItem(organisationDepartment->toString());
        m_organisationDetails->setOrganisationDepartment(organisationDepartment);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, organisationDepartment->toString());
    }
}

void OrganisationDetailsTypeForm::detailsFormClosed(Operation op, QVariant value)
{
    DetailsType *details = QVarPtr<DetailsType>::asPointer(value);
    if (!details)
        return;
    if (op == Add) {
        m_listView->addItem(details->toString());
        m_organisationDetails->details().append(details);
    } else if (op == Edit) {
        int row = m_organisationDetails->details().indexOf(details);
        m_listView->setItem(row, details->toString());
    }
}

void OrganisationDetailsTypeForm::contactsFormClosed(Operation op, QVariant value)
{
    EntityType *contacts = QVarPtr<EntityType>::asPointer(value);
    if (!contacts)
        return;
    if (op == Add) {
        m_listView->addItem(contacts->toString());
        m_organisationDetails->contacts().append(contacts);
    } else if (op == Edit) {
        int row = m_organisationDetails->contacts().indexOf(contacts);
        m_listView->setItem(row, contacts->toString());
    }
}

bool OrganisationDetailsTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editOrganisationId)
            m_textDocumentation->setText(tr("An attribute to uniquely indetify an organisation."));
        else if (obj == (QObject*) m_editOrganisationName->editValue())
            m_textDocumentation->setText(tr("To provide the name of an organisation."));
        else if (obj == (QObject*) m_editOrganisationName->editLang())
            m_textDocumentation->setText(tr("The language in which the organisation name is provided."));
        else if (obj == (QObject*) m_buttonContacts)
            m_textDocumentation->setText(tr("To provide a list of contacts/persons through which the organisation can be contacted."));
        else if (obj == (QObject*) m_buttonDetails)
            m_textDocumentation->setText(tr("To provide the details of an organisation."));
        else if (obj == (QObject*) m_buttonOrganisationDepartment)
            m_textDocumentation->setText(tr("To identify a specific department within an organisation."));
    }
    return QObject::eventFilter(obj, event);
}

void OrganisationDetailsTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == OrganisationDepartment)
        title = tr("Organisation Department");
    else if (m_currentEditMode == Details)
        title = tr("Details");
    else if (m_currentEditMode == Contacts)
        title = tr("Contacts");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool OrganisationDetailsTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if(m_editOrganisationName->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Organisation name");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}
