#include "entitytypeform.h"
#include "qvarptr.h"
#include "typegroupform.h"
#include <QtGui>

EntityTypeForm::EntityTypeForm(EntityType *entity, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (entity) ? Edit : Add;
    if (!entity)
        m_entityType = new EntityType;
    else
        m_entityType = entity;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->addWidget(new QLabel(tr("Entity ID:")));
        m_editEntityId = new QLineEdit;
        hl->addWidget(m_editEntityId);
        l->addLayout(hl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonContactDetails = new QPushButton(">>");
        fl->addRow(tr("Contact details"), m_buttonContactDetails);
        QObject::connect(m_buttonContactDetails,
                         SIGNAL(toggled(bool)),
                         this,
                         SLOT(contactDetailsChecked(bool)));
        m_buttonOrganisationDetails = new QPushButton(">>");
        fl->addRow(tr("Organisation details"), m_buttonOrganisationDetails);
        QObject::connect(m_buttonOrganisationDetails,
                         SIGNAL(toggled(bool)),
                         this,
                         SLOT(organisationDetailsChecked(bool)));
        m_buttonRole = new QPushButton(">>");
        fl->addRow(tr("Roles"), m_buttonRole);
        QObject::connect(m_buttonRole,
                         SIGNAL(toggled(bool)),
                         this,
                         SLOT(roleChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonContactDetails->setCheckable(true);
        group->addButton(m_buttonContactDetails);
        m_buttonOrganisationDetails->setCheckable(true);
        group->addButton(m_buttonOrganisationDetails);
        m_buttonRole->setCheckable(true);
        group->addButton(m_buttonRole);
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
    m_editEntityId->setText(m_entityType->entityId());
    m_buttonContactDetails->setChecked(true);
}

QString EntityTypeForm::toString()
{
    return QString("Entity Type");
}

void EntityTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_entityType;
        m_entityType = 0;
    }
    emit closed(m_op, QVarPtr<EntityType>::asQVariant(m_entityType));
}

void EntityTypeForm::applyClicked()
{
    m_entityType->setEntityId(m_editEntityId->text());
    emit closed(m_op, QVarPtr<EntityType>::asQVariant(m_entityType));
}

void EntityTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case ContactDetails:
        break;
    case OrganisationDetails:
        break;
    case Roles:
    {
        TypeGroupForm *rolesForm = new TypeGroupForm(0, this->mainWindow());
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
        break;
    case OrganisationDetails:
        break;
    case Roles:
    {
        TypeGroupForm *rolesForm = new TypeGroupForm(
                    m_entityType->roles().at(index), this->mainWindow());
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
        m_entityType->contactDetails().removeAt(row);
    }
        break;
    case OrganisationDetails:
    {
        m_entityType->setOrganisationDetails(0);
    }
        break;
    case Roles:
    {
        m_entityType->roles().removeAt(row);
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
    int s = m_entityType->contactDetails().size();
    for (int i=0; i < s; ++i) {
        ContactDetailsType *cdt = m_entityType->contactDetails().at(i);
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
    OrganisationDetailsType *odt = m_entityType->organisationDetails();
    if (odt) {
        m_listView->addItem(odt->toString());
    }
}

void EntityTypeForm::roleChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Roles;
    updateListAndButtons();
    int s = m_entityType->roles().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *tg = m_entityType->roles().at(i);
        if (!tg)
            continue;
        m_listView->addItem(tg->toString());
    }
}

void EntityTypeForm::roleFormClosed(Operation op, QVariant value)
{
    TypeGroup *typeGroup = QVarPtr<TypeGroup>::asPointer(value);
    if (!typeGroup)
        return;
    if (op == Add) {
        m_listView->addItem(typeGroup->toString());
        m_entityType->roles().append(typeGroup);
    } else if (op == Edit) {
        int row = m_entityType->roles().indexOf(typeGroup);
        m_listView->setItem(row, typeGroup->toString());
    }
}

void EntityTypeForm::updateListAndButtons()
{
    // Disable one button and enable all the others
//    m_buttonContactDetails->setEnabled(true);
//    m_buttonOrganisationDetails->setEnabled(true);
//    m_buttonRole->setEnabled(true);
    QString title;
    if (m_currentEditMode == ContactDetails) {
//        m_buttonContactDetails->setEnabled(false);
        title = tr("Contact Details");
    } else if (m_currentEditMode == OrganisationDetails) {
//        m_buttonOrganisationDetails->setEnabled(false);
        title = tr("Organisation Details");
    } else if (m_currentEditMode == Roles) {
//        m_buttonRole->setEnabled(false);
        title = tr("Roles");
    }
    m_listView->setTitle(title);
    m_listView->clear();
}
