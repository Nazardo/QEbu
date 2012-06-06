#include "int32form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>

Int32Form::Int32Form(Int32 *int32,
                     QEbuMainWindow *mainWindow,
                     QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int32) ? Edit : Add;
    if (!int32)
        m_int32 = new Int32;
    else
        m_int32 = int32;

    // Layout
    QVBoxLayout *l = new QVBoxLayout;

    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinInt32(), qEbuLimits::getMaxInt32());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged(int)),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        l->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(int32);
        l->addWidget(m_editTypeGroup);
    }
    this->setLayout(l);

    // Set data fields...
    if (m_int32->value()) {
        m_spinValue->setValue(*(m_int32->value()));
        m_checkValue->setChecked(true);
    }
}

QString Int32Form::toString()
{
    return QString("Int32");
}

void Int32Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_int32;
        m_int32 = 0;
    }
    emit closed(m_op, QVarPtr<Int32>::asQVariant(m_int32));
}

void Int32Form::applyClicked()
{
    if (m_checkValue->isChecked())
        m_int32->setValue(m_spinValue->value());
    else
        m_int32->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_int32);

    emit closed(m_op, QVarPtr<Int32>::asQVariant(m_int32));
}

void Int32Form::valueChanged()
{
    m_checkValue->setChecked(true);
}
