#include "detailstypeform.h"
#include "../model/detailstype.h"
#include "listview.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "addresstypeform.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QEvent>

DetailsTypeForm::DetailsTypeForm(DetailsType *details,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (details) ? Edit : Add;
    if (!details)
        m_details = new DetailsType;
    else
        m_details = details;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(m_details);
        m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
        m_editTypeGroup->editTypeLabel()->installEventFilter(this);
        m_editTypeGroup->editTypeLink()->installEventFilter(this);
        l->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_editEmailAddress = new QLineEdit;
        m_editEmailAddress->installEventFilter(this);
        fl->addRow(tr("Email"), m_editEmailAddress);
        m_editWebAddress = new QLineEdit;
        m_editWebAddress->installEventFilter(this);
        fl->addRow(tr("Web Address"), m_editWebAddress);
        m_editTelephoneNumber = new QLineEdit;
        m_editTelephoneNumber->installEventFilter(this);
        fl->addRow(tr("Telephone"), m_editTelephoneNumber);
        m_editMobileTelephoneNumber = new QLineEdit;
        m_editMobileTelephoneNumber->installEventFilter(this);
        fl->addRow(tr("Mobile"), m_editMobileTelephoneNumber);
        m_buttonAddress = new QPushButton(">>");
        m_buttonAddress->installEventFilter(this);
        fl->addRow(tr("Address"), m_buttonAddress);
        QObject::connect(m_buttonAddress, SIGNAL(toggled(bool)),
                         this, SLOT(addressChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonAddress->setCheckable(true);
        group->addButton(m_buttonAddress);

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
    m_textDocumentation->setText(tr("The contact details of a contact/person or organisation"));
    m_editEmailAddress->setText(m_details->emailAddress());
    m_editWebAddress->setText(m_details->webAddress());
    m_editTelephoneNumber->setText(m_details->telephoneNumber());
    m_editMobileTelephoneNumber->setText(m_details->mobileTelephoneNumber());
    m_buttonAddress->setChecked(true);
}

QString DetailsTypeForm::toString()
{
    return QString(tr("Details"));
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

bool DetailsTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition."));
        else if ( obj == (QObject*) m_editTypeGroup->editTypeLabel() )
            m_textDocumentation->setText(tr("Free text to define the type."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a term or only identify a classification scheme"));
        else if  (obj == (QObject*) m_editEmailAddress)
            m_textDocumentation->setText(tr("The email address of a contact or organisation"));
        else if  (obj == (QObject*) m_editTelephoneNumber)
            m_textDocumentation->setText(tr("The telephone number of a contact or organisation."));
        else if  (obj == (QObject*) m_editWebAddress)
            m_textDocumentation->setText(tr("The web address of a contact or organisation"));
        else if  (obj == (QObject*) m_editMobileTelephoneNumber)
            m_textDocumentation->setText(tr("The mobile telephone number of a contact or organisation."));
        else if  (obj == (QObject*) m_buttonAddress)
            m_textDocumentation->setText(tr("The address of a contact or organisation."));

    }
    return QObject::eventFilter(obj, event);
}
