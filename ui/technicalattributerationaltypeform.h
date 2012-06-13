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

#ifndef TECHNICALATTRIBUTERATIONALTYPEFORM_H
#define TECHNICALATTRIBUTERATIONALTYPEFORM_H

#include "stackablewidget.h"

class TechnicalAttributeRationalType;
class QDoubleSpinBox;
class QSignedSpinBox;
class QSpinBox;
class QUnsignedSpinBox;
class QCheckBox;
class TypeGroupEditBox;

class TechnicalAttributeRationalTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TechnicalAttributeRationalTypeForm(
            TechnicalAttributeRationalType *rational,
            QEbuMainWindow *mainWindow, QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    void valueChanged();
    void numeratorChanged();
    void denominatorChanged();
private:
    bool eventFilter(QObject *, QEvent *);
    QSignedSpinBox *m_spinValue;
    QSpinBox *m_spinFactorNumerator;
    QSpinBox *m_spinFactorDenominator;
    QCheckBox *m_checkValue;
    QCheckBox *m_checkNumerator;
    QCheckBox *m_checkDenominator;
    TypeGroupEditBox *m_editTypeGroup;
    TechnicalAttributeRationalType *m_rational;
};


#endif // TECHNICALATTRIBUTERATIONALTYPEFORM_H
