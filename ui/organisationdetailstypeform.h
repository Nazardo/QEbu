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
    bool eventFilter(QObject *obj, QEvent *event);
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
