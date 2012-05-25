#ifndef ORGANISATIONDETAILSTYPEFORM_H
#define ORGANISATIONDETAILSTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "stackablewidget.h"
#include "listview.h"
#include "elementtypeeditbox.h"
#include "../model/organisationdetailstype.h"

class OrganisationDetailsTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit OrganisationDetailsTypeForm(OrganisationDetailsType *organisationDetails, QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void organisationDepartmentChecked(bool checked);
    void contactsChecked(bool checked);
    void detailsChecked(bool checked);
    // -
    void organisationDepartmentFormClosed(Operation op, QVariant value);
    void detailsFormClosed(Operation op, QVariant value);
    void contactsFormClosed(Operation op, QVariant value);
private:
    enum EditMode { OrganisationDepartment, Details, Contacts };
    void updateListAndButtons();

    QHBoxLayout *m_mainHLayout;
    ListView *m_listView;
    QLineEdit *m_editOrganisationId;
    ElementTypeEditBox *m_editOrganisationName;
    QPushButton *m_buttonOrganisationDepartment;
    QPushButton *m_buttonDetails;
    QPushButton *m_buttonContacts;
    OrganisationDetailsType *m_organisationDetails;
    Operation m_op;
    EditMode m_currentEditMode;
};

#endif // ORGANISATIONDETAILSTYPEFORM_H
