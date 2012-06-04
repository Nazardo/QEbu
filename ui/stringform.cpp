#include "stringform.h"
#include "../model/technicalattributes.h"
#include "formatgroupeditbox.h"
#include "typegroupeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QFormLayout>

StringForm::StringForm(String *string,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (string) ? Edit : Add;
    if (!string)
        m_string = new String;
    else
        m_string = string;

    // Layout
    QVBoxLayout *l = new QVBoxLayout;

    {
        QFormLayout *fl = new QFormLayout;
        m_editValue = new QLineEdit;
        fl->addRow(tr("Value"), m_editValue);
        l->addLayout(fl);
    }
    {
        m_editFormatGroup = new FormatGroupEditBox(string);
        m_editTypeGroup = new TypeGroupEditBox(string);
        l->addWidget(m_editTypeGroup);
        l->addWidget(m_editFormatGroup);
    }
    this->setLayout(l);

    // Set data fields...
    m_editValue->setText(m_string->value());
}

QString StringForm::toString()
{
    return QString("String");
}

void StringForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_string;
        m_string = 0;
    }
    emit closed(m_op, QVarPtr<String>::asQVariant(m_string));
}

void StringForm::applyClicked()
{
    m_string->setValue(m_editValue->text());
    m_editFormatGroup->updateExistingFormatGroup(m_string);
    m_editTypeGroup->updateExistingTypeGroup(m_string);
    emit closed(m_op, QVarPtr<String>::asQVariant(m_string));
}

