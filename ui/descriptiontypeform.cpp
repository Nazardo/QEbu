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

#include "descriptiontypeform.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QEvent>
#include <QTextBrowser>
#include <QComboBox>

DescriptionTypeForm::DescriptionTypeForm(DescriptionType *description,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (description) ? Edit : Add;

    if(!description)
        m_description = new DescriptionType;
    else
        m_description = description;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editElementDescription = new ElementTypeEditBox;
        m_editElementDescription->setLabel(tr("Description"));
        m_editElementDescription->editLang()->installEventFilter(this);
        m_editElementDescription->editValue()->installEventFilter(this);
        vl->addWidget(m_editElementDescription);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(description);
        m_editTypeGroup = new TypeGroupEditBox(m_description);
        m_editTypeGroup->addLinksMap(mainWindow->getMap("ebu_DescriptionTypeCodeCS")); //Autocompletion values
        m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
        m_editTypeGroup->editTypeLabel()->installEventFilter(this);
        m_editTypeGroup->editTypeLink()->installEventFilter(this);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        m_textNote->installEventFilter(this);
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    this->setLayout(vl);

    // Set text fields...
    m_textDocumentation->setText(tr("Free-form text or a narrative to report general notes, abstracts, or summaries about the intellectual content of a resource. The information may be in the form of a paragraph giving an individual program description, anecdotal interpretations, or brief content reviews. The description may also consist of outlines, lists, bullet points, edit decision lists, indexes, or tables of content, a reference to a graphical representation of content or even a pointer (URI, URL) to an external resource.\nA running order can also be provided as a description.\nFor a Radio or television programme a running order can be used as description.\nA description can be provided in different languages."));
    m_textNote->setText(m_description->note());
    if (m_description->description()) {
        m_editElementDescription->editLang()->setText(m_description->description()->lang());
        m_editElementDescription->editValue()->setText(m_description->description()->value());
    }

}

QString DescriptionTypeForm::toString()
{
    return QString(tr("Description"));
}

void DescriptionTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_description;
        m_description = 0;
    }
    emit closed(m_op, QVarPtr<DescriptionType>::asQVariant(m_description));
}

void DescriptionTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_description);
    m_description->setNote(m_textNote->toPlainText());
    m_description->setDescription(new ElementType(
                              m_editElementDescription->editValue()->text(),
                              m_editElementDescription->editLang()->text()));
    emit closed(m_op, QVarPtr<DescriptionType>::asQVariant(m_description));
}

bool DescriptionTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition."));
        else if ( obj == (QObject*) m_editTypeGroup->editTypeLabel() )
            m_textDocumentation->setText(tr("Free text to define the type."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(tr("A link to a term or only identify a classification scheme.<br/>Reference:<br/> <a href=\"http://www.ebu.ch/metadata/cs/web/ebu_DescriptionTypeCodeCS_p.xml.htm\">ebu_DescriptionTypeCodeCS</a>"));
        else if  (obj == (QObject*) m_editElementDescription->editLang())
            m_textDocumentation->setText(tr("The language in which the title is provided."));
        else if  (obj == (QObject*) m_editElementDescription->editValue())
            m_textDocumentation->setText(tr("Free-text to provide the main title by which the resource is known. The title can be provided in different languages.\nExample: 'the fifth element'."));
        else if  (obj == (QObject*) m_textNote)
            m_textDocumentation->setText(tr("A note element to provide additional contextual information"));
    }
    return QObject::eventFilter(obj, event);
}

bool DescriptionTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_editElementDescription->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Description");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}
