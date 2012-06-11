#include "alternativetypeform.h"
#include "../model/coremetadatatype.h"
#include "dategroupeditbox.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTimeEdit>
#include <QDateEdit>
#include <QEvent>

AlternativeTypeForm::AlternativeTypeForm(AlternativeType *alternative,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (alternative) ? Edit : Add;
    if (!alternative)
        m_alternative = new AlternativeType;
    else
        m_alternative = alternative;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editTypeGroup = new TypeGroupEditBox(m_alternative);
    vl->addWidget(m_editTypeGroup);
    m_editDateGroup = new DateGroupEditBox(m_alternative);
    vl->addWidget(m_editDateGroup);

    // Event filter
    m_textDocumentation->setText(tr("To define an alternative date important to qualify the resource."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_editDateGroup->editEndDate()->installEventFilter(this);
    m_editDateGroup->editEndTime()->installEventFilter(this);
    m_editDateGroup->editEndYear()->installEventFilter(this);
    m_editDateGroup->editPeriod()->installEventFilter(this);
    m_editDateGroup->editStartDate()->installEventFilter(this);
    m_editDateGroup->editStartTime()->installEventFilter(this);
    m_editDateGroup->editStartYear()->installEventFilter(this);

    this->setLayout(vl);
}

QString AlternativeTypeForm::toString()
{
    return QString(tr("Alternative"));
}

void AlternativeTypeForm::setTitle(const QString &title)
{
    m_editDateGroup->setLabel(title);
}

void AlternativeTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_alternative;
        m_alternative = 0;
    }
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(m_alternative));
}

void AlternativeTypeForm::applyClicked()
{
    m_editTypeGroup->updateExistingTypeGroup(m_alternative);
    m_editDateGroup->updateExistingDateGroup(m_alternative);
    emit closed(m_op, QVarPtr<DateGroup>::asQVariant(m_alternative));
}

bool AlternativeTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("To define the type of alternative date being instantiated.\nExample: ”the date and time at which content was ingested”;"));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("A link to a term or only identify a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("To define the type of alternative date being instantiated.\nExample: ”ingested”;"));
        else if ( obj == (QObject*) m_editDateGroup->editEndDate())
            m_textDocumentation->setText(tr("To express an end date."));
        else if ( obj ==(QObject*) m_editDateGroup->editEndTime())
            m_textDocumentation->setText(tr("To express an end time."));
        else if ( obj == (QObject*) m_editDateGroup->editEndYear())
            m_textDocumentation->setText(tr("To express an end year."));
        else if ( obj == (QObject*) m_editDateGroup->editPeriod())
            m_textDocumentation->setText(tr("To express a time period."));
        else if ( obj == (QObject*) m_editDateGroup->editStartDate())
            m_textDocumentation->setText(tr("To express a start date."));
        else if ( obj == (QObject*) m_editDateGroup->editStartTime())
            m_textDocumentation->setText(tr("To express a start time."));
        else if ( obj == (QObject*) m_editDateGroup->editStartYear())
            m_textDocumentation->setText(tr("To express a start year."));
    }
    return QObject::eventFilter(obj, event);
}

