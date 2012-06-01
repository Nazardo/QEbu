#include "elementtypeform.h"
#include "../model/elementtype.h"
#include "elementtypeeditbox.h"
#include "qvarptr.h"
#include <QLineEdit>
#include <QVBoxLayout>

ElementTypeForm::ElementTypeForm(ElementType *element,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent) :
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
