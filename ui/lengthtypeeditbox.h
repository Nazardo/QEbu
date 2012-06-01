#ifndef LENGTHTYPEEDITBOX_H
#define LENGTHTYPEEDITBOX_H

#include <QWidget>

class QCheckBox;
class QSpinBox;
class QLineEdit;
class LengthType;

class LengthTypeEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit LengthTypeEditBox(LengthType *length, QWidget *parent = 0);
    LengthType *lengthType();
    void setLabel(const QString &label);
private:
    QCheckBox *m_check;
    QSpinBox *m_editValue;
    QLineEdit *m_editUnit;
};

#endif // LENGTHTYPEEDITBOX_H
