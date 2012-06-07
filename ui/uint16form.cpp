#include "uint16form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>
#include "qextendedspinbox.h"

Uint16Form::Uint16Form(UInt16 *uint16,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint16) ? Edit : Add;
    if(!uint16)
        m_uint16 = new UInt16();
    else
        m_uint16 = uint16;

    QVBoxLayout *vl = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QUnsignedSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinUInt16(), qEbuLimits::getMaxUInt16());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged()),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        vl->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uint16);
        vl->addWidget(m_editTypeGroup);
    }
    this->setLayout(vl);

    if (m_uint16->value()) {
        m_spinValue->setValue(*(m_uint16->value()));
        m_checkValue->setChecked(true);
    }
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
    if (m_checkValue->isChecked())
        m_uint16->setValue(m_spinValue->value());
    else
        m_uint16->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_uint16);
    emit closed(m_op, QVarPtr<UInt16>::asQVariant(m_uint16));
}

void Uint16Form::valueChanged()
{
    m_checkValue->setChecked(true);
}
