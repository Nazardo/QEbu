#include "subjecttypeform.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>

SubjectTypeForm::SubjectTypeForm(SubjectType *subject, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (subject) ? Edit : Add;
    if(!subject)
        m_subject = new SubjectType;
    else
        m_subject = subject;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(subject);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;

        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);

        vl->addLayout(fl);
    }
    m_editElementSubject = new ElementTypeEditBox;
    m_editElementSubject->setLabel(tr("Subject"));
    vl->addWidget(m_editElementSubject);
    {
        QFormLayout *fl = new QFormLayout;

        m_editSubjectCode = new QLineEdit;  ///PUT AUTOCOMPLETION HERE
        fl->addRow(tr("Subject code"), m_editSubjectCode);

        m_editSubjectDefinition = new QLineEdit;
        fl->addRow(tr("Subject definition"), m_editSubjectDefinition);

        vl->addLayout(fl);
    }
    {
        QHBoxLayout *hl = new QHBoxLayout;

        hl->addWidget(new QLabel(tr("Attributor")));
        m_editAttributor = new QLineEdit;
        m_editAttributor->setReadOnly(true);
        hl->addWidget(m_editAttributor);

        QPushButton *buttonAttributor = new QPushButton(tr("Add/Edit"));
        QObject::connect(buttonAttributor, SIGNAL(clicked()),
                         this, SLOT(attributorClicked()));
        hl->addWidget(buttonAttributor);
        QPushButton *buttonAttributorRemove = new QPushButton(tr("Remove"));
        QObject::connect(buttonAttributorRemove, SIGNAL(clicked()),
                         this, SLOT(attributorRemoveClicked()));
        hl->addWidget(buttonAttributorRemove);
        vl->addLayout(hl);
    }
    this->setLayout(vl);
    // Set text fields...
    m_textNote->setText(m_subject->note());
    if (m_subject->subject()) {
        m_editElementSubject->editLang()->setText(m_subject->subject()->lang());
        m_editElementSubject->editValue()->setText(m_subject->subject()->value());
    }
    m_editSubjectCode->setText(m_subject->subjectCode());
    m_editSubjectDefinition->setText(m_subject->subjectDefinition());
    if (m_subject->attributor())
        m_editAttributor->setText(m_subject->attributor()->toString());
}

QString SubjectTypeForm::toString()
{
    return QString(tr("Subject"));
}

void SubjectTypeForm::attributorRemoveClicked()
{
    if (!m_subject->attributor())
        return;
    m_subject->setAttributor(0);
    m_editAttributor->setText(tr("(none)"));
}

void SubjectTypeForm::attributorClicked()
{
    EntityTypeForm *attributorForm = new EntityTypeForm(
                m_subject->attributor(),this->mainWindow());
    attributorForm->setTitle(tr("Attributor"));
    QObject::connect(attributorForm, SIGNAL(closed(Operation,QVariant)),
                     this, SLOT(attributorClosed(Operation,QVariant)));
    this->mainWindow()->pushWidget(attributorForm);
}

void SubjectTypeForm::attributorClosed(Operation op, QVariant value)
{
    EntityType *attributor = QVarPtr<EntityType>::asPointer(value);
    if (!attributor)
        return;
    if (op == Add)
        m_subject->setAttributor(attributor);
    m_editAttributor->setText(attributor->toString());
}

void SubjectTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_subject;
        m_subject = 0;
    }
    emit closed(m_op, QVarPtr<SubjectType>::asQVariant(m_subject));
}

void SubjectTypeForm::applyClicked()
{
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_subject);
    m_subject->setNote(m_textNote->toPlainText());
    m_subject->setSubject(new ElementType(
                              m_editElementSubject->editValue()->text(),
                              m_editElementSubject->editLang()->text()));
    m_subject->setSubjectCode(m_editSubjectCode->text());
    m_subject->setSubjectDefinition(m_editSubjectDefinition->text());
    emit closed(m_op, QVarPtr<SubjectType>::asQVariant(m_subject));
}

bool SubjectTypeForm::checkCompliance()
{
    bool ok = true;
    QStringList fields;
    if (m_editElementSubject->editValue()->text().isEmpty()) {
        ok = false;
        fields += tr("Subject");
    }
    if(!ok) {
        QMessageBox::warning(this, this->toString(),
                             tr("<b>Required fields:</b><br>")
                             +fields.join(",<br>"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    return ok;
}
