#ifndef FLOATFORM_H
#define FLOATFORM_H

#include "stackablewidget.h"

class Float;
class TypeGroupEditBox;
class QDoubleSpinBox;
class QCheckBox;

class FloatForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit FloatForm(Float *p_float,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
private:
    QDoubleSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    TypeGroupEditBox *m_editTypeGroup;
    Float  *m_float;
};

#endif // FLOATFORM_H
