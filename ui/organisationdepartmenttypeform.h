#ifndef ORGANISATIONDEPARTMENTTYPEFORM_H
#define ORGANISATIONDEPARTMENTTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "stackablewidget.h"
#include "elementtypeeditbox.h"
#include "../model/organisationdetailstype.h"

class OrganisationDepartmentTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit OrganisationDepartmentTypeForm(OrganisationDepartmentType *organisationDepartment,
                                            QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
private:
    enum EditMode { ContactDetails, OrganisationDetails, Roles };
    void updateListAndButtons();

    OrganisationDepartmentType *m_organisationDepartment;
    ElementTypeEditBox *m_editElementType;
    QLineEdit *m_editDepartmentId;
    QPushButton *m_buttonCancel;
    QPushButton *m_buttonApply;
    Operation m_op;
};

#endif // ORGANISATIONDEPARTMENTTYPEFORM_H
