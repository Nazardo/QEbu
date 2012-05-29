#include "typegroupeditbox.h"
#include <QFormLayout>
#include <QGroupBox>

TypeGroupEditBox::TypeGroupEditBox(QWidget *parent) :
    QWidget(parent)
{
    m_typeLabel = new QLineEdit(this);
    m_typeDefinition = new QLineEdit(this);
    m_typeLink = new QLineEdit(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    QGroupBox *group = new QGroupBox(tr("Type"));
    formL->addRow(tr("Label"), m_typeLabel);
    formL->addRow(tr("Definition"), m_typeDefinition);
    formL->addRow(tr("Link"), m_typeLink);
    group->setLayout(formL);
    l->addWidget(group);
    this->setLayout(l);
}

QLineEdit *TypeGroupEditBox::typeLabel()
{
    return m_typeLabel;
}

QLineEdit *TypeGroupEditBox::typeDefinition()
{
    return m_typeDefinition;
}

QLineEdit *TypeGroupEditBox::typeLink()
{
    return m_typeLink;
}
