#ifndef INT8FORM_H
#define INT8FORM_H

#include "stackablewidget.h"

class Int8;
class TypeGroupEditBox;
class QSpinBox;
class QCheckBox;

class Int8Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Int8Form(Int8 *int8,
                      QEbuMainWindow *mainWindow,
                      QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
private:
    QSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    TypeGroupEditBox *m_editTypeGroup;
    Int8 *m_int8;
};

#endif // INT8FORM_H
