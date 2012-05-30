#include "alternativetypeform.h"
#include "qvarptr.h"
#include <QtGui>

AlternativeTypeForm::AlternativeTypeForm(AlternativeType *alternative, QEbuMainWindow *mainWindow, QWidget *parent) :
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

QString AlternativeTypeForm::toString()
{
    return QString(tr("DateGroup"));
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

