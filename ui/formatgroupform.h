#ifndef TYPEGROUPFORM_H
#define TYPEGROUPFORM_H

#include <QPushButton>
#include "stackablewidget.h"
#include "formatgroupeditbox.h"
#include "../model/formatgroup.h"

class FormatGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit FormatGroupForm(FormatGroup *typeGroup, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QPushButton *m_buttonApply;
    QPushButton *m_buttonCancel;
    FormatGroupEditBox *m_editFormatGroup;
    Operation m_op;
};

#endif // TYPEGROUPFORM_H
