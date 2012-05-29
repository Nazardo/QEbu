#include "dategroupeditbox.h"
#include <QFormLayout>
#include <QLabel>

DateGroupEditBox::DateGroupEditBox(DateGroup *dateGroup, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *outerLayout = new QVBoxLayout;
    m_groupBox = new QGroupBox(tr("Date"));
    QGridLayout *innerLayout = new QGridLayout;

    m_editStartYear = new QSpinBox;
    m_editStartYear->setRange(0, 9999);
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
    innerLayout->addWidget(m_checkStartTime, 2, 0);
    innerLayout->addWidget(m_editStartTime, 2, 1);
    QObject::connect(m_editStartTime, SIGNAL(timeChanged(QTime)),
                     this, SLOT(startTimeChanged()));

    m_editEndYear = new QSpinBox;
    m_editEndYear->setRange(0, 9999);
    m_checkEndYear = new QCheckBox(tr("End year"));
    innerLayout->addWidget(m_checkEndYear, 3, 0);
    innerLayout->addWidget(m_editEndYear, 3, 1);
    QObject::connect(m_editEndYear, SIGNAL(valueChanged(int)),
                     this, SLOT(endYearChanged()));

    m_editEndDate = new QDateEdit;
    m_editEndDate->setCalendarPopup(true);
    m_checkEndDate = new QCheckBox(tr("End date"));
    innerLayout->addWidget(m_checkEndDate, 4, 0);
    innerLayout->addWidget(m_editEndDate, 4, 1);
    QObject::connect(m_editEndDate, SIGNAL(dateChanged(QDate)),
                     this, SLOT(endDateChanged()));

    m_editEndTime = new QTimeEdit;
    m_checkEndTime = new QCheckBox(tr("End time"));
    innerLayout->addWidget(m_checkEndTime, 5, 0);
    innerLayout->addWidget(m_editEndTime, 5, 1);
    QObject::connect(m_editEndTime, SIGNAL(timeChanged(QTime)),
                     this, SLOT(endTimeChanged()));

    m_editPeriod = new QLineEdit;
    innerLayout->addWidget(new QLabel(tr("Period")), 6, 0);
    innerLayout->addWidget(m_editPeriod, 6, 1);

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

    if (m_checkStartTime->isChecked())
        dateGroup->setStartTime(m_editStartTime->dateTime());
    else
        dateGroup->setStartTime(QDateTime());

    if (m_checkEndYear->isChecked())
        dateGroup->setEndYear(m_editEndYear->value());
    else
        dateGroup->removeEndYear();

    if (m_checkEndDate->isChecked())
        dateGroup->setEndDate(m_editEndDate->dateTime());
    else
        dateGroup->setEndDate(QDateTime());

    if (m_checkEndTime->isChecked())
        dateGroup->setEndTime(m_editEndTime->dateTime());
    else
        dateGroup->setEndTime(QDateTime());

    dateGroup->setPeriod(m_editPeriod->text());
}

void DateGroupEditBox::setLabel(QString label)
{
    m_groupBox->setTitle(label);
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
