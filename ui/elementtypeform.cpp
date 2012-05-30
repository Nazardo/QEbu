#include "elementtypeform.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "qvarptr.h"

ElementTypeForm::ElementTypeForm(ElementType *element, QEbuMainWindow *mainWindow, QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (element) ? Edit : Add;
    if (element)
        m_element = element;
    else
        m_element = new ElementType;
    QVBoxLayout *vl = new QVBoxLayout;
    m_editElementType = new ElementTypeEditBox;
    vl->addWidget(m_editElementType);
    {
        QHBoxLayout *hl = new QHBoxLayout;
        QPushButton *buttonApply = new QPushButton(tr("Apply changes"));
        QPushButton *buttonCancel = new QPushButton(tr("Cancel"));
        hl->addWidget(buttonApply);
        hl->addWidget(buttonCancel);
        QObject::connect(buttonApply, SIGNAL(clicked()),
                         this, SLOT(applyClicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()),
                         this, SLOT(cancelClicked()));
        vl->addLayout(hl);
    }
    this->setLayout(vl);
    // Set values in text fields
    m_editElementType->editValue()->setText(m_element->value());
    m_editElementType->editLang()->setText(m_element->lang());
}

QString ElementTypeForm::toString()
{
    return QString("ElementType");
}

void ElementTypeForm::setTitle(const QString &title)
{
    m_editElementType->setLabel(title);
}

void ElementTypeForm::applyClicked()
{
    m_element->setValue(m_editElementType->editValue()->text());
    m_element->setLang(m_editElementType->editLang()->text());
    emit closed(m_op, QVarPtr<ElementType>::asQVariant(m_element));
}

void ElementTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_element;
        m_element = 0;
    }
    emit closed(m_op, QVarPtr<ElementType>::asQVariant(m_element));
}
