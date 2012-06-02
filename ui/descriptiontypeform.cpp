#include "descriptiontypeform.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFormLayout>


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
        m_editTypeGroup = new TypeGroupEditBox(description);
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
    this->setLayout(vl);
    // Set text fields...
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
    m_editTypeGroup->updateExistingTypeGroup(m_description);
    m_description->setNote(m_textNote->toPlainText());
    m_description->setDescription(new ElementType(
                              m_editElementDescription->editValue()->text(),
                              m_editElementDescription->editLang()->text()));
    emit closed(m_op, QVarPtr<DescriptionType>::asQVariant(m_description));
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
