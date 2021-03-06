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

#include "publicationhistorytypeform.h"
#include "../model/ebucoremaintype.h"
#include "listview.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "publicationtypeform.h"
#include "../model/typeconverter.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTimeEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QEvent>
#include <QTextBrowser>

PublicationHistoryTypeForm::PublicationHistoryTypeForm(
        PublicationHistoryType *publicationHistory,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (publicationHistory) ? Edit : Add;
    if (!publicationHistory)
        m_publicationHistory = new PublicationHistoryType;
    else
        m_publicationHistory = publicationHistory;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    {
        QGroupBox *group = new QGroupBox(tr("First publication"));
        QGridLayout *gl = new QGridLayout;
        m_editFirstPublicationDate = new QDateEdit;
        m_checkFirstPublicationDate = new QCheckBox(tr("Date"));
        QObject::connect(m_editFirstPublicationDate, SIGNAL(dateChanged(QDate)),
                         this, SLOT(firstPublicationDateChanged()));
        m_editFirstPublicationDate->setCalendarPopup(true);
        gl->addWidget(m_checkFirstPublicationDate, 0, 0);
        gl->addWidget(m_editFirstPublicationDate, 0, 1);
        m_editFirstPublicationTime = new QTimeEdit;
        m_checkFirstPublicationTime = new QCheckBox(tr("Time"));
        QObject::connect(m_editFirstPublicationTime, SIGNAL(timeChanged(QTime)),
                         this, SLOT(firstPublicationTimeChanged()));
        gl->addWidget(m_checkFirstPublicationTime, 1, 0);
        gl->addWidget(m_editFirstPublicationTime, 1, 1);
        m_editFirstPublicationChannel = new QComboBox;
        m_editFirstPublicationChannel->addItems(mainWindow->ebuCoreMain()->formatIdRefs());
        m_checkFirstPublicationChannel = new QCheckBox(tr("Channel format"));
        QObject::connect(m_editFirstPublicationChannel, SIGNAL(currentIndexChanged(int)),
                         this, SLOT(firstPublicationChannelChanged()));
        gl->addWidget(m_checkFirstPublicationChannel, 2, 0);
        gl->addWidget(m_editFirstPublicationChannel, 2, 1);
        m_editFirstPublicationChannelString = new QLineEdit;
        gl->addWidget(new QLabel(tr("Channel title")), 3, 0);
        gl->addWidget(m_editFirstPublicationChannelString, 3, 1);
        group->setLayout(gl);
        // l->addWidget(group);
        mainHLayout->addWidget(group);
    }
    // Add list view on the right
    m_listView = new ListView(tr("Repetitions"));
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    mainHLayout->addWidget(m_listView);
    this->setLayout(mainHLayout);

    // Install Event filters
    m_textDocumentation->setText(tr("To provide information about the publication history."));
    m_editFirstPublicationDate->installEventFilter(this);
    m_editFirstPublicationTime->installEventFilter(this);
    m_editFirstPublicationChannelString->installEventFilter(this);
    m_editFirstPublicationChannel->installEventFilter(this);

    // Set data fields...
    if (m_publicationHistory->firstPublication()) {
        if (m_publicationHistory->firstPublication()->date().isValid()) {
            m_editFirstPublicationDate->setDate(m_publicationHistory->firstPublication()->date().date());
            m_checkFirstPublicationDate->setChecked(true);
        }
        if (m_publicationHistory->firstPublication()->time().isValid()) {
            m_editFirstPublicationTime->setTime(m_publicationHistory->firstPublication()->time().time());
            m_checkFirstPublicationTime->setChecked(true);
        }
        m_editFirstPublicationChannelString->setText(m_publicationHistory->firstPublication()->channelString());
        if (m_publicationHistory->firstPublication()->channel()) {
            m_checkFirstPublicationChannel->setChecked(true);
            int index = m_editFirstPublicationChannel->findText(m_publicationHistory->firstPublication()->channel()->formatId());
            m_editFirstPublicationChannel->setCurrentIndex(index);
        }
    }
    int s = m_publicationHistory->repetitions().size();
    for (int i=0; i < s; ++i) {
        PublicationType *rep = m_publicationHistory->repetitions().at(i);
        if (!rep)
            continue;
        m_listView->addItem(rep->toString());
    }
}

QString PublicationHistoryTypeForm::toString()
{
    return QString(tr("Publication History"));
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
    if (m_checkFirstPublicationTime->isChecked())
        pt->setTime(m_editFirstPublicationTime->dateTime());
    else
        pt->clearTime();
    if (m_checkFirstPublicationDate->isChecked())
        pt->setDate(m_editFirstPublicationDate->dateTime());
    else
        pt->clearDate();
    if (m_checkFirstPublicationChannel->isChecked()) {
        QString formatIdRef = m_editFirstPublicationChannel->currentText();
        const FormatType *format = mainWindow()->ebuCoreMain()->formatById(formatIdRef, pt);
        if (pt->channel()) {
            mainWindow()->ebuCoreMain()->unlinkListener(pt->channel()->formatId(), pt);
        }
        if (format) {
            pt->setChannel(format);
        } else {
            pt->setChannel(0);
        }
    } else {
        pt->setChannel(0);
    }
    pt->setChannelString(m_editFirstPublicationChannelString->text());
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
    delete(m_publicationHistory->repetitions().takeAt(row));
}

void PublicationHistoryTypeForm::firstPublicationTimeChanged()
{
    m_checkFirstPublicationTime->setChecked(true);
}

void PublicationHistoryTypeForm::firstPublicationDateChanged()
{
    m_checkFirstPublicationDate->setChecked(true);
}

void PublicationHistoryTypeForm::firstPublicationChannelChanged()
{
    m_checkFirstPublicationChannel->setChecked(true);
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

bool PublicationHistoryTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editFirstPublicationDate)
            m_textDocumentation->setText(tr("The first publication date."));
        if (obj == (QObject*) m_editFirstPublicationTime)
            m_textDocumentation->setText(tr("The first publication time."));
        if (obj == (QObject*) m_editFirstPublicationChannelString)
            m_textDocumentation->setText(tr("The channel on which the title was first transmitted."));
        if (obj == (QObject*) m_editFirstPublicationChannel)
            m_textDocumentation->setText(tr("A reference to an existing format."));
    }
    return QObject::eventFilter(obj, event);
}

