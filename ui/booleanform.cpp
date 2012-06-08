#include "booleanform.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QFormLayout>

BooleanForm::BooleanForm(Boolean *boolean, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (boolean) ? Edit : Add;
    if (!boolean)
        m_boolean = new Boolean;
    else
        m_boolean = boolean;

    // Layout
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
    this->setLayout(l);

    // Set data fields...
    if (m_boolean->value())
        m_checkValue->setChecked(m_boolean->value());
}

QString BooleanForm::toString()
{
    return QString(tr("Boolean"));
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
    m_boolean->setValue(m_checkValue->isChecked());
    m_editTypeGroup->updateExistingTypeGroup(m_boolean);

    emit closed(m_op, QVarPtr<Boolean>::asQVariant(m_boolean));
}
