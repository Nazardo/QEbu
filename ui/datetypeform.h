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

#ifndef DATETYPEFORM_H
#define DATETYPEFORM_H

#include "stackablewidget.h"

class DateType;
class ListView;
class QPushButton;

class DateTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DateTypeForm(DateType *date,
                          QEbuMainWindow *mainWindow,
                          QWidget *parent = 0);
    QString toString();
private slots:
    void applyClicked();
    void cancelClicked();
    // Toggle buttons:
    void dateChecked(bool checked);
    void createdChecked(bool checked);
    void issuedChecked(bool checked);
    void modifiedChecked(bool checked);
    void digitisedChecked(bool checked);
    void alternativeChecked(bool checked);
    // List view:
    void addClicked();
    void editClicked();
    void removeClicked();
    void elementTypeFormClosed(Operation op, QVariant value);
    void dateGroupFormClosed(Operation op, QVariant value);
    void alternativeTypeFormClosed(Operation op, QVariant value);
private:
    enum EditMode {
        Date,
        Created,
        Issued,
        Modified,
        Digitised,
        Alternative
    };
    void updateListTitle();
    bool eventFilter(QObject *, QEvent *);
    EditMode m_currentEditMode;
    DateType *m_date;
    QPushButton *m_buttonDate;
    QPushButton *m_buttonCreated;
    QPushButton *m_buttonIssued;
    QPushButton *m_buttonModified;
    QPushButton *m_buttonDigitised;
    QPushButton *m_buttonAlternative;
    ListView *m_listView;
};

#endif // DATETYPEFORM_H
