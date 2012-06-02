#include "uint32form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>

Uint32Form::Uint32Form(UInt32 *uint32,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint32) ? Edit : Add;
    if(!uint32)
        m_uint32 = new UInt32();
    else
        m_uint32 = uint32;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinUInt32(), qEbuLimits::getMaxUInt32());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged(unsigned int)),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        vl->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uint32);
        vl->addWidget(m_editTypeGroup);
    }
    this->setLayout(vl);

    if (m_uint32->value()) {
        m_spinValue->setValue(*(m_uint32->value()));
        m_checkValue->setChecked(true);
    }
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
    if (m_checkValue->isChecked())
        m_uint32->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_uint32);
    emit closed(m_op, QVarPtr<UInt32>::asQVariant(m_uint32));
}

void Uint32Form::valueChanged()
{
    m_checkValue->setChecked(true);
}
