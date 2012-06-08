#ifndef TITLETYPEFORM_H
#define TITLETYPEFORM_H

#include "stackablewidget.h"

class TitleType;
class QTextEdit;
class QDateEdit;
class QCheckBox;
class ElementTypeEditBox;

class TitleTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TitleTypeForm(TitleType *title,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
    void attributionDateChanged();
    bool checkCompliance();
private:
    QDateEdit *m_editAttributionDate;
    QTextEdit *m_textNote;
    QCheckBox *m_checkAttributionDate;
    ElementTypeEditBox *m_editTitle;
    TitleType *m_title;
};

#endif // TITLETYPEFORM_H
