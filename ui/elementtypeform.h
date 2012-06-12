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
    void setGenericTextDocumentation(const QString &doc);
    void setValueDocumentation(const QString &value);
    void setLangDocumentation(const QString &lang);
public slots:
    void applyClicked();
    void cancelClicked();
private:
    bool eventFilter(QObject *obj, QEvent *event);
    QString m_docGeneral;
    QString m_docValue;
    QString m_docLang;
    QString m_title;
    ElementType *m_element;
    ElementTypeEditBox *m_editElementType;
};

#endif // ELEMENTTYPEFORM_H
