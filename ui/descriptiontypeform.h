#ifndef DESCRIPTIONTYPEFORM_H
#define DESCRIPTIONTYPEFORM_H

#include "stackablewidget.h"
#include "../model/ebucoremaintype.h"
#include "typegroupeditbox.h"
#include <QTextEdit>
#include "elementtypeeditbox.h"

class DescriptionTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DescriptionTypeForm(DescriptionType *description, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
private:
    TypeGroupEditBox *m_editTypeGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editElementDescription;
    DescriptionType *m_description;
    Operation m_op;
};

#endif // DESCRIPTIONTYPEFORM_H
