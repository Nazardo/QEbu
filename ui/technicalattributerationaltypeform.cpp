#include "technicalattributerationaltypeform.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "../model/qebulimits.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QLayout>
#include "qextendedspinbox.h"

TechnicalAttributeRationalTypeForm::TechnicalAttributeRationalTypeForm(
        TechnicalAttributeRationalType *rational,
        QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (rational) ? Edit : Add;
    if (!rational)
        m_rational = new TechnicalAttributeRationalType;
    else
        m_rational = rational;

    // Layout
    QVBoxLayout *l = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;

        m_spinValue = new QSignedSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinInt64(), qEbuLimits::getMaxInt64());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged()),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);

        m_spinFactorNumerator = new QSpinBox;
        m_spinFactorNumerator->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
        m_checkNumerator = new QCheckBox(tr("Factor numerator"));
        QObject::connect(m_spinFactorNumerator, SIGNAL(valueChanged(int)),
                         this, SLOT(numeratorChanged()));
        gl->addWidget(m_checkNumerator, 1, 0);
        gl->addWidget(m_spinFactorNumerator, 1, 1);

        m_spinFactorDenominator = new QSpinBox;
        m_spinFactorDenominator->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
        m_checkDenominator = new QCheckBox(tr("Factor denominator"));
        QObject::connect(m_spinFactorDenominator, SIGNAL(valueChanged(int)),
                         this, SLOT(denominatorChanged()));
        gl->addWidget(m_checkDenominator, 2, 0);
        gl->addWidget(m_spinFactorDenominator, 2, 1);

        l->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(rational);
        l->addWidget(m_editTypeGroup);
    }
    this->setLayout(l);

    // Set data fields...
    if (m_rational->value()) {
        m_spinValue->setValue(*(m_rational->value()));
        m_checkValue->setChecked(true);
    }
    if (m_rational->factorNumerator()) {
        m_spinFactorNumerator->setValue(*(m_rational->factorNumerator()));
        m_checkNumerator->setChecked(true);
    }
    else
        m_spinFactorNumerator->setValue(1);
    if (m_rational->factorDenominator()) {
        m_spinFactorDenominator->setValue(*(m_rational->factorDenominator()));
        m_checkDenominator->setChecked(true);
    }
    else
        m_spinFactorDenominator->setValue(1);
}

QString TechnicalAttributeRationalTypeForm::toString()
{
    return QString(tr("Technical Attribute Rational"));
}

void TechnicalAttributeRationalTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_rational;
        m_rational = 0;
    }
    emit closed(m_op, QVarPtr<TechnicalAttributeRationalType>::asQVariant(m_rational));
}

void TechnicalAttributeRationalTypeForm::applyClicked()
{
    if (m_checkValue->isChecked())
        m_rational->setValue(m_spinValue->value());
    else
        m_rational->clearValue();
    if (m_checkDenominator->isChecked())
        m_rational->setFactorDenominator(m_spinFactorDenominator->value());
    else
        m_rational->clearFactorDenominator();
    if (m_checkNumerator->isChecked())
        m_rational->setFactorNumerator(m_spinFactorNumerator->value());
    else
        m_rational->clearFactorNumerator();
    m_editTypeGroup->updateExistingTypeGroup(m_rational);
    emit closed(m_op, QVarPtr<TechnicalAttributeRationalType>::asQVariant(m_rational));
}

void TechnicalAttributeRationalTypeForm::valueChanged()
{
    m_checkValue->setChecked(true);
}

void TechnicalAttributeRationalTypeForm::numeratorChanged()
{
    m_checkNumerator->setChecked(true);
}

void TechnicalAttributeRationalTypeForm::denominatorChanged()
{
    m_checkDenominator->setChecked(true);
}
