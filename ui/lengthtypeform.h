#ifndef LENGTHTYPEFORM_H
#define LENGTHTYPEFORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include <QLineEdit>


class LengthTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit LengthTypeForm(LengthType *description, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
private:
    QLineEdit *m_editUnit;
    QLineEdit *m_editValue;
    LengthType *m_length;
    Operation m_op;
};

#endif // LENGTHTYPEFORM_H
