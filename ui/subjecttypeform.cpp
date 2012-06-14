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

#include "subjecttypeform.h"
#include "../model/ebucoremaintype.h"
#include "../model/typeconverter.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include "entitytypeform.h"
#include "qvarptr.h"
#include <QTextBrowser>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QString>
#include <QComboBox>
#include <QEvent>

SubjectTypeForm::SubjectTypeForm(SubjectType *subject, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (subject) ? Edit : Add;
    if(!subject)
        m_subject = new SubjectType;
    else
        m_subject = subject;

    QVBoxLayout *vl = new QVBoxLayout;
    m_editElementSubject = new ElementTypeEditBox;
    m_editElementSubject->setLabel(tr("Subject"));
    vl->addWidget(m_editElementSubject);
    {
        m_editTypeGroup = new TypeGroupEditBox(subject);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;

        m_editSubjectCode = new QComboBox;
        m_editSubjectCode->setEditable(true);
        m_editSubjectCode->setInsertPolicy(QComboBox::InsertAtTop);
        m_editSubjectCode->setValidator(TypeConverter::getUriValidator());
        m_editSubjectCode->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        m_linkMap = mainWindow->getMap("ebu_SubjectCodeCS");
        QList<QString> keys = m_linkMap->keys();
        for (int i=0; i < keys.size(); ++i) {
            QString key = keys.at(i);
            m_editSubjectCode->addItem(m_linkMap->value(key),key);
        }

        QObject::connect(m_editSubjectCode, SIGNAL(currentIndexChanged(int)), this, SLOT(onChange(int)));
        QObject::connect(m_editSubjectCode->lineEdit(), SIGNAL(editingFinished()), this, SLOT(onChange()));
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
    {
        QFormLayout *fl = new QFormLayout;

        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);

        vl->addLayout(fl);
    }
    this->setLayout(vl);

    //Event filter
    m_textDocumentation->setText(tr("The generalised topic that represents the intellectual content of the resource. Typically, a subject is expressed by keywords, key phrases. Free text, controlled vocabularies, authorities, or formal classification schemes (codes) may be employed when selecting descriptive subject terms. Persons as subjects are also placed here."));
    m_editElementSubject->editValue()->installEventFilter(this);
    m_editElementSubject->editLang()->installEventFilter(this);
    m_editSubjectCode->installEventFilter(this);
    m_editSubjectDefinition->installEventFilter(this);
    m_editAttributor->installEventFilter(this);
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_textNote->installEventFilter(this);

    // Set text fields...
    m_textNote->setText(m_subject->note());
    if (m_subject->subject()) {
        m_editElementSubject->editLang()->setText(m_subject->subject()->lang());
        m_editElementSubject->editValue()->setText(m_subject->subject()->value());
    }

    m_editSubjectCode->setCurrentIndex(m_editSubjectCode->findData(m_subject->subjectCode()));
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
    m_subject->setSubjectCode(m_editSubjectCode->itemData(m_editSubjectCode->currentIndex()).toString());
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

void SubjectTypeForm::onChange(int index) {
    if(!m_editSubjectCode->itemData(index).isValid()) {
        //New value
        QString linkText = m_editSubjectCode->itemText(index);
        m_editSubjectCode->setItemData(index, linkText);

        //Add it to the autocompletion map
        m_linkMap->insert(linkText,linkText);
    }
}

void SubjectTypeForm::onChange()
{
    QString s = m_editSubjectCode->lineEdit()->text();
    if (m_editSubjectCode->findText(s) < 0) {
        m_editSubjectCode->addItem(s, s);
        //Add it to the autocompletion maps
        m_linkMap->insert(s,s);
        int i = m_editSubjectCode->findText(s);
        if (i >= 0)
            m_editSubjectCode->setCurrentIndex(i);
    }
}

bool SubjectTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_textNote )
            m_textDocumentation->setText(tr("A note element to provide additional contextual information."));
        else if  (obj == (QObject*) m_editElementSubject->editValue() )
            m_textDocumentation->setText(tr("Free text to provide subject.\nExample: 'Tennis'."));
        else if  (obj == (QObject*) m_editElementSubject->editLang() )
            m_textDocumentation->setText(tr("The language in which the subject is provided."));
        else if  (obj == (QObject*) m_editSubjectCode )
            m_textDocumentation->setHtml(tr("A link or code to/within a classification scheme.<br/>Reference data:<ul><li>Library of Congress Subject Heading (LCSH), Library of Congress Classification (LCC), Medical Subject Headings (MeSH), Dewey Decimal Classification (DDC), Dansk decimalklassedeling 5.utgave (DK5), Klassifikasjonssystem för svenska bibliotek (SAB), Universal Decimal Classification (UDC), Norske emneord</li><li><a href=\"http://cv.iptc.org/newscodes/subjectcode/\">http://cv.iptc.org/newscodes/subjectcode/</a></li></ul>"));
        else if (obj == (QObject*) m_editSubjectDefinition )
            m_textDocumentation->setText(tr("An optional definition.\nExample: 'the subject is about tennis (sport, game)'."));
        else if (obj == (QObject*) m_editAttributor )
            m_textDocumentation->setText(tr("A person or organisation having defined/attributed the subject (e.g. a user tag)."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("An optional definition for the source of reference for subject.\nExample: the IPTC subject codes formatted using the EBU classification Scheme schema."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setHtml(tr("A link to a classification scheme.<br/>Example: <a href=\"http://cv.iptc.org/newscodes/subjectcode/\">http://cv.iptc.org/newscodes/subjectcode/</a>"));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text to define the type of the source of reference for subject.\nExample: 'IPTC Subject Code Classification Scheme' (EBU subset)."));
    }
    return QObject::eventFilter(obj, event);
}
