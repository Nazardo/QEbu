#include "entitytypeform.h"
#include <QtGui>

EntityTypeForm::EntityTypeForm(EntityType *entity, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent), m_entity(entity)
{
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
        QObject::connect(buttonClose, SIGNAL(clicked()), this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));
        hl->addWidget(buttonClose);
        hl->addWidget(buttonCancel);
        l->addLayout(hl);
    }
    m_mainHLayout->addLayout(l);
    this->setLayout(m_mainHLayout);
    updateData();
}

QString EntityTypeForm::toString()
{
    return QString("Entity Type");
}

void EntityTypeForm::updateData()
{
    m_editEntityId->setText(m_entity->entityId());
}

void EntityTypeForm::cancelClicked()
{
    emit closed();
}

void EntityTypeForm::applyClicked()
{
    m_entity->setEntityId(m_editEntityId->text());
    emit closed();
}

void EntityTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case ContactDetails:
        /*
        new ContactDetailsForm(...
        */
        break;
    case OrganisationDetails:
        break;
    case Roles:
        break;
    }
}

void EntityTypeForm::editClicked()
{
    switch (m_currentEditMode) {
    case ContactDetails:
        break;
    case OrganisationDetails:
        break;
    case Roles:
        break;
    }
}

void EntityTypeForm::removeClicked()
{
    switch (m_currentEditMode) {
    case ContactDetails:
        break;
    case OrganisationDetails:
        break;
    case Roles:
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
}

void EntityTypeForm::organisationDetailsClicked()
{
    m_currentEditMode = OrganisationDetails;
    showListView(tr("Organisation details"));
}

void EntityTypeForm::roleClicked()
{
    m_currentEditMode = Roles;
    showListView(tr("Roles"));
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
