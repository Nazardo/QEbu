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

#include "alternativetitletypeform.h"
#include "../model/coremetadatatype.h"
#include "dategroupeditbox.h"
#include "statusgroupeditbox.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QTextBrowser>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QEvent>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QTextBrowser>

AlternativeTitleTypeForm::AlternativeTitleTypeForm(
        AlternativeTitleType *alternativeTitle,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (alternativeTitle) ? Edit : Add;
    if (!alternativeTitle)
        m_alternativeTitle = new AlternativeTitleType;
    else
        m_alternativeTitle = alternativeTitle;

    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    m_editTitle = new ElementTypeEditBox;
    m_editTitle->setLabel(tr("Title"));
    leftVLayout->addWidget(m_editTitle);
    m_editTypeGroup = new TypeGroupEditBox(m_alternativeTitle);
    m_editTypeGroup->addLinksMap(mainWindow->getMap("ebu_ObjectTypeCodeCS")); //Autocompletion values
    leftVLayout->addWidget(m_editTypeGroup);
    m_editStatusGroup = new StatusGroupEditBox(m_alternativeTitle);
    m_editStatusGroup->addLinksMap(mainWindow->getMap("ebu_TitleStatusCodeCS")); //Autocompletion values
    leftVLayout->addWidget(m_editStatusGroup);

    hLayout->addLayout(leftVLayout);
    QVBoxLayout *rightVLayout = new QVBoxLayout;
    m_editDateGroup = new DateGroupEditBox(m_alternativeTitle);
    rightVLayout->addWidget(m_editDateGroup);
    {
        QFormLayout *form = new QFormLayout;
        m_textNote = new QTextEdit;
        form->addRow(tr("Note"), m_textNote);
        rightVLayout->addLayout(form);
    }
    hLayout->addLayout(rightVLayout);
    hLayout->setAlignment(leftVLayout, Qt::AlignTop);
    hLayout->setAlignment(rightVLayout, Qt::AlignTop);
    this->setLayout(hLayout);

    // Event Filter
    m_textDocumentation->setText(tr("An Alternative Title is the name other than the 'main' Title given to a resource.\nThe type of title is defined by the typeGroup of attributes.\nThe status of the title is defined by the statusGroup of attributes.\nAlternative Titles are recorded as they appear.\nAn Alternative Title may be attributed to a resource for several reasons described using the status (e.g. working title) and type (e.g. series title) attributes.\nThe alternativeTitle may be provided in several languages.\nIt is sometimes common practice to put dates into the alternativeTitle. If present, the attributionDate (indicating when the alternativeTitle was attributed) in the date attribute should be consistent."));
    m_textNote->installEventFilter(this);
    m_textDocumentation->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editStatusGroup->editStatusDefinition()->installEventFilter(this);
    m_editStatusGroup->editStatusLabel()->installEventFilter(this);
    m_editStatusGroup->editStatusLink()->installEventFilter(this);
    m_editTitle->editValue()->installEventFilter(this);
    m_editTitle->editLang()->installEventFilter(this);
    m_editDateGroup->editEndDate()->installEventFilter(this);
    m_editDateGroup->editEndTime()->installEventFilter(this);
    m_editDateGroup->editEndYear()->installEventFilter(this);
    m_editDateGroup->editPeriod()->installEventFilter(this);
    m_editDateGroup->editStartDate()->installEventFilter(this);
    m_editDateGroup->editStartTime()->installEventFilter(this);
    m_editDateGroup->editStartYear()->installEventFilter(this);

    // Set text fields
    if (m_op == Add)
        return;
    m_textNote->setText(m_alternativeTitle->note());
    if (m_alternativeTitle->title()) {
        m_editTitle->editValue()->setText(m_alternativeTitle->title()->value());
        m_editTitle->editLang()->setText(m_alternativeTitle->title()->lang());
    }
}

QString AlternativeTitleTypeForm::toString()
{
    return QString(tr("Alternative Title"));
}

bool AlternativeTitleTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_editTitle->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Title");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}

void AlternativeTitleTypeForm::applyClicked()
{
    if (!checkCompliance())
            return;
    m_alternativeTitle->setNote(m_textNote->toPlainText());
    m_editTypeGroup->updateExistingTypeGroup(m_alternativeTitle);
    m_editStatusGroup->updateExistingStatusGroup(m_alternativeTitle);
    m_editDateGroup->updateExistingDateGroup(m_alternativeTitle);
    if (m_editTitle->editLang()->text().isEmpty() && m_editTitle->editValue()->text().isEmpty())
        m_alternativeTitle->setTitle(0);
    else
        m_alternativeTitle->setTitle(
                    new ElementType(m_editTitle->editValue()->text(),
                                    m_editTitle->editLang()->text()));
    emit closed(m_op, QVarPtr<AlternativeTitleType>::asQVariant(m_alternativeTitle));
}

void AlternativeTitleTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_alternativeTitle;
        m_alternativeTitle = 0;
    }
    emit closed(m_op, QVarPtr<AlternativeTitleType>::asQVariant(m_alternativeTitle));
}

bool AlternativeTitleTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote )
            m_textDocumentation->setText(tr("A note element to provide additional contextual information."));
        else if  (obj == (QObject*) m_editTitle->editValue())
            m_textDocumentation->setText(tr("Free-text to provide alternative titles by which the resource is known.\nExample: 'the fifth element'."));
        else if  (obj == (QObject*) m_editTitle->editLang())
            m_textDocumentation->setText("The language in which the title is provided.");
        else if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition.\nExample: the 'title' of the series that the resource is an episode of."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(tr("A link to a term or only identify a classification scheme.<br/>Reference data<br/> <a href=\"http://www.ebu.ch/metadata/cs/web/ebu_ObjectTypeCodeCS_p.xml.htm\">ebu_ObjectTypeCodeCS</a>"));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text to define the type of resource.\nExample: 'series'."));
        else if (obj == (QObject*) m_editStatusGroup->editStatusDefinition())
            m_textDocumentation->setText(tr("An optional definition.\nExample: a temporary title, which is different from the formal title under wbeen published."));
        else if (obj == (QObject*) m_editStatusGroup->editStatusLink())
            m_textDocumentation->setHtml(tr("A link to a term or only identify a classification scheme.<br/>Reference data<br/> <a href=\"http://www.ebu.ch/metadata/cs/web/ebu_TitleStatusCodeCS_p.xml.htm\">ebu_TitleStatusCodeCS</a>"));
        else if (obj == (QObject*) m_editStatusGroup->editStatusLabel())
            m_textDocumentation->setText(tr("Free text to define the status of the title of the resource.\nExample: statusLabel: working (for 'working title')."));
        else if ( obj == (QObject*) m_editDateGroup->editEndDate())
            m_textDocumentation->setText(tr("To express an end date."));
        else if ( obj ==(QObject*) m_editDateGroup->editEndTime())
            m_textDocumentation->setText(tr("To express an end time."));
        else if ( obj == (QObject*) m_editDateGroup->editEndYear())
            m_textDocumentation->setText(tr("To express an end year."));
        else if ( obj == (QObject*) m_editDateGroup->editPeriod())
            m_textDocumentation->setText(tr("To express a time period."));
        else if ( obj == (QObject*) m_editDateGroup->editStartDate())
            m_textDocumentation->setText(tr("To express a start date."));
        else if ( obj == (QObject*) m_editDateGroup->editStartTime())
            m_textDocumentation->setText(tr("To express a start time."));
        else if ( obj == (QObject*) m_editDateGroup->editStartYear())
            m_textDocumentation->setText(tr("To express a start year."));
    }
    return QObject::eventFilter(obj, event);
}
