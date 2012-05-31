#include "uint8form.h"

#include "qvarptr.h"
#include <QtGui>

Uint8Form::Uint8Form(UInt8 *uint8, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint8) ? Edit : Add;
    if(!uint8)
        m_uint8 = new UInt8();
    else
        m_uint8 = uint8;
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        m_editTypeGroup = new TypeGroupEditBox(uint8);
        vl->addWidget(m_editTypeGroup);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_spinValue = new QSpinBox;
        fl->addRow(tr("Uint8"), m_spinValue);
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
    m_spinValue->setValue((int) m_uint8->value() );
}

QString Uint8Form::toString()
{
    return QString(tr("Uint8"));
}

void Uint8Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_uint8;
        m_uint8 = 0;
    }
    emit closed(m_op, QVarPtr<UInt8>::asQVariant(m_uint8));
}

void Uint8Form::applyClicked()
{
    if (!checkCompliance())
        return;
    m_editTypeGroup->updateExistingTypeGroup(m_uint8);
    m_uint8->setValue(m_spinValue->value());
    emit closed(m_op, QVarPtr<UInt8>::asQVariant(m_uint8));
}

bool Uint8Form::checkCompliance()
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
