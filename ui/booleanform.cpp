#include "booleanform.h"
#include "qvarptr.h"
#include <QtGui>

BooleanForm::BooleanForm(Boolean *boolean, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (boolean) ? Edit : Add;
    if (!boolean)
        m_boolean = new Boolean;
    else
        m_boolean = boolean;

    // Layout
    m_mainHLayout = new QHBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;

    {
        QFormLayout *fl = new QFormLayout;
        m_checkValue = new QCheckBox;
        m_checkValue->setCheckable(true);
        fl->addRow(tr("Value"), m_checkValue);
        l->addLayout(fl);
    }
    {
        m_editTypeGroup = new TypeGroupEditBox(boolean);
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
    if (m_boolean->value())
        m_checkValue->setChecked(m_boolean->value());
}

QString BooleanForm::toString()
{
    return QString("Boolean");
}

void BooleanForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_boolean;
        m_boolean = 0;
    }
    emit closed(m_op, QVarPtr<Boolean>::asQVariant(m_boolean));
}

void BooleanForm::applyClicked()
{
    if (!checkCompliance())
        return;

    m_boolean->setValue(m_checkValue->isChecked());
    m_editTypeGroup->updateExistingTypeGroup(m_boolean);

    emit closed(m_op, QVarPtr<Boolean>::asQVariant(m_boolean));
}


bool BooleanForm::checkCompliance()
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
