#include "int8form.h"
#include "qvarptr.h"
#include <QtGui>

Int8Form::Int8Form(Int8 *int8, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int8) ? Edit : Add;
    if (!int8)
        m_int8 = new Int8;
    else
        m_int8 = int8;

    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    {
        QGridLayout *gl = new QGridLayout;
        m_spinValue = new QSpinBox;
        m_checkValue = new QCheckBox(tr("Value"));
        QObject::connect(m_spinValue, SIGNAL(valueChanged(int)),
                         this, SLOT(valueChanged()));
        gl->addWidget(m_checkValue, 0, 0);
        gl->addWidget(m_spinValue, 0, 1);
        l->addLayout(gl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(int8);
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
    if (m_int8->value()) {
        m_spinValue->setValue(*(m_int8->value()));
        m_checkValue->setChecked(true);
    }
}

QString Int8Form::toString()
{
    return QString("Int8");
}

void Int8Form::cancelClicked()
{
    if (m_op == Add) {
        delete m_int8;
        m_int8 = 0;
    }
    emit closed(m_op, QVarPtr<Int8>::asQVariant(m_int8));
}

void Int8Form::applyClicked()
{
    if (!checkCompliance())
        return;

    if (m_checkValue->isChecked())
        m_int8->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_int8);

    emit closed(m_op, QVarPtr<Int8>::asQVariant(m_int8));
}

void Int8Form::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool Int8Form::checkCompliance()
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
