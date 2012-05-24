#ifndef TYPEGROUPFORM_H
#define TYPEGROUPFORM_H

#include <QPushButton>
#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include "../model/typegroup.h"

class TypeGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit TypeGroupForm(TypeGroup *typeGroup, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QPushButton *m_buttonApply;
    QPushButton *m_buttonCancel;
    TypeGroupEditBox *m_editTypeGroup;
    TypeGroup *m_typeGroup;
    enum Operation m_op;
};

#endif // TYPEGROUPFORM_H
