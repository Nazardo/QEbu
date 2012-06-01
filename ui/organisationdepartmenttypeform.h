#ifndef ORGANISATIONDEPARTMENTTYPEFORM_H
#define ORGANISATIONDEPARTMENTTYPEFORM_H

#include "stackablewidget.h"

class OrganisationDepartmentType;
class ElementTypeEditBox;
class QLineEdit;

class OrganisationDepartmentTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit OrganisationDepartmentTypeForm(
            OrganisationDepartmentType *organisationDepartment,
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
};

#endif // ORGANISATIONDEPARTMENTTYPEFORM_H
