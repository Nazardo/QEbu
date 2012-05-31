#include "uint32form.h"

#include "qvarptr.h"
#include <QtGui>

Uint32Form::Uint32Form(UInt32 *uint32, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint32) ? Edit : Add;
    if(!uint32)
        m_uint32 = new UInt32();
    else
        m_uint32 = uint32;
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(uint32);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_spinValue = new QSpinBox;
        fl->addRow(tr("Uint32"), m_spinValue);
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
    m_spinValue->setValue((int) m_uint32->value() );
}

QString Uint32Form::toString()
{
    return QString(tr("uint32"));
}

void Uint32Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_uint32;
        m_uint32 = 0;
    }
    emit closed(m_op, QVarPtr<UInt32>::asQVariant(m_uint32));
}

void Uint32Form::applyClicked()
{
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_uint32);
    m_uint32->setValue(m_spinValue->value());
    emit closed(m_op, QVarPtr<UInt32>::asQVariant(m_uint32));
}

bool Uint32Form::checkCompliance()
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
