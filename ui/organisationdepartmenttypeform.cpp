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

#include "organisationdepartmenttypeform.h"
#include "../model/organisationdetailstype.h"
#include "../model/typeconverter.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QEvent>
#include <QTextBrowser>


OrganisationDepartmentTypeForm::OrganisationDepartmentTypeForm(
        OrganisationDepartmentType *organisationDepartment,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (organisationDepartment) ? Edit : Add;
    if (!organisationDepartment)
        m_organisationDepartment = new OrganisationDepartmentType;
    else
        m_organisationDepartment = organisationDepartment;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editDepartmentId = new QLineEdit(this);
        m_editDepartmentId->setValidator(TypeConverter::getUriValidator());
        QFormLayout *formL = new QFormLayout;
        formL->addRow(tr("Department ID"), m_editDepartmentId);
        vl->addLayout(formL);
    }
    m_editElementType = new ElementTypeEditBox;
    m_editElementType->setLabel(tr("Organisation department"));

    vl->addWidget(m_editElementType);
    this->setLayout(vl);

    // Install Event filters
    m_textDocumentation->setText(tr("To identify a specific department within an organisation."));
    m_editDepartmentId->installEventFilter(this);
    m_editElementType->editValue()->installEventFilter(this);
    m_editElementType->editLang()->installEventFilter(this);

    // Set values in text fields
    m_editDepartmentId->setText(m_organisationDepartment->departmentId());
    m_editElementType->editValue()->setText(m_organisationDepartment->value());
    m_editElementType->editLang()->setText(m_organisationDepartment->lang());
}

QString OrganisationDepartmentTypeForm::toString()
{
    return QString(tr("Organisation Department"));
}

void OrganisationDepartmentTypeForm::applyClicked()
{
    m_organisationDepartment->setDepartmentId(m_editDepartmentId->text());
    m_organisationDepartment->setLang(m_editElementType->editLang()->text());
    m_organisationDepartment->setValue(m_editElementType->editValue()->text());
    emit closed(m_op, QVarPtr<OrganisationDepartmentType>::asQVariant(m_organisationDepartment));
}

void OrganisationDepartmentTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_organisationDepartment;
        m_organisationDepartment = 0;
    }
    emit closed(m_op, QVarPtr<OrganisationDepartmentType>::asQVariant(m_organisationDepartment));
}


bool OrganisationDepartmentTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editDepartmentId)
            m_textDocumentation->setText(tr("To identify a specific department within an organisation."));
        else if (obj == (QObject*) m_editElementType->editValue())
            m_textDocumentation->setText(tr("To identify a specific department within an organisation."));
        else if (obj == (QObject*) m_editElementType->editLang())
            m_textDocumentation->setText(tr("The language in which the department name is provided."));
    }
    return QObject::eventFilter(obj, event);
}
