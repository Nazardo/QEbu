#include "typegroupeditbox.h"
#include <QFormLayout>
#include <QGroupBox>

TypeGroupEditBox::TypeGroupEditBox(TypeGroup *typeGroup, QWidget *parent) :
    QWidget(parent)
{
    m_editTypeLabel = new QLineEdit(this);
    m_editTypeDefinition = new QLineEdit(this);
    m_editTypeLink = new QLineEdit(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    QGroupBox *group = new QGroupBox(tr("Type"));
    formL->addRow(tr("Label"), m_editTypeLabel);
    formL->addRow(tr("Definition"), m_editTypeDefinition);
    formL->addRow(tr("Link"), m_editTypeLink);
    group->setLayout(formL);
    l->addWidget(group);
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

void TypeGroupEditBox::updateExistingTypeGroup(TypeGroup *typeGroup)
{
    typeGroup->setTypeDefinition(m_editTypeDefinition->text());
    typeGroup->setTypeLabel(m_editTypeLabel->text());
    typeGroup->setTypeLink(m_editTypeLink->text());
}
