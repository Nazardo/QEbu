#ifndef DATEGROUPFORM_H
#define DATEGROUPFORM_H

#include "stackablewidget.h"

class DateGroup;
class DateGroupEditBox;

class DateGroupForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DateGroupForm(DateGroup *dateGroup,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
private slots:
    void cancelClicked();
    void applyClicked();
private:
    bool eventFilter(QObject *, QEvent *);
    DateGroupEditBox *m_editDateGroup;
    QString m_title;
    DateGroup *m_dateGroup;
};

#endif // DATEGROUPFORM_H
