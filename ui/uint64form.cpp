#include "uint64form.h"

#include "qvarptr.h"
#include <QtGui>

Uint64Form::Uint64Form(UInt64 *uint64, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint64) ? Edit : Add;
    if(!uint64)
        m_uint64 = new UInt64();
    else
        m_uint64 = uint64;
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(uint64);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_spinValue = new QSpinBox;
        fl->addRow(tr("Uint64"), m_spinValue);
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
        vl->addLayout(hl);
    }
    m_mainHLayout->addLayout(vl);
    this->setLayout(m_mainHLayout);
    m_spinValue->setValue((int) m_uint64->value() );
}

QString Uint64Form::toString()
{
    return QString(tr("uint64"));
}

void Uint64Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_uint64;
        m_uint64 = 0;
    }
    emit closed(m_op, QVarPtr<UInt64>::asQVariant(m_uint64));
}

void Uint64Form::applyClicked()
{
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_uint64);
    m_uint64->setValue(m_spinValue->value());
    emit closed(m_op, QVarPtr<UInt64>::asQVariant(m_uint64));
}

bool Uint64Form::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";
    //TODO
    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Rrequired fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
