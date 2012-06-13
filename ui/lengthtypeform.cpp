#include "lengthtypeform.h"
#include "../model/ebucoremaintype.h"
#include "../model/qebulimits.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QTextBrowser>
#include <QEvent>
#include <QCheckBox>
#include <QFormLayout>
#include "qextendedspinbox.h"

LengthTypeForm::LengthTypeForm(LengthType *length,
                               QEbuMainWindow *mainWindow,
                               QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (length) ? Edit : Add;

    if(!length)
        m_length= new LengthType;
    else
        m_length = length;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editUnit = new QLineEdit;
        fl->addRow(tr("Unit"), m_editUnit);
        vl->addLayout(fl);
    }
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QUnsignedSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinUInt(), qEbuLimits::getMaxUInt());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged()),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        vl->addLayout(gl);
    }
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(tr(""));
    m_editUnit->installEventFilter(this);
    m_spinValue->installEventFilter(this);

    // Set data fields...
    if (m_length->value()) {
        m_spinValue->setValue(*(m_length->value()));
        m_checkValue->setChecked(true);
    }
    m_editUnit->setText(m_length->unit());
}

QString LengthTypeForm::toString()
{
    return QString(tr("Length"));
}

void LengthTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_length;
        m_length = 0;
    }
    emit closed(m_op, QVarPtr<LengthType>::asQVariant(m_length));
}

void LengthTypeForm::applyClicked()
{
    m_length->setUnit(m_editUnit->text());
    if (m_checkValue->isChecked())
        m_length->setValue(m_spinValue->value());
    else
        m_length->clearValue();
    emit closed(m_op, QVarPtr<LengthType>::asQVariant(m_length));
}

void LengthTypeForm::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool LengthTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    Q_UNUSED(event);
    return true;
}
