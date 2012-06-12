#ifndef TEMPORALTYPEFORM_H
#define TEMPORALTYPEFORM_H

#include "stackablewidget.h"

class TemporalType;
class TypeGroupEditBox;
class DateGroupEditBox;
class QLineEdit;
class QTextEdit;

class TemporalTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TemporalTypeForm(TemporalType *temporal,
                              QEbuMainWindow *mainWindow,
                              QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    bool eventFilter(QObject *, QEvent *);
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editPeriodId;
    QTextEdit *m_textNote;
    DateGroupEditBox *m_editPeriodOfTime;
    TemporalType *m_temporal;
};

#endif // TEMPORALTYPEFORM_H
