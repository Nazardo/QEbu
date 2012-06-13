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

#ifndef ALTERNATIVETITLETYPEFORM_H
#define ALTERNATIVETITLETYPEFORM_H

#include "stackablewidget.h"

class QTextEdit;
class AlternativeTitleType;
class TypeGroupEditBox;
class StatusGroupEditBox;
class DateGroupEditBox;
class ElementTypeEditBox;

class AlternativeTitleTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit AlternativeTitleTypeForm(AlternativeTitleType *alternativeTitle,
                                      QEbuMainWindow *mainWindow,
                                      QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
private slots:
    void applyClicked();
    void cancelClicked();
private:
    bool eventFilter(QObject *obj, QEvent *event);
    AlternativeTitleType *m_alternativeTitle;
    TypeGroupEditBox *m_editTypeGroup;
    StatusGroupEditBox *m_editStatusGroup;
    DateGroupEditBox *m_editDateGroup;
    QTextEdit *m_textNote;
    ElementTypeEditBox *m_editTitle;
};

#endif // ALTERNATIVETITLETYPEFORM_H
