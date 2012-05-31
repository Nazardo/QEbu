#ifndef UINTFORM64_H
#define UINTFORM64_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include "elementtypeeditbox.h"
#include <QSpinBox>

class Uint64Form : public StackableWidget
{
    Q_OBJECT
public:
    explicit Uint64Form(UInt64 *uint64, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
private:
    QHBoxLayout *m_mainHLayout;
    TypeGroupEditBox *m_editTypeGroup;
    QSpinBox *m_spinValue;
    UInt64 *m_uint64;
    Operation m_op;
};

#endif // UINTFORM64_H
