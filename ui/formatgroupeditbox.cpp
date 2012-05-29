#include "formatgroupeditbox.h"
#include <QFormLayout>
#include <QGroupBox>

FormatGroupEditBox::FormatGroupEditBox(QWidget *parent) :
    QWidget(parent)
{
    m_formatLabel = new QLineEdit(this);
    m_formatDefinition = new QLineEdit(this);
    m_formatLink = new QLineEdit(this);
    QHBoxLayout *l = new QHBoxLayout;
    QFormLayout *formL = new QFormLayout;
    QGroupBox *group = new QGroupBox(tr("Format"));
    formL->addRow(tr("Label"), m_formatLabel);
    formL->addRow(tr("Definition"), m_formatDefinition);
    formL->addRow(tr("Link"), m_formatLink);
    group->setLayout(formL);
    l->addWidget(group);
    this->setLayout(l);
}

QLineEdit *FormatGroupEditBox::formatLabel()
{
    return m_formatLabel;
}

QLineEdit *FormatGroupEditBox::formatDefinition()
{
    return m_formatDefinition;
}

QLineEdit *FormatGroupEditBox::formatLink()
{
    return m_formatLink;
}
