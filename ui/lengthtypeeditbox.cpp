/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

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

QUnsignedSpinBox *LengthTypeEditBox::editValue()
{
    return m_editValue;
}

QLineEdit *LengthTypeEditBox::editUnit()
{
    return m_editUnit;
}
