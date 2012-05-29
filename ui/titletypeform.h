#ifndef TITLETYPEFORM_H
#define TITLETYPEFORM_H

#include <QWidget>
#include <QTextEdit>
#include <QDateEdit>
#include "stackablewidget.h"
#include "../model/coremetadatatype.h"
#include "elementtypeeditbox.h"

class TitleTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TitleTypeForm(TitleType *title, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QHBoxLayout *m_mainHLayout;
    QDateEdit *m_editAttributionDate;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editTitle;
    TitleType *m_title;
    Operation m_op;
};

#endif // TITLETYPEFORM_H
