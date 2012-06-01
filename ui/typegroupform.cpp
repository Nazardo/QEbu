#include "typegroupform.h"
#include "../model/typegroup.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLayout>

TypeGroupForm::TypeGroupForm(TypeGroup *typeGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (typeGroup) ? Edit : Add;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editTypeGroup = new TypeGroupEditBox(typeGroup);
    vl->addWidget(m_editTypeGroup);
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
