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

#ifndef RIGHTSTYPEFORM_H
#define RIGHTSTYPEFORM_H

#include "stackablewidget.h"

class RightsType;
class ListView;
class TypeGroupEditBox;
class QLineEdit;
class QTextEdit;
class QCheckBox;
class QPushButton;

class RightsTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit RightsTypeForm(RightsType *rights,
                            QEbuMainWindow *mainWindow,
                            QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
    // List view
    void addClicked();
    void editClicked();
    void removeClicked();
    // -
    void formatIDRefsChecked(bool checked);
    void rightsChecked(bool checked);
    void rightsHolderChecked(bool checked);
    void exploitationIssuesChecked(bool checked);
    void coverageChecked(bool checked);
    void disclaimerChecked(bool checked);
    void rightsIdChecked(bool checked);
    void contactDetailsChecked(bool checked);
    // -
    void rightsFormClosed(Operation op, QVariant value);
    void rightsHolderFormClosed(Operation op, QVariant value);
    void exploitationIssuesFormClosed(Operation op, QVariant value);
    void coverageFormClosed(Operation op, QVariant value);
    void disclaimerFormClosed(Operation op, QVariant value);
    void rightsIdFormClosed(Operation op, QVariant value);
    void contactDetailsFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    enum EditMode {
        FormatIDRefs,
        Rights,
        RightsHolder,
        ExploitationIssues,
        Coverage,
        Disclaimer,
        RightsId,
        ContactDetails
    };
    void updateListAndButtons();

    ListView *m_listView;
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editRightsLink;
    QCheckBox *m_checkRightsClearanceFlag;
    QTextEdit *m_textNote;
    QPushButton *m_comboFormatIDRefs;
    QPushButton *m_buttonRights;
    QPushButton *m_buttonRightsHolder;
    QPushButton *m_buttonExploitationIssues;
    QPushButton *m_buttonCoverage;
    QPushButton *m_buttonDisclaimer;
    QPushButton *m_buttonRightsId;
    QPushButton *m_buttonContactDetails;
    RightsType *m_rights;
    EditMode m_currentEditMode;
};

#endif // RIGHTSTYPEFORM_H
