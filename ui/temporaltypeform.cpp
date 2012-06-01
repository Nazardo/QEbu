#include "temporaltypeform.h"
#include "model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "dategroupeditbox.h"
#include "qvarptr.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>

TemporalTypeForm::TemporalTypeForm(TemporalType *temporal,
                                   QEbuMainWindow *mainWindow,
                                   QWidget *parent)  :
    StackableWidget(mainWindow, parent)
{
    m_op = (temporal) ? Edit : Add;
    if (!temporal)
        m_temporal = new TemporalType;
    else
        m_temporal = temporal;
    // Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    {
        QVBoxLayout *vl = new QVBoxLayout;
        m_editTypeGroup = new TypeGroupEditBox(temporal);
        vl->addWidget(m_editTypeGroup);
        QFormLayout *fl = new QFormLayout;
        m_editPeriodId = new QLineEdit;
        fl->addRow(tr("Period ID"), m_editPeriodId);
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
        mainHLayout->addLayout(vl);
    }
    m_editPeriodOfTime = new DateGroupEditBox(m_temporal->periodOfTime());
    m_editPeriodOfTime->setLabel(tr("Period of time"));
    mainHLayout->addWidget(m_editPeriodOfTime);
    this->setLayout(mainHLayout);

    // Set data fields
    m_editPeriodId->setText(m_temporal->periodId());
    m_textNote->setText(m_temporal->note());
}

QString TemporalTypeForm::toString()
{
    return QString("Temporal Type");
}

void TemporalTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_temporal;
        m_temporal = 0;
    }
    emit closed(m_op, QVarPtr<TemporalType>::asQVariant(m_temporal));
}

void TemporalTypeForm::applyClicked()
{
    m_temporal->setPeriodOfTime(m_editPeriodOfTime->dateGroup());
    m_temporal->setPeriodId(m_editPeriodId->text());
    m_temporal->setNote(m_textNote->toPlainText());
    m_editTypeGroup->updateExistingTypeGroup(m_temporal);
    emit closed(m_op, QVarPtr<TemporalType>::asQVariant(m_temporal));
}
