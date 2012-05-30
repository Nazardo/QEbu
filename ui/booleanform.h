#ifndef BOOLEANFORM_H
#define BOOLEANFORM_H

#include "stackablewidget.h"
#include "typegroupeditbox.h"
#include <QCheckBox>

class BooleanForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit BooleanForm(Boolean *boolean, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QHBoxLayout *m_mainHLayout;
    QCheckBox *m_checkValue;
    TypeGroupEditBox *m_editTypeGroup;
    Boolean  *m_boolean;
    Operation m_op;
};

#endif // BOOLEANFORM_H
