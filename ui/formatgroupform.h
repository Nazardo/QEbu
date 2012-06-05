#ifndef FORMATGROUPFORM_H
#define FORMATGROUPFORM_H

#include "stackablewidget.h"

class FormatGroup;
class FormatGroupEditBox;

class FormatGroupForm : public StackableWidget
{
Q_OBJECT
public:
    explicit FormatGroupForm(FormatGroup *typeGroup,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    FormatGroupEditBox *m_editFormatGroup;
};

#endif // FORMATGROUPFORM_H
