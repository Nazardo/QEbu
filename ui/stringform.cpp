#include "stringform.h"
#include "qvarptr.h"
#include <QtGui>

StringForm::StringForm(String *string, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (string) ? Edit : Add;
    if (!string)
        m_string = new String;
    else
        m_string = string;

    // Layout
    m_mainHLayout = new QHBoxLayout;
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
    if (!checkCompliance())
        return;

    m_string->setValue(m_editValue->text());
    m_editFormatGroup->updateExistingFormatGroup(m_string);

    emit closed(m_op, QVarPtr<String>::asQVariant(m_string));
}


bool StringForm::checkCompliance()
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


