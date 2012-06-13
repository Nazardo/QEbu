/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

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
    bool eventFilter(QObject *obj, QEvent *event);
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
