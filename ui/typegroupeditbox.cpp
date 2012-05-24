#include "typegroupeditbox.h"
#include <QFormLayout>

TypeGroupEditBox::TypeGroupEditBox(QWidget *parent) :
    QWidget(parent)
{
    m_typeLabel = new QLineEdit(this);
    m_typeDefinition = new QLineEdit(this);
    m_typeLink = new QLineEdit(this);
    QFormLayout *formL = new QFormLayout;
    formL->addRow(tr("Label"), m_typeLabel);
    formL->addRow(tr("Definition"), m_typeDefinition);
    formL->addRow(tr("Link"), m_typeLink);
    this->setLayout(formL);
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
