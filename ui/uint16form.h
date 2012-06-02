#ifndef UINT16FORM_H
#define UINT16FORM_H

#include "stackablewidget.h"

class UInt16;
class TypeGroupEditBox;
class QSpinBox;
class QCheckBox;

class Uint16Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint16Form(UInt16 *uint16,
                        QEbuMainWindow *mainWindow,
                        QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
private:
    TypeGroupEditBox *m_editTypeGroup;
    QSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    UInt16 *m_uint16;
};

#endif // UINT16FORM_H
