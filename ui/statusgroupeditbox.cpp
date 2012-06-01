#include "statusgroupeditbox.h"
#include "../model/statusgroup.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>

StatusGroupEditBox::StatusGroupEditBox(StatusGroup *statusGroup, QWidget *parent) :
    QWidget(parent)
{
    m_editStatusLabel = new QLineEdit(this);
    m_editStatusDefinition = new QLineEdit(this);
    m_editStatusLink = new QLineEdit(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    QGroupBox *group = new QGroupBox(tr("Status"));
    formL->addRow(tr("Label"), m_editStatusLabel);
    formL->addRow(tr("Definition"), m_editStatusDefinition);
    formL->addRow(tr("Link"), m_editStatusLink);
    group->setLayout(formL);
    l->addWidget(group);
    this->setLayout(l);
    if (!statusGroup)
        return;
    // Set text fields
    m_editStatusLabel->setText(statusGroup->statusLabel());
    m_editStatusDefinition->setText(statusGroup->statusDefinition());
    m_editStatusLink->setText(statusGroup->statusLink());
}

StatusGroup *StatusGroupEditBox::statusGroup()
{
    StatusGroup *statusGroup = new StatusGroup;
    updateExistingStatusGroup(statusGroup);
    return statusGroup;
}

void StatusGroupEditBox::updateExistingStatusGroup(StatusGroup *statusGroup)
{
    statusGroup->setStatusDefinition(m_editStatusDefinition->text());
    statusGroup->setStatusLabel(m_editStatusLabel->text());
    statusGroup->setStatusLink(m_editStatusLink->text());
}





