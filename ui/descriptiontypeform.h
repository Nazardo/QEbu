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

#ifndef DESCRIPTIONTYPEFORM_H
#define DESCRIPTIONTYPEFORM_H

#include "stackablewidget.h"

class DescriptionType;
class TypeGroupEditBox;
class QTextEdit;
class ElementTypeEditBox;

class DescriptionTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DescriptionTypeForm(DescriptionType *description,
                                 QEbuMainWindow *mainWindow,
                                 QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    bool eventFilter(QObject *, QEvent *);
private:
    TypeGroupEditBox *m_editTypeGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editElementDescription;
    DescriptionType *m_description;
};

#endif // DESCRIPTIONTYPEFORM_H
