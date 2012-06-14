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

#ifndef HASTRACKPARTTYPEFORM_H
#define HASTRACKPARTTYPEFORM_H

#include "stackablewidget.h"

class HasTrackPartType;
class QLineEdit;

class HasTrackPartTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit HasTrackPartTypeForm(HasTrackPartType *hasTrackPart,
                                  QEbuMainWindow *mainWindow,
                                  QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void trackPartTitleRemoveClicked();
    void trackPartTitleClicked();
    void trackPartTitleClosed(Operation op, QVariant value);
    void destinationStartRemoveClicked();
    void destinationStartClicked();
    void destinationStartClosed(Operation op, QVariant value);
    void destinationEndRemoveClicked();
    void destinationEndClicked();
    void destinationEndClosed(Operation op, QVariant value);
    void sourceStartRemoveClicked();
    void sourceStartClicked();
    void sourceStartClosed(Operation op, QVariant value);
    void sourceEndRemoveClicked();
    void sourceEndClicked();
    void sourceEndClosed(Operation op, QVariant value);
    void relationRemovedClicked();
    void relationClicked();
    void relationClosed(Operation op, QVariant value);

private:
    bool eventFilter(QObject *obj, QEvent *event);
    QLineEdit *m_editRelation;
    QLineEdit *m_editTrackPartTitle;
    QLineEdit *m_editDestinationStart;
    QLineEdit *m_editDestinationEnd;
    QLineEdit *m_editSourceStart;
    QLineEdit *m_editSourceEnd;
    HasTrackPartType *m_hasTrackPart;
};

#endif // HASTRACKPARTTYPEFORM_H
