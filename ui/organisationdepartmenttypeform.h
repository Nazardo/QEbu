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
    bool eventFilter(QObject *obj, QEvent *event);

    OrganisationDepartmentType *m_organisationDepartment;
    ElementTypeEditBox *m_editElementType;
    QLineEdit *m_editDepartmentId;
};

#endif // ORGANISATIONDEPARTMENTTYPEFORM_H
