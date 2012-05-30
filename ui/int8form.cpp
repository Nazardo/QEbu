#include "int8form.h"
#include "qvarptr.h"
#include <QtGui>


Int8Form::Int8Form(Int8 *int8, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int8) ? Edit : Add;
    if (!int8)
        m_int8 = new Int8;
    else
        m_int8 = int8;

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
        m_editTypeGroup = new TypeGroupEditBox(int8);
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
    if (m_int8->value()) {
        m_spinValue->setValue(*(m_int8->value()));
    }
}

QString Int8Form::toString()
{
    return QString("Int8");
}

void Int8Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_int8;
        m_int8 = 0;
    }
    emit closed(m_op, QVarPtr<Int8>::asQVariant(m_int8));
}

void Int8Form::applyClicked()
{
    if (!checkCompliance())
        return;

    m_int8->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_int8);

    emit closed(m_op, QVarPtr<Int8>::asQVariant(m_int8));
}


bool Int8Form::checkCompliance()
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
