#include "formatgroupeditbox.h"
#include <QFormLayout>

FormatGroupEditBox::FormatGroupEditBox(QWidget *parent) :
    QWidget(parent)
{
    m_formatLabel = new QLineEdit(this);
    m_formatDefinition = new QLineEdit(this);
    m_formatLink = new QLineEdit(this);
    QFormLayout *formL = new QFormLayout;
    formL->addRow(tr("Label"), m_formatLabel);
    formL->addRow(tr("Definition"), m_formatDefinition);
    formL->addRow(tr("Link"), m_formatLink);
    this->setLayout(formL);
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
