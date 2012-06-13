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

#include "languagetypeform.h"
#include "../model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QEvent>
#include <QComboBox>
#include <QFormLayout>

LanguageTypeForm::LanguageTypeForm(LanguageType *language,
                                   QEbuMainWindow *mainWindow,
                                   QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (language) ? Edit : Add;
    if (!language)
        m_language = new LanguageType;
    else
        m_language = language;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editElementLanguage = new ElementTypeEditBox;
        m_editElementLanguage->setLabel(tr("Language"));
        vl->addWidget(m_editElementLanguage);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(language);
        m_editTypeGroup->addLinksMap(mainWindow->getMap("ebu_LanguagePurposeCodeCS"));
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    this->setLayout(vl);
    // Set text fields...
    m_textNote->setText(m_language->note());
    if (m_language->language()) {
        m_editElementLanguage->editLang()->setText(m_language->language()->lang());
        m_editElementLanguage->editValue()->setText(m_language->language()->value());
    }
}

QString LanguageTypeForm::toString()
{
    return QString(tr("Language"));
}

void LanguageTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_language;
        m_language = 0;
    }
    emit closed(m_op, QVarPtr<LanguageType>::asQVariant(m_language));
}

void LanguageTypeForm::applyClicked()
{
    m_editTypeGroup->updateExistingTypeGroup(m_language);
    m_language->setNote(m_textNote->toPlainText());
    m_language->setLanguage(new ElementType(
                              m_editElementLanguage->editValue()->text(),
                              m_editElementLanguage->editLang()->text()));
    emit closed(m_op, QVarPtr<LanguageType>::asQVariant(m_language));
}

bool LanguageTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote )
            m_textDocumentation->setText(tr("A note for additional contextual information."));
        else if  (obj == (QObject*) m_editElementLanguage->editLang())
            m_textDocumentation->setText(tr("A name attributed to a particular format."));
        else if  (obj == (QObject*) m_editElementLanguage->editValue())
            m_textDocumentation->setText(tr("Use to identify the language."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text used to identify the purpose of use of the language.\n.Example: 'the main language as originally created/captured for the resource'"));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: 'main original language'."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(tr("A link to a classification scheme.<br/>Reference data:<br/><a href=\"http://www.ebu.ch/metadata/cs/web/ebu_LanguagePurposeCodeCS_p.xml.htm\">ebu_LanguagePurposeCodeCS</a>"));
    }
    return QObject::eventFilter(obj, event);
}
