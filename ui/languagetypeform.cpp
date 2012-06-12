#include "languagetypeform.h"
#include "../model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QTextEdit>
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
            m_textDocumentation->setText(tr("Free text used to identify the purpose of use of the language.\n.Example: ‘the main language as originally created/captured for the resource’"));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: ‘main original language’."));
        else if  (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a classification scheme."));
    }
    return QObject::eventFilter(obj, event);
}
