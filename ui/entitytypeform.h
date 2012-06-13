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

#ifndef ENTITYTYPEFORM_H
#define ENTITYTYPEFORM_H

#include "stackablewidget.h"

class EntityType;
class ListView;
class QPushButton;
class QLineEdit;

class EntityTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit EntityTypeForm(EntityType *entity,
                            QEbuMainWindow *mainWindow,
                            QWidget *parent = 0);
    QString toString();
    void setTitle(const QString &title);
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void contactDetailsChecked(bool checked);
    void organisationDetailsChecked(bool checked);
    void roleChecked(bool checked);
    // -
    void contactDetailsFormClosed(Operation op, QVariant value);
    void organisationDetailsFormClosed(Operation op, QVariant value);
    void roleFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    enum EditMode {
        ContactDetails,
        OrganisationDetails,
        Roles
    };
    void updateListAndButtons();

    ListView *m_listView;
    QLineEdit *m_editEntityId;
    QPushButton *m_buttonContactDetails;
    QPushButton *m_buttonOrganisationDetails;
    QPushButton *m_buttonRole;
    EntityType *m_entity;
    EditMode m_currentEditMode;
    QString m_title;
};

#endif // ENTITYTYPEFORM_H
