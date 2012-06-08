#include "dategroupform.h"
#include "../model/dategroup.h"
#include "dategroupeditbox.h"
#include "qvarptr.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

DateGroupForm::DateGroupForm(DateGroup *dateGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (dateGroup) ? Edit : Add;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editDateGroup = new DateGroupEditBox(dateGroup);
    vl->addWidget(m_editDateGroup);
    this->setLayout(vl);
    m_title = QString(tr("Date Group"));
}

QString DateGroupForm::toString()
{
    return m_title;
}

void DateGroupForm::setTitle(const QString &title)
{
    m_editDateGroup->setLabel(title);
    m_title = title;
}

void DateGroupForm::cancelClicked()
{
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(0));
}

void DateGroupForm::applyClicked()
{
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(m_editDateGroup->dateGroup()));
}
