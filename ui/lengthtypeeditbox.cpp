#include "lengthtypeeditbox.h"
#include "../model/lengthtype.h"
#include "../model/qebulimits.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLineEdit>

LengthTypeEditBox::LengthTypeEditBox(LengthType *length, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hl = new QHBoxLayout;
    m_check = new QCheckBox(tr("Length"));
    hl->addWidget(m_check);
    m_editValue = new QSpinBox;
    m_editValue->setRange(qEbuLimits::getMinUInt(),
                          qEbuLimits::getMaxUInt());
    hl->addWidget(m_editValue);
    m_editUnit = new QLineEdit;
    m_editUnit->setPlaceholderText(tr("Unit"));
    hl->addWidget(m_editUnit);
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
