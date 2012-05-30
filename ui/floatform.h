#ifndef FLOATFORM_H
#define FLOATFORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QDoubleSpinBox>

class FloatForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit FloatForm(Float *p_float, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QHBoxLayout *m_mainHLayout;
    QDoubleSpinBox *m_spinValue;
    TypeGroupEditBox *m_editTypeGroup;
    Float  *m_float;
    Operation m_op;
};

#endif // FLOATFORM_H
