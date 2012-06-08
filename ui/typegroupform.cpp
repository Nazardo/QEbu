#include "typegroupform.h"
#include "../model/typegroup.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLayout>
#include <QString>

TypeGroupForm::TypeGroupForm(TypeGroup *typeGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (typeGroup) ? Edit : Add;
    QVBoxLayout *vl = new QVBoxLayout;
    m_title = QString(tr("Type Group"));
    m_editTypeGroup = new TypeGroupEditBox(typeGroup);
    m_editTypeGroup->setLabel(m_title);
    vl->addWidget(m_editTypeGroup);
    this->setLayout(vl);
}

void TypeGroupForm::addLinksMap(QMap<QString, QString> *values) {
    m_editTypeGroup->addLinksMap(values); //Autocompletion values
}

QString TypeGroupForm::toString()
{
    return m_title;
}

void TypeGroupForm::setTitle(const QString &title)
{
    m_title = title;
    m_editTypeGroup->setLabel(title);
}

void TypeGroupForm::applyClicked()
{
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(m_editTypeGroup->typeGroup()));
}

void TypeGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<TypeGroup>::asQVariant(0));
}
