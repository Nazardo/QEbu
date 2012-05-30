#ifndef INT64FORM_H
#define INT64FORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QSpinBox>

class Int64Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Int64Form(Int64 *int64, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QHBoxLayout *m_mainHLayout;
    QSpinBox *m_spinValue;
    TypeGroupEditBox *m_editTypeGroup;
    Int64 *m_int64;
    Operation m_op;
};

#endif // INT64FORM_H
