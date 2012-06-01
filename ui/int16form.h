#ifndef INT16FORM_H
#define INT16FORM_H

#include "stackablewidget.h"

class Int16;
class TypeGroupEditBox;
class QSpinBox;
class QCheckBox;

class Int16Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Int16Form(Int16 *int16,
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
    Int16 *m_int16;
};

#endif // INT16FORM_H
