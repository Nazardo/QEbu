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

#ifndef COVERAGETYPEFORM_H
#define COVERAGETYPEFORM_H

#include "stackablewidget.h"

class CoverageType;
class QPushButton;
class ListView;
class ElementTypeEditBox;

class CoverageTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit CoverageTypeForm(CoverageType *coverage,
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
    void temporalChecked(bool checked);
    void locationChecked(bool checked);
    // -
    void temporalFormClosed(Operation op, QVariant value);
    void locationFormClosed(Operation op, QVariant value);
private:
    enum EditMode { Temporal, Location };
    void updateListAndButtons();
    bool eventFilter(QObject *obj, QEvent *event);
    ListView *m_listView;
    ElementTypeEditBox *m_editCoverage;
    QPushButton *m_buttonTemporal;
    QPushButton *m_buttonLocation;
    CoverageType *m_coverage;
    EditMode m_currentEditMode;
};

#endif // COVERAGETYPEFORM_H
