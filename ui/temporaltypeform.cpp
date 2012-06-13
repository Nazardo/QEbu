#include "temporaltypeform.h"
#include "model/coremetadatatype.h"
#include "../model/typeconverter.h"
#include "typegroupeditbox.h"
#include "dategroupeditbox.h"
#include "qvarptr.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QEvent>
#include <QComboBox>
#include <QTimeEdit>
#include <QDateEdit>
#include <QSpinBox>

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
        m_editTypeGroup = new TypeGroupEditBox(m_temporal);
        m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
        m_editTypeGroup->editTypeLabel()->installEventFilter(this);
        m_editTypeGroup->editTypeLink()->installEventFilter(this);
        vl->addWidget(m_editTypeGroup);
        QFormLayout *fl = new QFormLayout;
        m_editPeriodId = new QLineEdit;
        m_editPeriodId->installEventFilter(this);
        m_editPeriodId->setValidator(TypeConverter::getUriValidator());
        fl->addRow(tr("Period ID"), m_editPeriodId);
        m_textNote = new QTextEdit;
        m_textNote->installEventFilter(this);
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
        mainHLayout->addLayout(vl);
    }
    m_textDocumentation->setText(tr("Temporal characteristics of the content of the resource. To indicate e.g. dates, times or periods specific to the resource in complement to Description."));
    m_editPeriodOfTime = new DateGroupEditBox(m_temporal->periodOfTime());
    m_editPeriodOfTime->editEndDate()->installEventFilter(this);
    m_editPeriodOfTime->editEndTime()->installEventFilter(this);
    m_editPeriodOfTime->editEndYear()->installEventFilter(this);
    m_editPeriodOfTime->editPeriod()->installEventFilter(this);
    m_editPeriodOfTime->editStartDate()->installEventFilter(this);
    m_editPeriodOfTime->editStartTime()->installEventFilter(this);
    m_editPeriodOfTime->editStartYear()->installEventFilter(this);
    m_editPeriodOfTime->setLabel(tr("Period of time"));
    mainHLayout->addWidget(m_editPeriodOfTime);
    this->setLayout(mainHLayout);

    // Set data fields
    m_editPeriodId->setText(m_temporal->periodId());
    m_textNote->setText(m_temporal->note());
}

QString TemporalTypeForm::toString()
{
    return QString(tr("Temporal"));
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

bool TemporalTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if ( obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text"));
        if ( obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text"));
        if ( obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a classification scheme"));
        if ( obj == (QObject*) m_textNote)
            m_textDocumentation->setText(tr("A note to provide additional contextual information"));
        if ( obj == (QObject*) m_editPeriodId)
            m_textDocumentation->setText(tr("An attribute to identify the time period."));
        if ( obj == (QObject*) m_editPeriodOfTime->editEndDate())
            m_textDocumentation->setText(tr("To express an end date"));
        if ( obj == (QObject*) m_editPeriodOfTime->editEndTime())
            m_textDocumentation->setText(tr("To express an end time"));
        if ( obj == (QObject*) m_editPeriodOfTime->editEndYear())
            m_textDocumentation->setText(tr("To express an end year"));
        if ( obj == (QObject*) m_editPeriodOfTime->editPeriod())
            m_textDocumentation->setText(tr("The period of time depicted in the resource."));
        if ( obj == (QObject*) m_editPeriodOfTime->editStartDate())
            m_textDocumentation->setText(tr("To express a start date"));
        if ( obj == (QObject*) m_editPeriodOfTime->editStartTime())
            m_textDocumentation->setText(tr("To express a start time"));
        if ( obj == (QObject*) m_editPeriodOfTime->editStartYear())
            m_textDocumentation->setText(tr("To express a start year"));


    }
    return QObject::eventFilter(obj, event);
}
