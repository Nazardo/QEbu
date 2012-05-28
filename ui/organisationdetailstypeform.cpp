#include "organisationdetailstypeform.h"
#include "elementtypeform.h"
#include "organisationdepartmenttypeform.h"
#include "detailstypeform.h"
#include "entitytypeform.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QtGui>

OrganisationDetailsTypeForm::OrganisationDetailsTypeForm(OrganisationDetailsType *organisationDetails,
                                                         QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (organisationDetails) ? Edit : Add;
    if (!organisationDetails)
        m_organisationDetails = new OrganisationDetailsType;
    else
        m_organisationDetails = organisationDetails;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Organisation ID:")));
        m_editOrganisationId = new QLineEdit;
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
        l->addLayout(hl);
    }
    m_mainHLayout->addLayout(l);
    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    m_mainHLayout->addWidget(m_listView);
    this->setLayout(m_mainHLayout);

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
    return QString("Organisation Details Type");
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
        m_organisationDetails->details().removeAt(row);
    }
        break;
    case Contacts:
    {
        m_organisationDetails->contacts().removeAt(row);
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
    QString error_msg = "";
    if(m_editOrganisationName->editValue()->text().isEmpty()) {
        ok = false;
        error_msg += "organisationName\n";
    }
    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Rrequired fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
