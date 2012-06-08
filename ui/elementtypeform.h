#ifndef ELEMENTTYPEFORM_H
#define ELEMENTTYPEFORM_H

#include "stackablewidget.h"

class ElementType;
class ElementTypeEditBox;

class ElementTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit ElementTypeForm(ElementType *element,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
public slots:
    void applyClicked();
    void cancelClicked();
private:
    QString m_title;
    ElementType *m_element;
    ElementTypeEditBox *m_editElementType;
};

#endif // ELEMENTTYPEFORM_H
