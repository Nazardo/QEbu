#include "contactdetailstypeform.h"
#include "../model/contactdetailstype.h"
#include "listview.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "detailstypeform.h"
#include "entitytypeform.h"
#include "typegroupform.h"
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QButtonGroup>
#include <QInputDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

ContactDetailsTypeForm::ContactDetailsTypeForm(
        ContactDetailsType *contactDetails,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (contactDetails) ? Edit : Add;
    if (!contactDetails)
        m_contactDetails = new ContactDetailsType;
    else
        m_contactDetails = contactDetails;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editContactId = new QLineEdit;
        fl->addRow(tr("Contact ID"), m_editContactId);
        l->addLayout(fl);
    }
    {

        m_radioName = new QRadioButton(tr("Simple name"));
        m_radioCName = new QRadioButton(tr("Complex name"));
        QButtonGroup *radio = new QButtonGroup;
        m_radioName->setCheckable(true);
        m_radioCName->setCheckable(true);

        QObject::connect(m_radioName, SIGNAL(toggled(bool)),
                         this, SLOT(simpleNameChecked(bool)));
        QObject::connect(m_radioCName, SIGNAL(toggled(bool)),
                         this, SLOT(complexNameChecked(bool)));

        radio->addButton(m_radioName);
        radio->addButton(m_radioCName);

        QHBoxLayout *rl = new QHBoxLayout;
        rl->addWidget(m_radioName);
        rl->addWidget(m_radioCName);
        l->addLayout(rl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_editName = new QLineEdit;
        fl->addRow(tr("Name"), m_editName);
        m_editGivenName = new QLineEdit;
        fl->addRow(tr("Given name"), m_editGivenName);
        m_editFamilyName = new QLineEdit;
        fl->addRow(tr("Family name"), m_editFamilyName);
        m_editUsername = new QLineEdit;
        fl->addRow(tr("Username"), m_editUsername);
        m_editOccupation = new QLineEdit;
        fl->addRow(tr("Occupation"), m_editOccupation);

        m_buttonDetails = new QPushButton(">>");
        fl->addRow(tr("Details"), m_buttonDetails);
        QObject::connect(m_buttonDetails, SIGNAL(toggled(bool)),
                         this, SLOT(contactDetailsChecked(bool)));
        m_buttonStageName = new QPushButton(">>");
        fl->addRow(tr("Stage Name"), m_buttonStageName);
        QObject::connect(m_buttonStageName, SIGNAL(toggled(bool)),
                         this, SLOT(stageNameChecked(bool)));
        m_buttonRelatedContacts = new QPushButton(">>");
        fl->addRow(tr("Related Contacts"), m_buttonRelatedContacts);
        QObject::connect(m_buttonRelatedContacts, SIGNAL(toggled(bool)),
                         this, SLOT(relatedContactsChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonDetails->setCheckable(true);
        group->addButton(m_buttonDetails);
        m_buttonStageName->setCheckable(true);
        group->addButton(m_buttonStageName);
        m_buttonRelatedContacts->setCheckable(true);
        group->addButton(m_buttonRelatedContacts);
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

    // Set data fields...
    m_editContactId->setText(m_contactDetails->contactId());
    m_editName->setText(m_contactDetails->name().getName());
    m_editFamilyName->setText(m_contactDetails->name().getFamilyName());
    m_editGivenName->setText(m_contactDetails->name().getGivenName());
    m_editOccupation->setText(m_contactDetails->occupation());
    m_editUsername->setText(m_contactDetails->username());
    m_buttonDetails->setChecked(true);

    if (m_contactDetails && !m_contactDetails->name().isComplexName())
        m_radioName->setChecked(true);
    else if (m_contactDetails && m_contactDetails->name().isComplexName())
        m_radioCName->setChecked(true);
    else
        m_radioName->setChecked(true);

}

QString ContactDetailsTypeForm::toString()
{
    return QString("Contact Details Type");
}

void ContactDetailsTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_contactDetails;
        m_contactDetails = 0;
    }
    emit closed(m_op, QVarPtr<ContactDetailsType>::asQVariant(m_contactDetails));
}

void ContactDetailsTypeForm::applyClicked()
{
    if(!checkCompliance())
        return;
    m_contactDetails->setContactId(m_editContactId->text());
    m_contactDetails->setUsername(m_editUsername->text());
    m_contactDetails->setOccupation(m_editOccupation->text());
    if (m_radioName->isChecked()) {
        Name name(m_editName->text());
        m_contactDetails->setName(name);

    } else if (m_radioCName->isChecked()) {
        Name name(m_editGivenName->text(), m_editFamilyName->text());
        m_contactDetails->setName(name);

    }
    emit closed(m_op, QVarPtr<ContactDetailsType>::asQVariant(m_contactDetails));
}

void ContactDetailsTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case Details:
    {
        DetailsTypeForm *detailsForm = new DetailsTypeForm(0, this->mainWindow());
        QObject::connect(detailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(detailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(detailsForm);
    }
        break;
    case StageName:
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Contact Details > Stage Name"),
                                              tr("Stage Name"), QLineEdit::Normal,
                                              "", &ok);
        if (ok && !text.isEmpty()) {
            m_listView->addItem(text);
            m_contactDetails->stageNames().append(text);
        }
    }
        break;
    case Related:
    {
        EntityTypeForm *relatedForm = new EntityTypeForm(0, this->mainWindow());
        QObject::connect(relatedForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(relatedContactsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(relatedForm);
    }
        break;
    }
}

void ContactDetailsTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case Details:
    {
        DetailsTypeForm *detailsForm = new DetailsTypeForm(
                    m_contactDetails->details().at(index), this->mainWindow());
        QObject::connect(detailsForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(detailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(detailsForm);
    }
        break;
    case StageName:
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Contact Details > Stage Name"),
                                              tr("Stage Name"), QLineEdit::Normal,
                                             m_contactDetails->stageNames().at(index), &ok);
        if (ok && !text.isEmpty()) {
            m_listView->addItem(text);
        }
    }
        break;
    case Related:
    {
        EntityTypeForm *relatedForm = new EntityTypeForm(
                    m_contactDetails->relatedContacts().at(index), this->mainWindow());
        QObject::connect(relatedForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(relatedContactsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(relatedForm);
    }
        break;
    }
}

void ContactDetailsTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case Details:
    {
        delete(m_contactDetails->details().takeAt(row));
    }
        break;
    case StageName:
    {
        m_contactDetails->stageNames().takeAt(row);
    }
        break;
    case Related:
    {
        delete(m_contactDetails->relatedContacts().takeAt(row));
    }
        break;
    }
}

void ContactDetailsTypeForm::contactDetailsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Details;
    updateListAndButtons();
    int s = m_contactDetails->details().size();
    for (int i=0; i < s; ++i) {
        DetailsType *dt = m_contactDetails->details().at(i);
        if (!dt)
            continue;
        m_listView->addItem(dt->toString());
    }
}

void ContactDetailsTypeForm::stageNameChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = StageName;
    updateListAndButtons();
    int s = m_contactDetails->stageNames().size();
    for (int i=0; i < s; ++i) {
        QString sn = m_contactDetails->stageNames().at(i);
        if (sn.isEmpty())
            continue;
        m_listView->addItem(sn);
    }
}

void ContactDetailsTypeForm::relatedContactsChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Related;
    updateListAndButtons();
    int s = m_contactDetails->relatedContacts().size();
    for (int i=0; i < s; ++i) {
        EntityType *rc = m_contactDetails->relatedContacts().at(i);
        if (!rc)
            continue;
        m_listView->addItem(rc->toString());
    }
}

void ContactDetailsTypeForm::detailsFormClosed(StackableWidget::Operation op, QVariant value)
{
    DetailsType *detail = QVarPtr<DetailsType>::asPointer(value);
    if(!detail)
        return;
    if(op == Add) {
        m_listView->addItem(detail->toString());
        m_contactDetails->details().append(detail);
    } else if(op == Edit) {
        int row = m_contactDetails->details().indexOf(detail);
        m_listView->setItem(row, detail->toString());
    }
}

void ContactDetailsTypeForm::relatedContactsFormClosed(Operation op, QVariant value)
{
    EntityType *related = QVarPtr<EntityType>::asPointer(value);
    if (!related)
        return;
    if (op == Add) {
        m_listView->addItem(related->toString());
        m_contactDetails->relatedContacts().append(related);
    } else if (op == Edit) {
        int row = m_contactDetails->relatedContacts().indexOf(related);
        m_listView->setItem(row, related->toString());
    }
}

void ContactDetailsTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == Details)
        title = tr("Details");
    else if (m_currentEditMode == StageName)
        title = tr("Stage Name");
    else if (m_currentEditMode == Related)
        title = tr("Related Contacts");
    m_listView->setTitle(title);
    m_listView->clear();
}

void ContactDetailsTypeForm::simpleNameChecked(bool checked)
{
    if (!checked)
        return;
    m_editName->setEnabled(true);
    m_editFamilyName->setEnabled(false);
    m_editGivenName->setEnabled(false);
}

void ContactDetailsTypeForm::complexNameChecked(bool checked)
{
    if (!checked)
        return;
    m_editName->setEnabled(false);
    m_editFamilyName->setEnabled(true);
    m_editGivenName->setEnabled(true);
}

bool ContactDetailsTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_radioName->isChecked()) {
        if (m_editName->text().isEmpty()) {
            ok = false;
            fields += tr("Name");
        }
    }
    else if(m_radioCName->isChecked()) {
        if (m_editFamilyName->text().isEmpty() || m_editGivenName->text().isEmpty())
            ok = false;
        if (m_editGivenName->text().isEmpty())
            fields += tr("Given name");
        if (m_editFamilyName->text().isEmpty())
            fields += tr("Family name");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}
