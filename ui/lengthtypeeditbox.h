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

#ifndef LENGTHTYPEEDITBOX_H
#define LENGTHTYPEEDITBOX_H

#include <QWidget>

class QCheckBox;
class QUnsignedSpinBox;
class QLineEdit;
class LengthType;

class LengthTypeEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit LengthTypeEditBox(LengthType *length,
                               QWidget *parent = 0);
    LengthType *lengthType();
    void setLabel(const QString &label);
    QUnsignedSpinBox *editValue();
    QLineEdit *editUnit();
private slots:
    void lengthChanged();
private:
    QCheckBox *m_check;
    QUnsignedSpinBox *m_editValue;
    QLineEdit *m_editUnit;
};

#endif // LENGTHTYPEEDITBOX_H
