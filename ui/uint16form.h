#ifndef UINT16FORM_H
#define UINT16FORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include <QSpinBox>
#include <QCheckBox>

class Uint16Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint16Form(UInt16 *uint16, QEbuMainWindow *mainWindow, QWidget *parent = 0);
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
    UInt16 *m_uint16;
    Operation m_op;
};

#endif // UINT16FORM_H
