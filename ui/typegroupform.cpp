#include "typegroupform.h"
#include "qvarptr.h"

TypeGroupForm::TypeGroupForm(TypeGroup *typeGroup, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (typeGroup) ? Edit : Add;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editTypeGroup = new TypeGroupEditBox(typeGroup);
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
}

QString TypeGroupForm::toString()
{
    return QString("TypeGroup");
}

void TypeGroupForm::applyClicked()
{
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(m_editTypeGroup->typeGroup()));
}

void TypeGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(0));
}
