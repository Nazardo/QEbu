#ifndef ADDRESSTYPEFORM_H
#define ADDRESSTYPEFORM_H

#include "stackablewidget.h"

class AddressType;
class QLineEdit;
class QPushButton;
class ListView;
class TypeGroupEditBox;
class DetailsType;

class AddressTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AddressTypeForm(AddressType *address,
                             QEbuMainWindow *mainWindow,
                             QWidget *parent = 0);
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
    void addressLineChecked(bool checked);

private:
    enum EditMode { ContactDetails, OrganisationDetails, Roles };
    void updateListAndButtons();

    ListView *m_listView;
    QLineEdit *m_editAddressTownCity;
    QLineEdit *m_editAddressCountryState;
    QLineEdit *m_editAddressDeliveryCode;
    TypeGroupEditBox *m_editCountry;
    QPushButton *m_buttonAddressLine;
    AddressType *m_address;
    EditMode m_currentEditMode;
};

#endif // ADDRESSTYPEFORM_H
