#include "formatgroupeditbox.h"
#include <QFormLayout>
#include <QGroupBox>

FormatGroupEditBox::FormatGroupEditBox(FormatGroup *formatGroup, QWidget *parent) :
    QWidget(parent)
{
    m_editFormatLabel = new QLineEdit(this);
    m_editFormatDefinition = new QLineEdit(this);
    m_editFormatLink = new QLineEdit(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    QGroupBox *group = new QGroupBox(tr("Format"));
    formL->addRow(tr("Label"), m_editFormatLabel);
    formL->addRow(tr("Definition"), m_editFormatDefinition);
    formL->addRow(tr("Link"), m_editFormatLink);
    group->setLayout(formL);
    l->addWidget(group);
    this->setLayout(l);
    if (!formatGroup)
        return;
    m_editFormatLabel->setText(formatGroup->formatLabel());
    m_editFormatDefinition->setText(formatGroup->formatDefinition());
    m_editFormatLink->setText(formatGroup->formatLink());
}

FormatGroup *FormatGroupEditBox::formatGroup()
{
    FormatGroup *formatGroup = new FormatGroup;
    updateExistingFormatGroup(formatGroup);
    return formatGroup;
}

void FormatGroupEditBox::updateExistingFormatGroup(FormatGroup *formatGroup)
{
    formatGroup->setFormatLabel(m_editFormatLabel->text());
    formatGroup->setFormatDefinition(m_editFormatDefinition->text());
    formatGroup->setFormatLink(m_editFormatLink->text());
}
