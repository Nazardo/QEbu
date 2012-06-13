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

#ifndef TIMETYPEFORM_H
#define TIMETYPEFORM_H

#include "stackablewidget.h"
#include <QTimeEdit>

class TimeType;
class QLineEdit;
class QSignedSpinBox;
class QUnsignedSpinBox;
class QCheckBox;
class FormatGroupEditBox;
class QRadioButton;
class QLabel;

class TimeTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit TimeTypeForm(TimeType *time,
                          QEbuMainWindow *mainWindow,
                          QWidget *parent = 0);
    QString toString();
signals:
private slots:
    void cancelClicked();
    void applyClicked();
    // -
    void timecodeChecked(bool checked);
    void normalPlaytimeChecked(bool checked);
    void editUnitNumberChecked(bool checked);
    void timeChecked(bool checked);
    // -
    void rateChanged();
    void factorNumeratorChanged();
    void factorDenominatorChanged();
private:
    void updateListAndButtons();
    bool eventFilter(QObject *, QEvent *);
    QWidget *m_labelTimecode;
    QLineEdit *m_editTimecode;
    QWidget *m_labelNormalPlaytime;
    QTimeEdit *m_editNormalPlaytime;
    QUnsignedSpinBox *m_spinRate;
    QUnsignedSpinBox *m_spinFactorNumerator;
    QUnsignedSpinBox *m_spinFactorDenominator;
    QSignedSpinBox *m_spinUnitNumberValue;
    QCheckBox *m_checkRate;
    QCheckBox *m_checkFactorNumerator;
    QCheckBox *m_checkFactorDenominator;
    QLabel *m_labelUnitNumberValue;
    QLineEdit *m_editTimeValue;
    FormatGroupEditBox *m_editFormatGroup;
    QRadioButton *m_radioTimecode;
    QRadioButton *m_radioNormalPlaytime;
    QRadioButton *m_radioTime;
    QRadioButton *m_radioEditUnitNumber;
    TimeType *m_time;
};

#endif // TIMETYPEFORM_H
