#ifndef TEMPORALTYPEFORM_H
#define TEMPORALTYPEFORM_H

#include "stackablewidget.h"
#include "model/coremetadatatype.h"
#include "typegroupeditbox.h"
#include "dategroupeditbox.h"
#include <QTextEdit>
#include <QLineEdit>

class TemporalTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TemporalTypeForm(TemporalType *temporal, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QVBoxLayout *m_mainVLayout;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editPeriodId;
    QTextEdit *m_textNote;
    DateGroupEditBox *m_editPeriodOfTime;
    TemporalType *m_temporal;
    Operation m_op;
};

#endif // TEMPORALTYPEFORM_H
