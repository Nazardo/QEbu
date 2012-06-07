#ifndef LENGTHTYPEFORM_H
#define LENGTHTYPEFORM_H

#include "stackablewidget.h"

class QLineEdit;
class QUnsignedSpinBox;
class QCheckBox;
class LengthType;

class LengthTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit LengthTypeForm(LengthType *description,
                            QEbuMainWindow *mainWindow,
                            QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void valueChanged();
private:
    QLineEdit *m_editUnit;
    QUnsignedSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    LengthType *m_length;
};

#endif // LENGTHTYPEFORM_H
