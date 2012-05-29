#include "detailstypeform.h"
#include "qvarptr.h"
#include "addresstypeform.h"
#include <QtGui>

DetailsTypeForm::DetailsTypeForm(DetailsType *details, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (details) ? Edit : Add;
    if (!details)
        m_details = new DetailsType;
    else
        m_details = details;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(details);
        l->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_editEmailAddress = new QLineEdit;
        fl->addRow(tr("Email"), m_editEmailAddress);
        m_editWebAddress = new QLineEdit;
        fl->addRow(tr("Web Address"), m_editWebAddress);
        m_editTelephoneNumber = new QLineEdit;
        fl->addRow(tr("Telephone"), m_editTelephoneNumber);
        m_editMobileTelephoneNumber = new QLineEdit;
        fl->addRow(tr("Mobile"), m_editMobileTelephoneNumber);
        m_buttonAddress = new QPushButton(">>");
        fl->addRow(tr("Address"), m_buttonAddress);
        QObject::connect(m_buttonAddress, SIGNAL(toggled(bool)),
                         this, SLOT(addressChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonAddress->setCheckable(true);
        group->addButton(m_buttonAddress);

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
    m_editEmailAddress->setText(m_details->emailAddress());
    m_editWebAddress->setText(m_details->webAddress());
    m_editTelephoneNumber->setText(m_details->telephoneNumber());
    m_editMobileTelephoneNumber->setText(m_details->mobileTelephoneNumber());
    m_buttonAddress->setChecked(true);
}

QString DetailsTypeForm::toString()
{
    return QString("Details Type");
}

void DetailsTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_details;
        m_details = 0;
    }
    emit closed(m_op, QVarPtr<DetailsType>::asQVariant(m_details));
}

void DetailsTypeForm::applyClicked()
{
    m_details->setEmailAddress(m_editEmailAddress->text());
    m_details->setMobileTelephoneNumber(m_editMobileTelephoneNumber->text());
    m_details->setTelephoneNumber(m_editTelephoneNumber->text());
    m_details->setWebAddress(m_editWebAddress->text());
    m_editTypeGroup->updateExistingTypeGroup(m_details);
    emit closed(m_op, QVarPtr<DetailsType>::asQVariant(m_details));
}

void DetailsTypeForm::addClicked()
{
    AddressTypeForm *addressForm = new AddressTypeForm(0, this->mainWindow());
    QObject::connect(addressForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(addressFormClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(addressForm);
}

void DetailsTypeForm::editClicked()
{
    AddressTypeForm *addressForm = new AddressTypeForm(m_details->address(), this->mainWindow());
    QObject::connect(addressForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(addressFormClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(addressForm);
}

void DetailsTypeForm::removeClicked()
{
    m_listView->removeAt(0);
    m_details->setAddress(0);
}

void DetailsTypeForm::addressChecked(bool checked)
{
    if (!checked)
        return;
    updateListAndButtons();
    AddressType *a = m_details->address();
    if (a) {
        m_listView->addItem(a->toString());
    }
}

void DetailsTypeForm::addressFormClosed(StackableWidget::Operation op, QVariant value)
{
    AddressType *address = QVarPtr<AddressType>::asPointer(value);
    if(!address)
        return;
    if(op == Add) {
        m_listView->addItem(address->toString());
        m_details->setAddress(address);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, address->toString());
    }
}

void DetailsTypeForm::updateListAndButtons()
{
    QString title;
    title = tr("Address");
    m_listView->setTitle(title);
    m_listView->clear();
}
