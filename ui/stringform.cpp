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

#include "stringform.h"
#include "../model/technicalattributes.h"
#include "formatgroupeditbox.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QEvent>
#include <QComboBox>
#include <QTextBrowser>

StringForm::StringForm(String *string,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (string) ? Edit : Add;
    if (!string)
        m_string = new String;
    else
        m_string = string;

    // Layout
    QVBoxLayout *l = new QVBoxLayout;

    {
        QFormLayout *fl = new QFormLayout;
        m_editValue = new QLineEdit;
        m_editValue->installEventFilter(this);
        fl->addRow(tr("Value"), m_editValue);
        l->addLayout(fl);
    }
    {
        m_editFormatGroup = new FormatGroupEditBox(string);
        m_editFormatGroup->editFormatDefinition()->installEventFilter(this);
        m_editFormatGroup->editFormatLabel()->installEventFilter(this);
        m_editFormatGroup->editFormatLink()->installEventFilter(this);
        m_editTypeGroup = new TypeGroupEditBox(string);
        m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
        m_editTypeGroup->editTypeLabel()->installEventFilter(this);
        m_editTypeGroup->editTypeLink()->installEventFilter(this);
        m_editTypeGroup->addLinksMap(mainWindow->getMap("ebu_ColourCodeCS"));
        m_editTypeGroup->addLinksMap(mainWindow->getMap("ebu_VideoFrameRateCS"));
        l->addWidget(m_editTypeGroup);
        l->addWidget(m_editFormatGroup);
    }
    this->setLayout(l);
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters as ‘string’ for which a format can be defined to restrict the string format."));
    // Set data fields...
    m_editValue->setText(m_string->value());
}

QString StringForm::toString()
{
    return QString(tr("String"));
}

void StringForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_string;
        m_string = 0;
    }
    emit closed(m_op, QVarPtr<String>::asQVariant(m_string));
}

void StringForm::applyClicked()
{
    m_string->setValue(m_editValue->text());
    m_editFormatGroup->updateExistingFormatGroup(m_string);
    m_editTypeGroup->updateExistingTypeGroup(m_string);
    emit closed(m_op, QVarPtr<String>::asQVariant(m_string));
}

bool StringForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editFormatGroup->editFormatDefinition())
            m_textDocumentation->setText(tr("An optional definition."));
        if ( obj == (QObject*) m_editFormatGroup->editFormatLabel())
            m_textDocumentation->setText(tr("Free text."));
        if ( obj == (QObject*) m_editFormatGroup->editFormatLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
        if ( obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition"));
        if ( obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text"));
        if ( obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(tr("A link to a classification scheme<br/>Reference data<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_ColourCodeCS_p.xml.htm\">ebu_ColourCodeCS</a><br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_VideoFrameRateCS_p.xml.htm\">ebu_VideoFrameRateCS</a>"));
        if ( obj == (QObject*) m_editValue)
            m_textDocumentation->setText(tr("A string containing the value of the string technical attribute, which format may be further specified using the formatGroup attributes. This applies to all technicalAttributeString inc. audio and video"));
    }
    return QObject::eventFilter(obj, event);
}

