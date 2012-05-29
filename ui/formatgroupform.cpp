#include "formatgroupform.h"
#include "qvarptr.h"

FormatGroupForm::FormatGroupForm(FormatGroup *formatGroup, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (formatGroup) ? Edit : Add;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editFormatGroup = new FormatGroupEditBox(formatGroup);
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
}

QString FormatGroupForm::toString()
{
    return QString("FormatGroup");
}

void FormatGroupForm::applyClicked()
{
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(m_editFormatGroup->formatGroup()));
}

void FormatGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<FormatGroup>::asQVariant(0));
}
