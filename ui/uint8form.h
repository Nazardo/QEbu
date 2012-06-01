#ifndef UINT8FORM_H
#define UINT8FORM_H

#include "stackablewidget.h"

class UInt8;
class TypeGroupEditBox;
class QSpinBox;
class QCheckBox;

class Uint8Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint8Form(UInt8 *uint8,
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
    TypeGroupEditBox *m_editTypeGroup;
    QSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    UInt8 *m_uint8;
};

#endif // UINT8FORM_H
