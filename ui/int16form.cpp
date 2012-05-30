#include "int16form.h"
#include "qvarptr.h"
#include <QtGui>

Int16Form::Int16Form(Int16 *int16, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int16) ? Edit : Add;
    if (!int16)
        m_int16 = new Int16;
    else
        m_int16 = int16;

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
        m_editTypeGroup = new TypeGroupEditBox(int16);
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
    if (m_int16->value()) {
        m_spinValue->setValue(*(m_int16->value()));
    }
}

QString Int16Form::toString()
{
    return QString("Int16");
}

void Int16Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_int16;
        m_int16 = 0;
    }
    emit closed(m_op, QVarPtr<Int16>::asQVariant(m_int16));
}

void Int16Form::applyClicked()
{
    if (!checkCompliance())
        return;

    m_int16->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_int16);

    emit closed(m_op, QVarPtr<Int16>::asQVariant(m_int16));
}


bool Int16Form::checkCompliance()
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
