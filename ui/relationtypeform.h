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

#ifndef RELATIONTYPEFORM_H
#define RELATIONTYPEFORM_H

#include "stackablewidget.h"

class RelationType;
class QSpinBox;
class QCheckBox;
class QTextEdit;
class QLineEdit;
class TypeGroupEditBox;
class ElementTypeEditBox;
class QRadioButton;
class QPushButton;
class QLabel;

class RelationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit RelationTypeForm(RelationType *relation,
                              QEbuMainWindow *mainWindow,
                              QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
    void setTitle(const QString &title);
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void relationIdentifierRemoveClicked();
    void relationIdentifierClicked();
    void relationIdentifierClosed(Operation op, QVariant value);
    // -
    void runningOrderNumberChanged();
    // -
    void radioRelationChecked(bool checked);
    void radioRelationLinkChecked(bool checked);
    void radioRelationIdentifierChecked(bool checked);
private:
    bool eventFilter(QObject *obj, QEvent *event);

    TypeGroupEditBox *m_editTypeGroup;
    QSpinBox *m_spinRunningOrderNumber;
    QCheckBox *m_checkRunningOrderNumber;
    QTextEdit *m_textNote;
    QLabel *m_labelRelationLink;
    QLineEdit *m_editRelationLink;
    ElementTypeEditBox *m_editElementRelation;
    QLabel *m_labelRelationIdentifier;
    QLineEdit *m_editRelationIdentifier;
    QPushButton *m_buttonRelationIdentifierAdd;
    QPushButton *m_buttonRelationIdentifierRemove;
    RelationType *m_relation;
    QString m_title;
    QRadioButton *m_radioRelation;
    QRadioButton *m_radioRelationLink;
    QRadioButton *m_radioRelationIdentifier;
};

#endif // RELATIONTYPEFORM_H
