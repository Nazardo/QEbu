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

#include "dategroupform.h"
#include "../model/dategroup.h"
#include "dategroupeditbox.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QTextBrowser>
#include <QEvent>

DateGroupForm::DateGroupForm(DateGroup *dateGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (dateGroup) ? Edit : Add;
    if (!dateGroup)
        m_dateGroup = new DateGroup;
    else
        m_dateGroup = dateGroup;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editDateGroup = new DateGroupEditBox(m_dateGroup);
    m_editDateGroup->editEndDate()->installEventFilter(this);
    m_editDateGroup->editEndTime()->installEventFilter(this);
    m_editDateGroup->editEndYear()->installEventFilter(this);
    m_editDateGroup->editPeriod()->installEventFilter(this);
    m_editDateGroup->editStartDate()->installEventFilter(this);
    m_editDateGroup->editStartTime()->installEventFilter(this);
    m_editDateGroup->editStartYear()->installEventFilter(this);
    vl->addWidget(m_editDateGroup);
    m_textDocumentation->setText(tr("To define a date and or time"));
    this->setLayout(vl);
    m_title = QString(tr("Date Group"));
}

QString DateGroupForm::toString()
{
    return m_title;
}

void DateGroupForm::setTitle(const QString &title)
{
    m_editDateGroup->setLabel(title);
    m_title = title;
}

void DateGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(0));
}

void DateGroupForm::applyClicked()
{
    m_editDateGroup->updateExistingDateGroup(m_dateGroup);
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(m_dateGroup));
}

bool DateGroupForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editDateGroup->editEndDate())
            m_textDocumentation->setText(tr("To express an end date"));
        else if ( obj ==(QObject*) m_editDateGroup->editEndTime())
            m_textDocumentation->setText(tr("To express an end time"));
        else if ( obj == (QObject*) m_editDateGroup->editEndYear())
            m_textDocumentation->setText(tr("To express an end year"));
        else if ( obj == (QObject*) m_editDateGroup->editPeriod())
            m_textDocumentation->setText(tr("To express a time period"));
        else if ( obj == (QObject*) m_editDateGroup->editStartDate())
            m_textDocumentation->setText(tr("To express a start date"));
        else if ( obj == (QObject*) m_editDateGroup->editStartTime())
            m_textDocumentation->setText(tr("To express a start time"));
        else if ( obj == (QObject*) m_editDateGroup->editStartYear())
            m_textDocumentation->setText(tr("To express a start year"));
    }
    return QObject::eventFilter(obj, event);
}
