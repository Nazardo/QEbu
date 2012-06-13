/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
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

#include "publicationtypeform.h"
#include "../model/ebucoremaintype.h"
#include "listview.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "contactdetailstypeform.h"
#include "../model/typeconverter.h"
#include <QTimeEdit>
#include <QDateEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QEvent>
#include <QTextBrowser>

PublicationTypeForm::PublicationTypeForm(PublicationType *publication,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (publication) ? Edit : Add;
    if (!publication)
        m_publication = new PublicationType;
    else
        m_publication = publication;
    // Layout
    QGroupBox *group = new QGroupBox(tr("Publication"));
    QGridLayout *gl = new QGridLayout;
    m_editPublicationDate = new QDateEdit;
    m_editPublicationDate->setCalendarPopup(true);
    m_checkPublicationDate = new QCheckBox(tr("Date"));
    QObject::connect(m_editPublicationDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(publicationDateChanged()));
    gl->addWidget(m_checkPublicationDate, 0, 0);
    gl->addWidget(m_editPublicationDate, 0, 1);
    m_editPublicationTime = new QTimeEdit;
    m_checkPublicationTime = new QCheckBox(tr("Time"));
    QObject::connect(m_editPublicationTime, SIGNAL(timeChanged(QTime)),
                     this, SLOT(publicationTimeChanged()));
    gl->addWidget(m_checkPublicationTime, 1, 0);
    gl->addWidget(m_editPublicationTime, 1, 1);
    m_editPublicationChannel = new QComboBox;
    m_editPublicationChannel->addItems(mainWindow->ebuCoreMain()->formatIdRefs());
    m_checkPublicationChannel = new QCheckBox(tr("Channel format"));
    QObject::connect(m_editPublicationChannel, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(publicationChannelChanged()));
    gl->addWidget(m_checkPublicationChannel, 2, 0);
    gl->addWidget(m_editPublicationChannel, 2, 1);
    m_editPublicationChannelString = new QLineEdit;
    gl->addWidget(new QLabel(tr("Channel title")), 3, 0);
    gl->addWidget(m_editPublicationChannelString, 3, 1);
    group->setLayout(gl);
    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(group);
    this->setLayout(l);

    // Install Event filters
    m_textDocumentation->setText(tr("To provide information about a repeated publication."));
    m_editPublicationDate->installEventFilter(this);
    m_editPublicationTime->installEventFilter(this);
    m_editPublicationChannelString->installEventFilter(this);
    m_editPublicationChannel->installEventFilter(this);

    // Set data fields...
    if (m_publication) {
        if (m_publication->date().isValid()) {
            m_editPublicationDate->setDate(m_publication->date().date());
            m_checkPublicationDate->setChecked(true);
        }
        if (m_publication->time().isValid()) {
            m_editPublicationTime->setTime(m_publication->time().time());
            m_checkPublicationTime->setChecked(true);
        }
        if (m_publication->channel()) {
            m_checkPublicationChannel->setChecked(true);
            int index = m_editPublicationChannel->findText(m_publication->channel()->formatId());
            m_editPublicationChannel->setCurrentIndex(index);
        }
        m_editPublicationChannelString->setText(m_publication->channelString());
    }
}

QString PublicationTypeForm::toString()
{
    return QString(tr("Publication"));
}

void PublicationTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_publication;
        m_publication = 0;
    }
    emit closed(m_op, QVarPtr<PublicationType>::asQVariant(m_publication));
}

void PublicationTypeForm::applyClicked()
{
    if (m_checkPublicationTime->isChecked())
        m_publication->setTime(m_editPublicationTime->dateTime());
    else
        m_publication->clearTime();
    if (m_checkPublicationDate->isChecked())
        m_publication->setDate(m_editPublicationDate->dateTime());
    else
        m_publication->clearDate();
    if (m_checkPublicationChannel->isChecked()) {
        QString formatIdRef = m_editPublicationChannel->currentText();
        const FormatType *format = mainWindow()->ebuCoreMain()->formatById(formatIdRef, m_publication);
        // Unlink old format
        if (m_publication->channel()) {
            mainWindow()->ebuCoreMain()->unlinkListener(m_publication->channel()->formatId(), m_publication);
        }
        if (format) {
            m_publication->setChannel(format);
        } else {
            m_publication->setChannel(0);
        }
    } else {
        m_publication->setChannel(0);
    }
    m_publication->setChannelString(m_editPublicationChannelString->text());
    emit closed(m_op, QVarPtr<PublicationType>::asQVariant(m_publication));
}

void PublicationTypeForm::publicationTimeChanged()
{
    m_checkPublicationTime->setChecked(true);
}

void PublicationTypeForm::publicationDateChanged()
{
    m_checkPublicationDate->setChecked(true);
}

void PublicationTypeForm::publicationChannelChanged()
{
    m_checkPublicationChannel->setChecked(true);
}


bool PublicationTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editPublicationDate)
            m_textDocumentation->setText(tr("The repeat publication date."));
        else if (obj == (QObject*) m_editPublicationTime)
            m_textDocumentation->setText(tr("The repeat publication time."));
        else if (obj == (QObject*) m_editPublicationChannelString)
            m_textDocumentation->setText(tr("The channel on which the title was re-transmitted."));
        else if (obj == (QObject*) m_editPublicationChannel)
            m_textDocumentation->setText(tr("A reference to an existing format."));
    }
    return QObject::eventFilter(obj, event);
}
