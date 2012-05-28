#include "elementtypeeditbox.h"
#include <QHBoxLayout>

ElementTypeEditBox::ElementTypeEditBox(QWidget *parent) :
    QWidget(parent)
{
    m_editValue = new QLineEdit;
    m_editLang = new QLineEdit;
    /** @todo Set size for lang */
    QHBoxLayout *l = new QHBoxLayout;
    m_label = new QLabel("call setLabel()");
    l->addWidget(m_label);
    l->addStretch();
    l->addWidget(m_editValue);
    l->addWidget(new QLabel(tr("Lang")));
    l->addWidget(m_editLang);
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
}
