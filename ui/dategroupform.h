#ifndef DATEGROUPFORM_H
#define DATEGROUPFORM_H

#include "stackablewidget.h"
#include "../model/dategroup.h"
#include "dategroupeditbox.h"

class DateGroupForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DateGroupForm(DateGroup *dateGroup, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    DateGroupEditBox *m_editDateGroup;
    Operation m_op;
};

#endif // DATEGROUPFORM_H
