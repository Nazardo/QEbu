#include "int64form.h"
#include "qvarptr.h"
#include <QtGui>

Int64Form::Int64Form(Int64 *int64, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int64) ? Edit : Add;
    if (!int64)
        m_int64 = new Int64;
    else
        m_int64 = int64;

    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;

    {
        QFormLayout *fl = new QFormLayout;
        m_spinValue = new QSpinBox;
        fl->addRow(tr("Value"), m_spinValue);
        l->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(int64);
        l->addWidget(m_editTypeGroup);
    }
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
        l->addLayout(hl);
    }

    m_mainHLayout->addLayout(l);
    this->setLayout(m_mainHLayout);

    // Set data fields...
    if (m_int64->value()) {
        m_spinValue->setValue(*(m_int64->value()));
    }
}

QString Int64Form::toString()
{
    return QString("Int64");
}

void Int64Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_int64;
        m_int64 = 0;
    }
    emit closed(m_op, QVarPtr<Int64>::asQVariant(m_int64));
}

void Int64Form::applyClicked()
{
    if (!checkCompliance())
        return;

    m_int64->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_int64);

    emit closed(m_op, QVarPtr<Int64>::asQVariant(m_int64));
}


bool Int64Form::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";

    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Required fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
