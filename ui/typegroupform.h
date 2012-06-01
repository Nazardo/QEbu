#ifndef TYPEGROUPFORM_H
#define TYPEGROUPFORM_H

#include "stackablewidget.h"

class TypeGroup;
class TypeGroupEditBox;

class TypeGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit TypeGroupForm(TypeGroup *typeGroup,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    TypeGroupEditBox *m_editTypeGroup;
};

#endif // TYPEGROUPFORM_H
