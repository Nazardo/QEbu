#ifndef INT64FORM_H
#define INT64FORM_H

#include "stackablewidget.h"

class Int64;
class TypeGroupEditBox;
class QSignedSpinBox;
class QCheckBox;

class Int64Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Int64Form(Int64 *int64,
                       QEbuMainWindow *mainWindow,
                       QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
private:
    QSignedSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    TypeGroupEditBox *m_editTypeGroup;
    Int64 *m_int64;
};

#endif // INT64FORM_H
