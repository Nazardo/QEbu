#ifndef UINT32FORM_H
#define UINT32FORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include <QSpinBox>
#include <QCheckBox>

class Uint32Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint32Form(UInt32 *uint32, QEbuMainWindow *mainWindow, QWidget *parent = 0);
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
    UInt32 *m_uint32;
    Operation m_op;
};

#endif // UINT32FORM_H
