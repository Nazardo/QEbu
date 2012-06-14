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

#ifndef RATINGTYPEFORM_H
#define RATINGTYPEFORM_H

#include "stackablewidget.h"

class RatingType;
class TypeGroupEditBox;
class FormatGroupEditBox;
class QLineEdit;

class RatingTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit RatingTypeForm(RatingType *rating,
                            QEbuMainWindow *mainWindow,
                            QWidget *parent = 0);
    QString toString();
    bool checkCompliance();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void ratingProviderRemoveClicked();
    void ratingProviderClicked();
    void ratingProviderClosed(Operation op, QVariant value);
private:
    bool eventFilter(QObject *obj, QEvent *event);

    TypeGroupEditBox *m_editTypeGroup;
    FormatGroupEditBox *m_editFormatGroup;
    QLineEdit *m_editRatingValue;
    QLineEdit *m_editRatingScaleMaxValue;
    QLineEdit *m_editRatingScaleMinValue;
    QLineEdit *m_editRatingProvider;
    RatingType *m_rating;
};

#endif // RATINGTYPEFORM_H
