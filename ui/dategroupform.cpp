#include "dategroupform.h"
#include "qvarptr.h"
#include <QPushButton>

DateGroupForm::DateGroupForm(DateGroup *dateGroup, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (dateGroup) ? Edit : Add;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editDateGroup = new DateGroupEditBox(dateGroup);
    vl->addWidget(m_editDateGroup);
    {
        QHBoxLayout *hl = new QHBoxLayout;
        QPushButton *buttonApply = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        hl->addWidget(buttonApply);
        hl->addWidget(buttonCancel);
        QObject::connect(buttonApply, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        vl->addLayout(hl);
    }
    this->setLayout(vl);
}

QString DateGroupForm::toString()
{
    return QString(tr("DateGroup"));
}

void DateGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(0));
}

void DateGroupForm::applyClicked()
{
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(m_editDateGroup->dateGroup()));
}
