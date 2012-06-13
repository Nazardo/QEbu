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

#ifndef TYPETYPEFORM_H
#define TYPETYPEFORM_H

#include "stackablewidget.h"

class TypeType;
class ListView;
class QTextEdit;
class QPushButton;

class TypeTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TypeTypeForm(TypeType *type,
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
    void typeChecked(bool checked);
    void genreChecked(bool checked);
    void objectTypeChecked(bool checked);
    void targetAudienceChecked(bool checked);
    // -
    void typeFormClosed(Operation op, QVariant value);
    void genreFormClosed(Operation op, QVariant value);
    void objectTypeFormClosed(Operation op, QVariant value);
    void targetAudienceFormClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    enum EditMode { Type, Genre, ObjectType, TargetAudience };
    void updateListAndButtons();

    ListView *m_listView;
    QTextEdit *m_textNote;
    QPushButton *m_buttonType;
    QPushButton *m_buttonGenre;
    QPushButton *m_buttonObjectType;
    QPushButton *m_buttonTargetAudience;
    TypeType *m_type;
    EditMode m_currentEditMode;
};

#endif // TYPETYPEFORM_H
