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

#ifndef DATEGROUPEDITBOX_H
#define DATEGROUPEDITBOX_H

#include <QWidget>

class DateGroup;
class QSpinBox;
class QDateEdit;
class QTimeEdit;
class QGroupBox;
class QCheckBox;
class QLineEdit;
class TimezoneEditBox;

class DateGroupEditBox : public QWidget
{
    Q_OBJECT
public:
    explicit DateGroupEditBox(DateGroup *dateGroup,
                              QWidget *parent = 0);
    DateGroup *dateGroup();
    void updateExistingDateGroup(DateGroup *dateGroup);
    void setLabel(const QString &label);
    QSpinBox *editStartYear();
    QDateEdit *editStartDate();
    QTimeEdit *editStartTime();
    QSpinBox *editEndYear();
    QDateEdit *editEndDate();
    QTimeEdit *editEndTime();
    QLineEdit *editPeriod();
private slots:
    void startYearChanged();
    void startDateChanged();
    void startTimeChanged();
    void endYearChanged();
    void endDateChanged();
    void endTimeChanged();
private:
    QGroupBox *m_groupBox;
    QCheckBox *m_checkStartYear;
    QSpinBox *m_editStartYear;
    QCheckBox *m_checkStartDate;
    QDateEdit *m_editStartDate;
    QCheckBox *m_checkStartTime;
    QTimeEdit *m_editStartTime;
    TimezoneEditBox *m_editStartTimeTimezone;
    QCheckBox *m_checkEndYear;
    QSpinBox *m_editEndYear;
    QCheckBox *m_checkEndDate;
    QDateEdit *m_editEndDate;
    QCheckBox *m_checkEndTime;
    QTimeEdit *m_editEndTime;
    TimezoneEditBox *m_editEndTimeTimezone;
    QLineEdit *m_editPeriod;
};

#endif // DATEGROUPEDITBOX_H
