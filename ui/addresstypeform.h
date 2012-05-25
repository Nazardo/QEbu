#ifndef ADDRESSTYPEFORM_H
#define ADDRESSTYPEFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "stackablewidget.h"
#include "listview.h"
#include "typegroupeditbox.h"
#include "../model/detailstype.h"

class AddressTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AddressTypeForm(AddressType *entity, QEbuMainWindow *mainWindow, QWidget *parent = 0);
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

    QHBoxLayout *m_mainHLayout;
    ListView *m_listView;
    QLineEdit *m_editAddressTownCity;
    QLineEdit *m_editAddressCountryState;
    QLineEdit *m_editAddressDeliveryCode;
    TypeGroupEditBox *m_editCountry;
    QPushButton *m_buttonAddressLine;
    AddressType *m_address;
    Operation m_op;
    EditMode m_currentEditMode;
};

#endif // ADDRESSTYPEFORM_H
