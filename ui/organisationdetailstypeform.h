#ifndef ORGANISATIONDETAILSTYPEFORM_H
#define ORGANISATIONDETAILSTYPEFORM_H

#include "stackablewidget.h"

class OrganisationDetailsType;
class ListView;
class QLineEdit;
class ElementTypeEditBox;
class QPushButton;

class OrganisationDetailsTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit OrganisationDetailsTypeForm(
            OrganisationDetailsType *organisationDetails,
            QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
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
    enum EditMode {
        OrganisationDepartment,
        Details,
        Contacts
    };
    void updateListAndButtons();

    ListView *m_listView;
    QLineEdit *m_editOrganisationId;
    ElementTypeEditBox *m_editOrganisationName;
    QPushButton *m_buttonOrganisationDepartment;
    QPushButton *m_buttonDetails;
    QPushButton *m_buttonContacts;
    OrganisationDetailsType *m_organisationDetails;
    EditMode m_currentEditMode;
};

#endif // ORGANISATIONDETAILSTYPEFORM_H
