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

#ifndef COORDINATESTYPEFORM_H
#define COORDINATESTYPEFORM_H

#include "stackablewidget.h"

class CoordinatesType;
class FormatGroupEditBox;
class QCheckBox;
class QDoubleSpinBox;

class CoordinatesTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CoordinatesTypeForm(CoordinatesType *coordinates,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
private slots:
    void cancelClicked();
    void applyClicked();
    void posxChanged();
    void posyChanged();
private:
    bool eventFilter(QObject *obj, QEvent *event);
    QVBoxLayout *m_mainVLayout;
    FormatGroupEditBox *m_editFormatGroup;
    QDoubleSpinBox *m_spinPosx;
    QDoubleSpinBox *m_spinPosy;
    QCheckBox *m_checkPosx;
    QCheckBox *m_checkPosy;
    CoordinatesType *m_coordinates;
};

#endif // COORDINATESTYPEFORM_H
