#include "uint64form.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include "model/qebulimits.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QLayout>
#include <QEvent>
#include <QTextEdit>
#include <QComboBox>
#include "qextendedspinbox.h"

Uint64Form::Uint64Form(UInt64 *uint64,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (uint64) ? Edit : Add;
    if(!uint64)
        m_uint64 = new UInt64();
    else
        m_uint64 = uint64;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QUnsignedSpinBox;
        m_spinValue->setRange(qEbuLimits::getMinUInt64(), qEbuLimits::getMaxUInt64());
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged()),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        vl->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(uint64);
        vl->addWidget(m_editTypeGroup);
    }
    this->setLayout(vl);

    // Event Filter
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters using the type attribute of their need."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_spinValue->installEventFilter(this);

    if (m_uint64->value()) {
        m_spinValue->setValue(*(m_uint64->value()));
        m_checkValue->setChecked(true);
    }
}

QString Uint64Form::toString()
{
    return QString(tr("Unsigned Long"));
}

void Uint64Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_uint64;
        m_uint64 = 0;
    }
    emit closed(m_op, QVarPtr<UInt64>::asQVariant(m_uint64));
}

void Uint64Form::applyClicked()
{
    if (m_checkValue->isChecked())
        m_uint64->setValue(m_spinValue->value());
    else
        m_uint64->clearValue();
    m_editTypeGroup->updateExistingTypeGroup(m_uint64);
    emit closed(m_op, QVarPtr<UInt64>::asQVariant(m_uint64));
}

void Uint64Form::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool Uint64Form::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text.\nExample: ‘a flag indicating that the video bitrate corresponds to an average bitrate’."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: averageBitrateFlag, bitrate."));
        else if (obj == (QObject*) m_spinValue)
            m_textDocumentation->setText(tr("The value of the technical attribute."));
    }
    return QObject::eventFilter(obj, event);
}
