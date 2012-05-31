#ifndef INT8FORM_H
#define INT8FORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QSpinBox>
#include <QCheckBox>

class Int8Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Int8Form(Int8 *int8, QEbuMainWindow *mainWindow, QWidget *parent = 0);
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
    Int8 *m_int8;
    Operation m_op;
};

#endif // INT8FORM_H
