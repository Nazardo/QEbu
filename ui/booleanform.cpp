#include "booleanform.h"
#include "../model/technicalattributes.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QEvent>

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

    // Event Filter
    m_textDocumentation->setText(tr("Allows users / implementers to define their own technical parameters using the type attribute of their need."));
    m_editTypeGroup->editTypeDefinition()->installEventFilter(this);
    m_editTypeGroup->editTypeLabel()->installEventFilter(this);
    m_editTypeGroup->editTypeLink()->installEventFilter(this);
    m_checkValue->installEventFilter(this);

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

bool BooleanForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editTypeGroup->editTypeDefinition())
            m_textDocumentation->setText(tr("Free text.\nExample: �a flag indicating that the video bitrate corresponds to an average bitrate�."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLink())
            m_textDocumentation->setText(tr("Link to a classification scheme."));
        else if (obj == (QObject*) m_editTypeGroup->editTypeLabel())
            m_textDocumentation->setText(tr("Free text.\nExample: averageBitrateFlag, bitrate."));
        else if (obj == (QObject*) m_checkValue)
            m_textDocumentation->setText(tr("The value of the technical attribute."));
    }
    return QObject::eventFilter(obj, event);
}
