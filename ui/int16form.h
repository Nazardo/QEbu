#ifndef INT16FORM_H
#define INT16FORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QSpinBox>
#include <QCheckBox>

class Int16Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Int16Form(Int16 *int16, QEbuMainWindow *mainWindow, QWidget *parent = 0);
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
    Int16 *m_int16;
    Operation m_op;
};

#endif // INT16FORM_H
