#include "typegroupform.h"
#include "qvarptr.h"

TypeGroupForm::TypeGroupForm(TypeGroup *typeGroup, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (typeGroup) ? Edit : Add;
    if (!typeGroup)
        m_typeGroup = new TypeGroup;
    else
        m_typeGroup = typeGroup;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editTypeGroup = new TypeGroupEditBox;
    vl->addWidget(m_editTypeGroup);
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
    m_editTypeGroup->typeLabel()->setText(m_typeGroup->typeLabel());
    m_editTypeGroup->typeDefinition()->setText(m_typeGroup->typeDefinition());
    m_editTypeGroup->typeLink()->setText(m_typeGroup->typeLink());
}

QString TypeGroupForm::toString()
{
    return QString("TypeGroup");
}

void TypeGroupForm::applyClicked()
{
    m_typeGroup->setTypeDefinition(m_editTypeGroup->typeDefinition()->text());
    m_typeGroup->setTypeLabel(m_editTypeGroup->typeLabel()->text());
    m_typeGroup->setTypeLink(m_editTypeGroup->typeLink()->text());
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(m_typeGroup));
}

void TypeGroupForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_typeGroup;
        m_typeGroup = 0;
    }
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(m_typeGroup));
}
