#include "int64form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>
#include "qextendedspinbox.h"

Int64Form::Int64Form(Int64 *int64,
                     QEbuMainWindow *mainWindow,
                     QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int64) ? Edit : Add;
    if (!int64)
        m_int64 = new Int64;
    else
        m_int64 = int64;

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
        l->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(int64);
        l->addWidget(m_editTypeGroup);
    }
    this->setLayout(l);

    // Set data fields...
    if (m_int64->value()) {
        m_spinValue->setValue(*(m_int64->value()));
        m_checkValue->setChecked(true);
    }
}

QString Int64Form::toString()
{
    return QString(tr("Long"));
}

void Int64Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_int64;
        m_int64 = 0;
    }
    emit closed(m_op, QVarPtr<Int64>::asQVariant(m_int64));
}

void Int64Form::applyClicked()
{
    if (m_checkValue->isChecked())
        m_int64->setValue(m_spinValue->value());
    else
        m_int64->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_int64);

    emit closed(m_op, QVarPtr<Int64>::asQVariant(m_int64));
}

void Int64Form::valueChanged()
{
    m_checkValue->setChecked(true);
}
