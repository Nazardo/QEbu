#include "elementtypeeditbox.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

ElementTypeEditBox::ElementTypeEditBox(QWidget *parent) :
    QWidget(parent)
{
    m_editValue = new QLineEdit;
    m_editLang = new QLineEdit;
    /** @todo Set size for lang */
    QGridLayout *l = new QGridLayout;
    m_label = new QLabel("call setLabel()");
    l->addWidget(m_label, 0, 0);
    l->addWidget(m_editValue, 0, 1);
    m_labelLang = new QLabel(tr("%1 Lang").arg(m_label->text()));
    l->addWidget(m_labelLang, 1, 0);
    l->addWidget(m_editLang, 1, 1);
    this->setLayout(l);
}

QLineEdit *ElementTypeEditBox::editValue()
{
    return m_editValue;
}

QLineEdit *ElementTypeEditBox::editLang()
{
    return m_editLang;
}

void ElementTypeEditBox::setLabel(const QString &label)
{
    m_label->setText(label);
    m_labelLang->setText(tr("%1 Lang").arg(label));
}
