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

#include "elementtypeform.h"
#include "../model/elementtype.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QTextBrowser>
#include <QEvent>
#include <QVBoxLayout>

ElementTypeForm::ElementTypeForm(ElementType *element,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (element) ? Edit : Add;
    if (element)
        m_element = element;
    else
        m_element = new ElementType;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editElementType = new ElementTypeEditBox;
    vl->addWidget(m_editElementType);
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(m_docGeneral);
    m_editElementType->editLang()->installEventFilter(this);
    m_editElementType->editValue()->installEventFilter(this);

    // Set values in text fields
    m_editElementType->editValue()->setText(m_element->value());
    m_editElementType->editLang()->setText(m_element->lang());
    m_title = QString(tr("Element"));
}

QString ElementTypeForm::toString()
{
    return m_title;
}

void ElementTypeForm::setTitle(const QString &title)
{
    m_editElementType->setLabel(title);
    m_title = title;
}

void ElementTypeForm::setGenericTextDocumentation(const QString &doc)
{
    m_docGeneral = doc;
    m_textDocumentation->setText(doc);
}

void ElementTypeForm::setValueDocumentation(const QString &value)
{
    m_docValue = value;
}

void ElementTypeForm::setLangDocumentation(const QString &lang)
{
    m_docLang = lang;
}

void ElementTypeForm::applyClicked()
{
    m_element->setValue(m_editElementType->editValue()->text());
    m_element->setLang(m_editElementType->editLang()->text());
    emit closed(m_op, QVarPtr<ElementType>::asQVariant(m_element));
}

void ElementTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_element;
        m_element = 0;
    }
    emit closed(m_op, QVarPtr<ElementType>::asQVariant(m_element));
}

bool ElementTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editElementType->editLang())
            m_textDocumentation->setText(m_docLang);
        else if (obj == (QObject*) m_editElementType->editValue())
            m_textDocumentation->setText(m_docValue);
    }
    return QObject::eventFilter(obj, event);
}
