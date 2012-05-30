#include "technicalattributerationaltypeform.h"
#include "qvarptr.h"
#include <QtGui>
#include <limits>

TechnicalAttributeRationalTypeForm::TechnicalAttributeRationalTypeForm(
        TechnicalAttributeRationalType *rational, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (rational) ? Edit : Add;
    if (!rational)
        m_rational = new TechnicalAttributeRationalType;
    else
        m_rational = rational;

    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;

    {
        QFormLayout *fl = new QFormLayout;
        m_spinValue = new QDoubleSpinBox;
        fl->addRow(tr("Value"), m_spinValue);
        m_spinFactorNumerator = new QSpinBox;
        fl->addRow(tr("Factor numerator"), m_spinFactorNumerator);
        m_spinFactorDenominator = new QSpinBox;
        fl->addRow(tr("Factor denominator"), m_spinFactorDenominator);
        l->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(rational);
        l->addWidget(m_editTypeGroup);
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
        l->addLayout(hl);
    }

    m_mainHLayout->addLayout(l);
    this->setLayout(m_mainHLayout);

    // Set data fields...
    if (m_rational->value())
        m_spinValue->setValue(*(m_rational->value()));
    if (m_rational->factorNumerator())
        m_spinFactorNumerator->setValue(*(m_rational->factorNumerator()));
    if (m_rational->factorDenominator())
        m_spinFactorDenominator->setValue(*(m_rational->factorDenominator()));
}

QString TechnicalAttributeRationalTypeForm::toString()
{
    return QString("TechnicalAttributeRationalType");
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
    if (!checkCompliance())
        return;

    m_rational->setValue(m_spinValue->value());
    m_rational->setFactorDenominator(m_spinFactorDenominator->value());
    m_rational->setFactorNumerator(m_spinFactorNumerator->value());
    m_editTypeGroup->updateExistingTypeGroup(m_rational);
    emit closed(m_op, QVarPtr<TechnicalAttributeRationalType>::asQVariant(m_rational));
}


bool TechnicalAttributeRationalTypeForm::checkCompliance()
{
    bool ok = true;
    QString error_msg = "";

    if(!ok) {
        QErrorMessage *e = new QErrorMessage(this);
        e->setWindowTitle(tr("Required fields"));
        e->showMessage(error_msg);
    }
    return ok;
}
