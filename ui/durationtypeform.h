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

#ifndef DURATIONTYPEFORM_H
#define DURATIONTYPEFORM_H

#include "stackablewidget.h"
#include <QTimeEdit>

class DurationType;
class QLineEdit;
class QSpinBox;
class QUnsignedSpinBox;
class QSignedSpinBox;
class QCheckBox;
class FormatGroupEditBox;
class QRadioButton;

class DurationTypeForm : public StackableWidget
{
    Q_OBJECT
public:
    explicit DurationTypeForm(  DurationType *duration,
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
    QLabel *m_labelTimecode;
    QLineEdit *m_editTimecode;
    QLabel *m_labelNormalPlaytimeHour;
    QLabel *m_labelNormalPlaytimeMinute;
    QLabel *m_labelNormalPlaytimeSecond;
    QLabel *m_labelNormalPlaytimeMSecond;
    QSpinBox *m_spinNormalPlaytimeHour;
    QSpinBox *m_spinNormalPlaytimeMinute;
    QSpinBox *m_spinNormalPlaytimeSecond;
    QSpinBox *m_spinNormalPlaytimeMSecond;
    QUnsignedSpinBox *m_spinRate;
    QUnsignedSpinBox *m_spinFactorNumerator;
    QUnsignedSpinBox *m_spinFactorDenominator;
    QSignedSpinBox *m_spinUnitNumberValue;
    QCheckBox *m_checkRate;
    QCheckBox *m_checkFactorNumerator;
    QCheckBox *m_checkFactorDenominator;
    QLabel *m_labelUnitNumber;
    QLineEdit *m_editTimeValue;
    FormatGroupEditBox *m_editFormatGroup;
    QRadioButton *m_radioTimecode;
    QRadioButton *m_radioNormalPlaytime;
    QRadioButton *m_radioTime;
    QRadioButton *m_radioEditUnitNumber;
    DurationType *m_duration;
};

#endif // DURATIONTYPEFORM_H
