#include "formatgroupform.h"
#include "qvarptr.h"

FormatGroupForm::FormatGroupForm(FormatGroup *formatGroup, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (formatGroup) ? Edit : Add;
    if (!formatGroup)
        m_formatGroup = new FormatGroup;
    else
        m_formatGroup = formatGroup;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editFormatGroup = new FormatGroupEditBox;
    vl->addWidget(m_editFormatGroup);
    {
        QHBoxLayout *hl = new QHBoxLayout;
        m_buttonApply = new QPushButton(tr("Apply changes"));
        m_buttonCancel = new QPushButton(tr("Cancel"));
        hl->addWidget(m_buttonApply);
        hl->addWidget(m_buttonCancel);
        QObject::connect(m_buttonApply, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(m_buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        vl->addLayout(hl);
    }
    this->setLayout(vl);
    // Set values in text fields
    m_editFormatGroup->formatLabel()->setText(m_formatGroup->formatLabel());
    m_editFormatGroup->formatDefinition()->setText(m_formatGroup->formatDefinition());
    m_editFormatGroup->formatLink()->setText(m_formatGroup->formatLink());
}

QString FormatGroupForm::toString()
{
    return QString("FormatGroup");
}

void FormatGroupForm::applyClicked()
{
    m_formatGroup->setFormatDefinition(m_editFormatGroup->formatDefinition()->text());
    m_formatGroup->setFormatLabel(m_editFormatGroup->formatLabel()->text());
    m_formatGroup->setFormatLink(m_editFormatGroup->formatLink()->text());
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(m_formatGroup));
}

void FormatGroupForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_formatGroup;
        m_formatGroup = 0;
    }
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(m_formatGroup));
}
