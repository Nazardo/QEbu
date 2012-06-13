#include "addresstypeform.h"
#include "../model/detailstype.h"
#include "listview.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QButtonGroup>
#include <QInputDialog>
#include <QComboBox>
#include <QTextBrowser>
#include <QEvent>

AddressTypeForm::AddressTypeForm(AddressType *address, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (address) ? Edit : Add;
    if (!address)
        m_address = new AddressType;
    else
        m_address = address;

    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editAddressTownCity = new QLineEdit;
        fl->addRow(tr("Town"), m_editAddressTownCity);
        m_editAddressCountryState = new QLineEdit;
        fl->addRow(tr("County"), m_editAddressCountryState);
        m_editAddressDeliveryCode = new QLineEdit;
        fl->addRow(tr("Delivery"), m_editAddressDeliveryCode);
        l->addLayout(fl);
    }
    {
        QVBoxLayout *v = new QVBoxLayout;
        m_editCountry = new TypeGroupEditBox(m_address->country());
        m_editCountry->setLabel(tr("Country"));
        v->addWidget(m_editCountry);
        l->addLayout(v);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonAddressLine = new QPushButton(">>");
        fl->addRow(tr("Address Lines"), m_buttonAddressLine);
        QObject::connect(m_buttonAddressLine, SIGNAL(toggled(bool)),
                         this, SLOT(addressLineChecked(bool)));
        l->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonAddressLine->setCheckable(true);
        group->addButton(m_buttonAddressLine);
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

    // Event filter
    m_textDocumentation->setText(tr("The address of a contact/person or organisation."));
    m_editAddressTownCity->installEventFilter(this);
    m_editAddressCountryState->installEventFilter(this);
    m_editAddressDeliveryCode->installEventFilter(this);
    m_editCountry->editTypeDefinition()->installEventFilter(this);
    m_editCountry->editTypeLabel()->installEventFilter(this);
    m_editCountry->editTypeLink()->installEventFilter(this);
    m_buttonAddressLine->installEventFilter(this);

    // Set data fields...
    m_editAddressTownCity->setText(m_address->townCity());
    m_editAddressCountryState->setText(m_address->countyState());
    m_editAddressDeliveryCode->setText(m_address->deliveryCode());
    m_buttonAddressLine->setChecked(true);
}

QString AddressTypeForm::toString()
{
    return QString(tr("Address"));
}

void AddressTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_address;
        m_address = 0;
    }
    emit closed(m_op, QVarPtr<AddressType>::asQVariant(m_address));
}

void AddressTypeForm::applyClicked()
{
    m_address->setTownCity(m_editAddressTownCity->text());
    m_address->setCountyState(m_editAddressCountryState->text());
    m_address->setDeliveryCode(m_editAddressDeliveryCode->text());
    m_address->setCountry(m_editCountry->typeGroup());
    emit closed(m_op, QVarPtr<AddressType>::asQVariant(m_address));
}

void AddressTypeForm::addClicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Address Type > Address Line"),
                                          tr("Address Line"), QLineEdit::Normal,
                                          "", &ok);
    if (ok && !text.isEmpty()) {
        m_listView->addItem(text);
        m_address->lines().append(text);
    }
}

void AddressTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Address Type > Address Line"),
                                          tr("Address Line"), QLineEdit::Normal,
                                         m_address->lines().at(index), &ok);
    if (ok && !text.isEmpty()) {
       m_listView->setItem(index, text);
       m_address->lines().removeAt(index);
       m_address->lines().insert(index, text);
    }
}

void AddressTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    m_address->lines().takeAt(row);
}

void AddressTypeForm::addressLineChecked(bool checked)
{
    if (!checked)
        return;
    updateListAndButtons();
    int s = m_address->lines().size();
    for (int i=0; i < s; ++i) {
        QString line = m_address->lines().at(i);
        if (line.isEmpty())
            continue;
        m_listView->addItem(line);
    }
}

void AddressTypeForm::updateListAndButtons()
{
    QString title = tr("Address Lines");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool AddressTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editAddressTownCity )
            m_textDocumentation->setText(tr("The name of the city/town of the address."));
        else if  (obj == (QObject*) m_editAddressCountryState)
            m_textDocumentation->setText(tr("The optional name of the county/state of the address."));
        else if  (obj == (QObject*) m_editAddressDeliveryCode)
            m_textDocumentation->setText("The delivery code of the address.");
        else if (obj == (QObject*) m_editCountry->editTypeDefinition())
            m_textDocumentation->setText(tr("The country of residence."));
        else if (obj == (QObject*) m_editCountry->editTypeLink())
            m_textDocumentation->setText(tr("The country of residence.\n"));
        else if (obj == (QObject*) m_editCountry->editTypeLabel())
            m_textDocumentation->setText(tr("The country of residence."));
        else if (obj == (QObject*) m_buttonAddressLine)
            m_textDocumentation->setText(tr("One or more address lines."));
    }
    return QObject::eventFilter(obj, event);
}
