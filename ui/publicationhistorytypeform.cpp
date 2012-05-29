#include "publicationhistorytypeform.h"

#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "publicationtypeform.h"
#include "../model/typeconverter.h"
#include "typegroupform.h"
#include <QtGui>

PublicationHistoryTypeForm::PublicationHistoryTypeForm(PublicationHistoryType *publicationHistory, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (publicationHistory) ? Edit : Add;
    if (!publicationHistory)
        m_publicationHistory = new PublicationHistoryType;
    else
        m_publicationHistory = publicationHistory;
    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editFirstPublicationDate = new QDateEdit;
        m_editFirstPublicationDate->setCalendarPopup(true);
        fl->addRow(tr("First publication date"), m_editFirstPublicationDate);
        m_editFirstPublicationTime = new QTimeEdit;
        fl->addRow(tr("First publication time"), m_editFirstPublicationTime);
        m_editFirstPublicationChannel = new QComboBox;
        QStringList sl(mainWindow->ebuCoreMain()->formatMap().keys());
        m_editFirstPublicationChannel->addItems(sl);
        fl->addRow(tr("First publication channel"), m_editFirstPublicationChannel);
        m_buttonRepeat = new QPushButton(">>");
        m_buttonRepeat->setCheckable(true);
        fl->addRow(tr("Repetitions"), m_buttonRepeat);
        QObject::connect(m_buttonRepeat, SIGNAL(toggled(bool)),
                         this, SLOT(repeatChecked(bool)));
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
    if (m_publicationHistory->firstPublication()) {
        m_editFirstPublicationDate->setDate(m_publicationHistory->firstPublication()->date().date());
        m_editFirstPublicationTime->setTime(m_publicationHistory->firstPublication()->time().time());
        if (m_publicationHistory->firstPublication()->channel()) {
            int index = m_editFirstPublicationChannel->findText(m_publicationHistory->firstPublication()->channel()->formatId());
            m_editFirstPublicationChannel->setCurrentIndex(index);
        }
    }
    m_buttonRepeat->setChecked(true);
}

QString PublicationHistoryTypeForm::toString()
{
    return QString("Publication History Type");
}

void PublicationHistoryTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_publicationHistory;
        m_publicationHistory = 0;
    }
    emit closed(m_op, QVarPtr<PublicationHistoryType>::asQVariant(m_publicationHistory));
}

void PublicationHistoryTypeForm::applyClicked()
{
    PublicationType *pt = new PublicationType;
    pt->setTime(m_editFirstPublicationTime->dateTime());
    pt->setDate(m_editFirstPublicationDate->dateTime());
    pt->setChannel(0); /// @todo
    m_publicationHistory->setFirstPublication(pt);
    emit closed(m_op, QVarPtr<PublicationHistoryType>::asQVariant(m_publicationHistory));
}

void PublicationHistoryTypeForm::addClicked()
{
    PublicationTypeForm *repeatForm = new PublicationTypeForm(0, this->mainWindow());
    QObject::connect(repeatForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(repeatFormClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(repeatForm);
}

void PublicationHistoryTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;

    PublicationTypeForm *repeatForm = new PublicationTypeForm(
                m_publicationHistory->repetitions().at(index), this->mainWindow());
    QObject::connect(repeatForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(repeatFormClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(repeatForm);

}

void PublicationHistoryTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    m_publicationHistory->repetitions().removeAt(row);
}

void PublicationHistoryTypeForm::repeatChecked(bool checked)
{
    if (!checked)
        return;
    updateListAndButtons();
    int s = m_publicationHistory->repetitions().size();
    for (int i=0; i < s; ++i) {
        PublicationType *rep = m_publicationHistory->repetitions().at(i);
        if (!rep)
            continue;
        m_listView->addItem(rep->toString());
    }
}

void PublicationHistoryTypeForm::repeatFormClosed(StackableWidget::Operation op, QVariant value)
{
    PublicationType *repeat = QVarPtr<PublicationType>::asPointer(value);
    if(!repeat)
        return;
    if(op == Add) {
        m_listView->addItem(repeat->toString());
        m_publicationHistory->repetitions().append(repeat);
    } else if(op == Edit) {
        int row = m_publicationHistory->repetitions().indexOf(repeat);
        m_listView->setItem(row, repeat->toString());
    }
}

void PublicationHistoryTypeForm::updateListAndButtons()
{
    QString title;
    title = tr("Repetitions");
    m_listView->setTitle(title);
    m_listView->clear();
}


