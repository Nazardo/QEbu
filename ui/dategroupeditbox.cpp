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

#include "dategroupeditbox.h"
#include "../model/dategroup.h"
#include "timezoneeditbox.h"
#include <QDateEdit>
#include <QLineEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QFormLayout>

DateGroupEditBox::DateGroupEditBox(DateGroup *dateGroup, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *outerLayout = new QVBoxLayout;
    m_groupBox = new QGroupBox(tr("Date"));
    QGridLayout *innerLayout = new QGridLayout;

    m_editStartYear = new QSpinBox;
    m_editStartYear->setRange(1, 9999);
    m_editStartYear->setValue(2000);
    m_checkStartYear = new QCheckBox(tr("Start year"));
    innerLayout->addWidget(m_checkStartYear, 0, 0);
    innerLayout->addWidget(m_editStartYear, 0, 1);
    QObject::connect(m_editStartYear, SIGNAL(valueChanged(int)),
                     this, SLOT(startYearChanged()));

    m_editStartDate = new QDateEdit;
    m_editStartDate->setCalendarPopup(true);
    m_checkStartDate = new QCheckBox(tr("Start date"));
    innerLayout->addWidget(m_checkStartDate, 1, 0);
    innerLayout->addWidget(m_editStartDate, 1, 1);
    QObject::connect(m_editStartDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(startDateChanged()));

    m_editStartTime = new QTimeEdit;
    m_checkStartTime = new QCheckBox(tr("Start time"));
    m_editStartTimeTimezone = new TimezoneEditBox();
    innerLayout->addWidget(m_checkStartTime, 2, 0);
    innerLayout->addWidget(m_editStartTime, 2, 1);
    innerLayout->addWidget(m_editStartTimeTimezone, 3, 1);
    QObject::connect(m_editStartTime, SIGNAL(timeChanged(QTime)),
                     this, SLOT(startTimeChanged()));
    QObject::connect(m_editStartTimeTimezone, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(startTimeChanged()));


    m_editEndYear = new QSpinBox;
    m_editEndYear->setRange(1, 9999);
    m_editEndYear->setValue(2000);
    m_checkEndYear = new QCheckBox(tr("End year"));
    innerLayout->addWidget(m_checkEndYear, 4, 0);
    innerLayout->addWidget(m_editEndYear, 4, 1);
    QObject::connect(m_editEndYear, SIGNAL(valueChanged(int)),
                     this, SLOT(endYearChanged()));

    m_editEndDate = new QDateEdit;
    m_editEndDate->setCalendarPopup(true);
    m_checkEndDate = new QCheckBox(tr("End date"));
    innerLayout->addWidget(m_checkEndDate, 5, 0);
    innerLayout->addWidget(m_editEndDate, 5, 1);
    QObject::connect(m_editEndDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(endDateChanged()));

    m_editEndTime = new QTimeEdit;
    m_checkEndTime = new QCheckBox(tr("End time"));
    m_editEndTimeTimezone = new TimezoneEditBox();
    innerLayout->addWidget(m_checkEndTime, 6, 0);
    innerLayout->addWidget(m_editEndTime, 6, 1);
    innerLayout->addWidget(m_editEndTimeTimezone, 7, 1);
    QObject::connect(m_editEndTime, SIGNAL(timeChanged(QTime)),
                     this, SLOT(endTimeChanged()));
    QObject::connect(m_editEndTimeTimezone, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(endTimeChanged()));

    m_editPeriod = new QLineEdit;
    innerLayout->addWidget(new QLabel(tr("Period")), 8, 0);
    innerLayout->addWidget(m_editPeriod, 8, 1);

    m_groupBox->setLayout(innerLayout);
    outerLayout->addWidget(m_groupBox);
    this->setLayout(outerLayout);

    // Set fields
    if (!dateGroup)
        return;
    if (dateGroup->startYear()) {
        m_checkStartYear->setChecked(true);
        m_editStartYear->setValue(*(dateGroup->startYear()));
    }
    if (dateGroup->startDate().isValid()) {
        m_checkStartDate->setChecked(true);
        m_editStartDate->setDateTime(dateGroup->startDate());
    }
    if (dateGroup->startTime().isValid()) {
        m_checkStartTime->setChecked(true);
        m_editStartTime->setDateTime(dateGroup->startTime());
        if (dateGroup->startTime().timeSpec()!=Qt::LocalTime)
            m_editStartTimeTimezone->setUTCOffset(dateGroup->startTime().utcOffset()/60);
    }
    if (dateGroup->endYear()) {
        m_checkEndYear->setChecked(true);
        m_editEndYear->setValue(*(dateGroup->endYear()));
    }
    if (dateGroup->endDate().isValid()) {
        m_checkEndDate->setChecked(true);
        m_editEndDate->setDateTime(dateGroup->endDate());
    }
    if (dateGroup->endTime().isValid()) {
        m_checkEndTime->setChecked(true);
        m_editEndTime->setDateTime(dateGroup->endTime());
        if (dateGroup->endTime().timeSpec()!=Qt::LocalTime)
            m_editEndTimeTimezone->setUTCOffset(dateGroup->endTime().utcOffset()/60);
    }
    m_editPeriod->setText(dateGroup->period());
}

DateGroup *DateGroupEditBox::dateGroup()
{
    DateGroup *dateGroup = new DateGroup;
    updateExistingDateGroup(dateGroup);
    return dateGroup;
}

void DateGroupEditBox::updateExistingDateGroup(DateGroup *dateGroup)
{
    if (m_checkStartYear->isChecked())
        dateGroup->setStartYear(m_editStartYear->value());
    else
        dateGroup->removeEndYear();

    if (m_checkStartDate->isChecked())
        dateGroup->setStartDate(m_editStartDate->dateTime());
    else
        dateGroup->setStartDate(QDateTime());

    if (m_checkStartTime->isChecked()) {
        QDateTime dt(m_editStartTime->dateTime());
        dt.setUtcOffset(m_editStartTimeTimezone->getUTCOffset()*60);
        if (m_editStartTimeTimezone->isLocal())
            dt.setTimeSpec(Qt::LocalTime);
        dateGroup->setStartTime(dt);
    } else
        dateGroup->setStartTime(QDateTime());

    if (m_checkEndYear->isChecked())
        dateGroup->setEndYear(m_editEndYear->value());
    else
        dateGroup->removeEndYear();

    if (m_checkEndDate->isChecked())
        dateGroup->setEndDate(m_editEndDate->dateTime());
    else
        dateGroup->setEndDate(QDateTime());

    if (m_checkEndTime->isChecked()) {
        QDateTime dt(m_editEndTime->dateTime());
        dt.setUtcOffset(m_editEndTimeTimezone->getUTCOffset()*60);
        if (m_editEndTimeTimezone->isLocal())
            dt.setTimeSpec(Qt::LocalTime);
        dateGroup->setEndTime(dt);
    } else
        dateGroup->setEndTime(QDateTime());

    dateGroup->setPeriod(m_editPeriod->text());
}

void DateGroupEditBox::setLabel(const QString &label)
{
    m_groupBox->setTitle(label);
}

QSpinBox *DateGroupEditBox::editStartYear()
{
    return m_editStartYear;
}

QDateEdit *DateGroupEditBox::editStartDate()
{
    return m_editStartDate;
}

QTimeEdit *DateGroupEditBox::editStartTime()
{
    return m_editStartTime;
}

QSpinBox *DateGroupEditBox::editEndYear()
{
    return m_editEndYear;
}

QDateEdit *DateGroupEditBox::editEndDate()
{
    return m_editEndDate;
}

QTimeEdit *DateGroupEditBox::editEndTime()
{
    return m_editEndTime;
}

QLineEdit *DateGroupEditBox::editPeriod()
{
    return m_editPeriod;
}

void DateGroupEditBox::startYearChanged()
{
    m_checkStartYear->setChecked(true);
}

void DateGroupEditBox::startDateChanged()
{
    m_checkStartDate->setChecked(true);
}

void DateGroupEditBox::startTimeChanged()
{
    m_checkStartTime->setChecked(true);
}

void DateGroupEditBox::endYearChanged()
{
    m_checkEndYear->setChecked(true);
}

void DateGroupEditBox::endDateChanged()
{
    m_checkEndDate->setChecked(true);
}

void DateGroupEditBox::endTimeChanged()
{
    m_checkEndTime->setChecked(true);
}
