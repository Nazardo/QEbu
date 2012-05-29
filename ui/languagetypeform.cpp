#include "languagetypeform.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QtGui>


LanguageTypeForm::LanguageTypeForm(LanguageType *language, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (language) ? Edit : Add;
    if (!language)
        m_language = new LanguageType;
    else
        m_language = language;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(language);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    {
        m_editElementLanguage = new ElementTypeEditBox;
        m_editElementLanguage->setLabel(tr("Language"));
        vl->addWidget(m_editElementLanguage);
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
        vl->addLayout(hl);
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
    return QString(tr("Language Type"));
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
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_language);
    m_language->setNote(m_textNote->toPlainText());
    m_language->setLanguage(new ElementType(
                              m_editElementLanguage->editValue()->text(),
                              m_editElementLanguage->editLang()->text()));
    emit closed(m_op, QVarPtr<LanguageType>::asQVariant(m_language));
}

bool LanguageTypeForm::checkCompliance()
{
    bool ok = true;

    return ok;
}
