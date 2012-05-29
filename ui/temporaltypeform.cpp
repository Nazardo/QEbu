#include "temporaltypeform.h"
#include "qvarptr.h"
#include <QFormLayout>
#include <QPushButton>

TemporalTypeForm::TemporalTypeForm(TemporalType *temporal, QEbuMainWindow *mainWindow, QWidget *parent)  :
    StackableWidget(mainWindow, parent)
{
    m_op = (temporal) ? Edit : Add;
    if (!temporal)
        m_temporal = new TemporalType;
    else
        m_temporal = temporal;
    // Layout
    m_mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    {
        QVBoxLayout *vl = new QVBoxLayout;
        m_editTypeGroup = new TypeGroupEditBox;
        vl->addWidget(m_editTypeGroup);
        QFormLayout *fl = new QFormLayout;
        m_editPeriodId = new QLineEdit;
        fl->addRow(tr("Period ID"), m_editPeriodId);
        m_textNote = new QTextEdit;
        fl->addRow(tr("Note"), m_textNote);
        vl->addLayout(fl);
        mainHLayout->addLayout(vl);
    }
//    m_editDateGroup = new DateGroupEditBox;
//    mainHLayout->addWidget(m_editDateGroup);
    m_mainVLayout->addLayout(mainHLayout);
    {
        QHBoxLayout *hl = new QHBoxLayout;
        QPushButton *buttonClose = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        QObject::connect(buttonClose, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        hl->addWidget(buttonClose);
        hl->addWidget(buttonCancel);
        m_mainVLayout->addLayout(hl);
    }

    this->setLayout(m_mainVLayout);

    // Set data fields
    // TODO dategroup
    m_editPeriodId->setText(m_temporal->periodId());
    m_textNote->setText(m_temporal->note());
    m_editTypeGroup->typeLabel()->setText(m_temporal->typeLabel());
    m_editTypeGroup->typeLink()->setText(m_temporal->typeLink());
    m_editTypeGroup->typeDefinition()->setText(m_temporal->typeDefinition());
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
    //TODO Dategroup
    m_temporal->setPeriodId(m_editPeriodId->text());
    m_temporal->setNote(m_textNote->toPlainText());
    m_temporal->setTypeDefinition(m_editTypeGroup->typeDefinition()->text());
    m_temporal->setTypeLabel(m_editTypeGroup->typeLabel()->text());
    m_temporal->setTypeLink(m_editTypeGroup->typeLink()->text());
    emit closed(m_op, QVarPtr<TemporalType>::asQVariant(m_temporal));
}
