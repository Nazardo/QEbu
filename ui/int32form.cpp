#include "int32form.h"
#include "qvarptr.h"
#include <QtGui>

Int32Form::Int32Form(Int32 *int32, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (int32) ? Edit : Add;
    if (!int32)
        m_int32 = new Int32;
    else
        m_int32 = int32;

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
        m_editTypeGroup = new TypeGroupEditBox(int32);
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
    if (!checkCompliance())
        return;

    if (m_checkValue->isChecked())
        m_int32->setValue(m_spinValue->value());
    m_editTypeGroup->updateExistingTypeGroup(m_int32);

    emit closed(m_op, QVarPtr<Int32>::asQVariant(m_int32));
}

void Int32Form::valueChanged()
{
    m_checkValue->setChecked(true);
}

bool Int32Form::checkCompliance()
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
