/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@gmail.com
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

#ifndef DETAILSTYPEFORM_H
#define DETAILSTYPEFORM_H

#include "stackablewidget.h"

class DetailsType;
class ListView;
class QPushButton;
class QLineEdit;
class TypeGroupEditBox;

class DetailsTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DetailsTypeForm(DetailsType *details,
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
    void addressChecked(bool checked);
    // -
    void addressFormClosed(Operation op, QVariant value);
private:
    void updateListAndButtons();
    bool eventFilter(QObject *, QEvent *);
    ListView *m_listView;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editEmailAddress;
    QLineEdit *m_editWebAddress;
    QLineEdit *m_editTelephoneNumber;
    QLineEdit *m_editMobileTelephoneNumber;
    QPushButton *m_buttonAddress;
    DetailsType *m_details;
};

#endif // DETAILSTYPEFORM_H
