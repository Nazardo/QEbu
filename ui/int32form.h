#ifndef INT32FORM_H
#define INT32FORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QSpinBox>
#include <QCheckBox>

class Int32Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Int32Form(Int32 *int32, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
private:
    QHBoxLayout *m_mainHLayout;
    QSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    TypeGroupEditBox *m_editTypeGroup;
    Int32 *m_int32;
    Operation m_op;
};

#endif // INT32FORM_H
