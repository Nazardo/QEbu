#include "floatform.h"
#include "qvarptr.h"
#include <QtGui>

FloatForm::FloatForm(Float *p_float, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    // In this case only the variable passed to the constructor is called p_varName, because
    // either float and Float are reserved names.

    m_op = (p_float) ? Edit : Add;
    if (!p_float)
        m_float = new Float;
    else
        m_float = p_float;

    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;

    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QDoubleSpinBox;
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged(double)),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        l->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(p_float);
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
    if (m_float->value()) {
        m_spinValue->setValue(*(m_float->value()));
        m_checkValue->setChecked(true);
    }
}

QString FloatForm::toString()
{
    return QString("Float");
}

void FloatForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_float;
        m_float = 0;
    }
    emit closed(m_op, QVarPtr<Float>::asQVariant(m_float));
}

void FloatForm::applyClicked()
{
    if (!checkCompliance())
        return;

    if (m_checkValue->isChecked())
        m_float->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_float);

    emit closed(m_op, QVarPtr<Float>::asQVariant(m_float));
}

void FloatForm::valueChanged()
{
    m_checkValue->setChecked(true);
}


bool FloatForm::checkCompliance()
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
