#include "uint8form.h"
#include "../model/qebulimits.h"
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
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinUInt8(), qEbuLimits::getMaxUInt8());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged(unsigned int)),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        vl->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uint8);
        vl->addWidget(m_editTypeGroup);
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

    if (m_uint8->value()) {
        m_spinValue->setValue(*(m_uint8->value()));
        m_checkValue->setChecked(true);
    }
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
    if (m_checkValue->isChecked())
        m_uint8->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_uint8);
    emit closed(m_op, QVarPtr<UInt8>::asQVariant(m_uint8));
}

void Uint8Form::valueChanged()
{
    m_checkValue->setChecked(true);
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
