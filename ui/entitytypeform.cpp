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
    m_listView = 0;
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
        m_buttonContactDetails = new QPushButton("...");
        fl->addRow(tr("Contact details"), m_buttonContactDetails);
        QObject::connect(m_buttonContactDetails,
                         SIGNAL(clicked()),
                         this,
                         SLOT(contactDetailsClicked()));
        m_buttonOrganisationDetails = new QPushButton("...");
        fl->addRow(tr("Organisation details"), m_buttonOrganisationDetails);
        QObject::connect(m_buttonOrganisationDetails,
                         SIGNAL(clicked()),
                         this,
                         SLOT(organisationDetailsClicked()));
        m_buttonRole = new QPushButton("...");
        fl->addRow(tr("Roles"), m_buttonRole);
        QObject::connect(m_buttonRole,
                         SIGNAL(clicked()),
                         this,
                         SLOT(roleClicked()));
        l->addLayout(fl);
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
    this->setLayout(m_mainHLayout);
    // Set text fields...
    m_editEntityId->setText(m_entityType->entityId());
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

void EntityTypeForm::closeClicked()
{
    hideListView();
}

void EntityTypeForm::contactDetailsClicked()
{
    m_currentEditMode = ContactDetails;
    showListView(tr("Contact details"));
    int s = m_entityType->contactDetails().size();
    for (int i=0; i < s; ++i) {
        ContactDetailsType *cdt = m_entityType->contactDetails().at(i);
        if (!cdt)
            continue;
        m_listView->addItem(cdt->toString());
    }
}

void EntityTypeForm::organisationDetailsClicked()
{
    m_currentEditMode = OrganisationDetails;
    showListView(tr("Organisation details"));
    OrganisationDetailsType *odt = m_entityType->organisationDetails();
    if (odt) {
        m_listView->addItem(odt->toString());
    }
}

void EntityTypeForm::roleClicked()
{
    m_currentEditMode = Roles;
    showListView(tr("Roles"));
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

void EntityTypeForm::enableButtons(bool enable)
{
    m_buttonContactDetails->setEnabled(enable);
    m_buttonOrganisationDetails->setEnabled(enable);
    m_buttonRole->setEnabled(enable);
}

void EntityTypeForm::showListView(QString name)
{
    enableButtons(false);
    m_listView = new ListView("<h3>"+name+"</h3>");
    m_mainHLayout->addWidget(m_listView);
    QObject::connect(m_listView->buttonAdd(),
                     SIGNAL(clicked()),
                     this,
                     SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(),
                     SIGNAL(clicked()),
                     this,
                     SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(),
                     SIGNAL(clicked()),
                     this,
                     SLOT(removeClicked()));
    QObject::connect(m_listView->buttonClose(),
                     SIGNAL(clicked()),
                     this,
                     SLOT(closeClicked()));

}

void EntityTypeForm::hideListView()
{
    m_listView->hide();
    m_mainHLayout->removeWidget(m_listView);
    enableButtons(true);
}
