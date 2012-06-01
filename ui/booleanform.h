#ifndef BOOLEANFORM_H
#define BOOLEANFORM_H

#include "stackablewidget.h"

class Boolean;
class QCheckBox;
class TypeGroupEditBox;

class BooleanForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit BooleanForm(Boolean *boolean,
                         QEbuMainWindow *mainWindow,
                         QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    QCheckBox *m_checkValue;
    TypeGroupEditBox *m_editTypeGroup;
    Boolean  *m_boolean;
};

#endif // BOOLEANFORM_H
