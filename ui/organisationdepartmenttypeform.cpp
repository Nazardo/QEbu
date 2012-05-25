#include "organisationdepartmenttypeform.h"
#include "qvarptr.h"
#include <QtGui>

OrganisationDepartmentTypeForm::OrganisationDepartmentTypeForm(OrganisationDepartmentType *organisationDepartment,
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
        QFormLayout *formL = new QFormLayout;
        formL->addRow(tr("Department ID"), m_editDepartmentId);
        vl->addLayout(formL);
    }
    m_editElementType = new ElementTypeEditBox;
    vl->addWidget(m_editElementType);
    {
        QHBoxLayout *hl = new QHBoxLayout;
        m_buttonApply = new QPushButton(tr("Apply changes"));
        m_buttonCancel = new QPushButton(tr("Cancel"));
        hl->addWidget(m_buttonApply);
        hl->addWidget(m_buttonCancel);
        QObject::connect(m_buttonApply, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(m_buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        vl->addLayout(hl);
    }
    this->setLayout(vl);
    // Set values in text fields
    m_editDepartmentId->setText(m_organisationDepartment->departmentId());
    m_editElementType->editValue()->setText(m_organisationDepartment->value());
    m_editElementType->editLang()->setText(m_organisationDepartment->lang());
}

QString OrganisationDepartmentTypeForm::toString()
{
    return QString("Organisation Department Type");
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
