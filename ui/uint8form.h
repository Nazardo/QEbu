#ifndef UINT8FORM_H
#define UINT8FORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include <QSpinBox>
#include <QCheckBox>

class Uint8Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint8Form(UInt8 *uint8, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
private:
    QHBoxLayout *m_mainHLayout;
    TypeGroupEditBox *m_editTypeGroup;
    QSpinBox *m_spinValue;
    QCheckBox *m_checkValue;
    UInt8 *m_uint8;
    Operation m_op;
};

#endif // UINT8FORM_H
