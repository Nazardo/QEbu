#include "descriptiontypeform.h"

#include "entitytypeform.h"
#include "qvarptr.h"
#include <QtGui>


DescriptionTypeForm::DescriptionTypeForm(DescriptionType *description, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (description) ? Edit : Add;

    if(!description)
        m_description = new DescriptionType;
    else
        m_description = description;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox;
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
    }
    {
        m_editElementDescription = new ElementTypeEditBox;
        m_editElementDescription->setLabel(tr("Description"));
        vl->addWidget(m_editElementDescription);
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
    m_editTypeGroup->typeLabel()->setText(m_description->typeLabel());
    m_editTypeGroup->typeDefinition()->setText(m_description->typeDefinition());
    m_editTypeGroup->typeLink()->setText(m_description->typeLink());
    m_textNote->setText(m_description->note());
    if (m_description->description()) {
        m_editElementDescription->editLang()->setText(m_description->description()->lang());
        m_editElementDescription->editValue()->setText(m_description->description()->value());
    }

}

QString DescriptionTypeForm::toString()
{
    return QString(tr("Description Type"));
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
    m_description->setTypeLabel(m_editTypeGroup->typeLabel()->text());
    m_description->setTypeDefinition(m_editTypeGroup->typeDefinition()->text());
    m_description->setTypeLink(m_editTypeGroup->typeLink()->text());
    m_description->setNote(m_textNote->toPlainText());
    m_description->setDescription(new ElementType(
                              m_editElementDescription->editValue()->text(),
                              m_editElementDescription->editLang()->text()));
    emit closed(m_op, QVarPtr<DescriptionType>::asQVariant(m_description));
}

bool DescriptionTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";
    if (m_editElementDescription->editValue()->text().isEmpty()) {
        ok = false;
        error_msg += "Description \n";
    }
    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Rrequired fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
