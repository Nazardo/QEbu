#include "uint16form.h"

#include "qvarptr.h"
#include <QtGui>

Uint16Form::Uint16Form(UInt16 *uint16, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint16) ? Edit : Add;
    if(!uint16)
        m_uint16 = new UInt16();
    else
        m_uint16 = uint16;
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(uint16);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_spinValue = new QSpinBox;
        fl->addRow(tr("Uint16"), m_spinValue);
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
    m_spinValue->setValue((int) m_uint16->value() );
}

QString Uint16Form::toString()
{
    return QString(tr("uint16"));
}

void Uint16Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_uint16;
        m_uint16 = 0;
    }
    emit closed(m_op, QVarPtr<UInt16>::asQVariant(m_uint16));
}

void Uint16Form::applyClicked()
{
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_uint16);
    m_uint16->setValue(m_spinValue->value());
    emit closed(m_op, QVarPtr<UInt16>::asQVariant(m_uint16));
}

bool Uint16Form::checkCompliance()
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
