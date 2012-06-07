#include "lengthtypeeditbox.h"
#include "../model/lengthtype.h"
#include "../model/qebulimits.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include "qextendedspinbox.h"

LengthTypeEditBox::LengthTypeEditBox(LengthType *length, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hl = new QHBoxLayout;
    m_check = new QCheckBox(tr("Length"));
    hl->addWidget(m_check);
    m_editValue = new QUnsignedSpinBox;
    m_editValue->setRange(qEbuLimits::getMinUInt(),
                          qEbuLimits::getMaxUInt());
    hl->addWidget(m_editValue);
    QObject::connect(m_editValue, SIGNAL(valueChanged()),
                     this, SLOT(lengthChanged()));
    m_editUnit = new QLineEdit;
    m_editUnit->setPlaceholderText(tr("Unit"));
    hl->addWidget(m_editUnit);
    QObject::connect(m_editUnit, SIGNAL(textChanged(QString)),
                     this, SLOT(lengthChanged()));
    this->setLayout(hl);
    // Set text fields
    if (!length)
        return;
    m_check->setChecked(true);
    if (length->value())
        m_editValue->setValue(*(length->value()));
    m_editUnit->setText(length->unit());
}

LengthType *LengthTypeEditBox::lengthType()
{
    if (!m_check->isChecked())
        return 0;
    LengthType *length = new LengthType;
    length->setValue(m_editValue->value());
    length->setUnit(m_editUnit->text());
    return length;
}

void LengthTypeEditBox::setLabel(const QString &label)
{
    m_check->setText(label);
}

void LengthTypeEditBox::lengthChanged()
{
    m_check->setChecked(true);
}
