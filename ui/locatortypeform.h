#ifndef LOCATORTYPEFORM_H
#define LOCATORTYPEFORM_H

#include "stackablewidget.h"

class TypeGroupEditBox;
class LocatorType;
class QLineEdit;

class LocatorTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit LocatorTypeForm(LocatorType *locator,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
    QString toString();
private slots:
    void applyClicked();
private:
    bool eventFilter(QObject *obj, QEvent *event);

    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editLocatorValue;
    LocatorType *m_locator;
};

#endif // LOCATORTYPEFORM_H
