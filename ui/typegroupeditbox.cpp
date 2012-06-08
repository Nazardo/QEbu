#include "typegroupeditbox.h"
#include "../model/typegroup.h"
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>

TypeGroupEditBox::TypeGroupEditBox(TypeGroup *typeGroup,
                                   QWidget *parent) :
    QWidget(parent)
{
    m_editTypeLabel = new QLineEdit(this);
    m_editTypeDefinition = new QLineEdit(this);
    m_editTypeLink = new QLineEdit(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    m_groupBox = new QGroupBox(tr("Type"));
    formL->addRow(tr("Label"), m_editTypeLabel);
    formL->addRow(tr("Definition"), m_editTypeDefinition);
    formL->addRow(tr("Link"), m_editTypeLink);
    m_groupBox->setLayout(formL);
    l->addWidget(m_groupBox);
    this->setLayout(l);
    if (!typeGroup)
        return;
    // Set text fields
    m_editTypeLabel->setText(typeGroup->typeLabel());
    m_editTypeDefinition->setText(typeGroup->typeDefinition());
    m_editTypeLink->setText(typeGroup->typeLink());
}

TypeGroup *TypeGroupEditBox::typeGroup()
{
    TypeGroup *typeGroup = new TypeGroup();
    updateExistingTypeGroup(typeGroup);
    return typeGroup;
}

void TypeGroupEditBox::setLabel(const QString &label)
{
    m_groupBox->setTitle(label);
}

void TypeGroupEditBox::updateExistingTypeGroup(TypeGroup *typeGroup)
{
    typeGroup->setTypeDefinition(m_editTypeDefinition->text());
    typeGroup->setTypeLabel(m_editTypeLabel->text());
    typeGroup->setTypeLink(m_editTypeLink->text());
}
