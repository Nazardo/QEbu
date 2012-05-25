#ifndef ELEMENTTYPEFORM_H
#define ELEMENTTYPEFORM_H

#include "stackablewidget.h"
#include "elementtypeeditbox.h"
#include "../model/elementtype.h"

class ElementTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit ElementTypeForm(ElementType *element, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
public slots:
    void applyClicked();
    void cancelClicked();
private:
    ElementType *m_element;
    ElementTypeEditBox *m_editElementType;
    Operation m_op;
};

#endif // ELEMENTTYPEFORM_H
