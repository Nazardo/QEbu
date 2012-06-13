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

#ifndef LOCATIONTYPEFORM_H
#define LOCATIONTYPEFORM_H

#include "stackablewidget.h"

class LocationType;
class QLineEdit;
class QTextEdit;
class TypeGroupEditBox;

class LocationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit LocationTypeForm(LocationType *location,
                              QEbuMainWindow *mainWindow,
                              QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void coordinatesClicked();
    void coordinatesRemoveClicked();
    void coordinatesClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);
    TypeGroupEditBox *m_editTypeGroup;
    QLineEdit *m_editLocationId;
    QTextEdit *m_textNote;
    QLineEdit *m_editName;
    QLineEdit *m_editCoordinates;
    QLineEdit *m_editCode;
    LocationType *m_location;
};

#endif // LOCATIONTYPEFORM_H
