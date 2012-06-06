#include "timetypeform.h"
#include "../model/ebucoremaintype.h"
#include "listview.h"
#include "formatgroupeditbox.h"
#include "qvarptr.h"
#include "organisationdetailstypeform.h"
#include "detailstypeform.h"
#include "entitytypeform.h"
#include "typegroupform.h"
#include "timezoneeditbox.h"
#include "../model/typeconverter.h"
#include "../model/qebulimits.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>

TimeTypeForm::TimeTypeForm(TimeType *time,
                           QEbuMainWindow *mainWindow,
                           QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (time) ? Edit : Add;
    if (!time)
        m_time = new TimeType;
    else
        m_time = time;
    // Layout
    QVBoxLayout *l = new QVBoxLayout;
    {
        m_radioTimecode = new QRadioButton(tr("Timecode"));
        m_radioTimecode->setCheckable(true);
        l->addWidget(m_radioTimecode);
        QFormLayout *fl = new QFormLayout;

        m_labelTimecode = new QLabel(tr("Start time"));
        m_editTimecode = new QLineEdit();
        QRegExp SMPTE_ST_12_1_2008("(([0-1][0-9])|([2][0-3])):[0-5][0-9]:[0-5][0-9](([.,])|([:;]))[0-2][0-9]");
        m_editTimecode->setValidator(new QRegExpValidator(SMPTE_ST_12_1_2008));
        m_editTimecode->setPlaceholderText("hh:mm:ss:ff");
        fl->addRow(m_labelTimecode, m_editTimecode);
        l->addLayout(fl);

    }
    {
        m_radioNormalPlaytime = new QRadioButton(tr("Normal playtime"));
        m_radioNormalPlaytime->setCheckable(true);
        l->addWidget(m_radioNormalPlaytime);
        QFormLayout *fl = new QFormLayout;

        m_labelNormalPlaytime = new QLabel(tr("Start time"));
        m_editNormalPlaytime = new QTimeEdit;
        fl->addRow(m_labelNormalPlaytime, m_editNormalPlaytime);
        l->addLayout(fl);
    }
    {
        m_radioEditUnitNumber = new QRadioButton(tr("Edit unit number"));
        m_radioEditUnitNumber->setCheckable(true);
        l->addWidget(m_radioEditUnitNumber);
        {
            QGridLayout *gl = new QGridLayout;

            m_spinRate = new QSpinBox;
            m_spinRate->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
            m_checkRate = new QCheckBox(tr("Rate"));
            QObject::connect(m_spinRate, SIGNAL(valueChanged(int)),
                             this, SLOT(rateChanged()));
            gl->addWidget(m_checkRate, 0, 0);
            gl->addWidget(m_spinRate, 0, 1);

            m_spinFactorNumerator = new QSpinBox;
            m_spinFactorNumerator->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
            m_checkFactorNumerator = new QCheckBox(tr("Factor numerator"));
            QObject::connect(m_spinFactorNumerator, SIGNAL(valueChanged(int)),
                             this, SLOT(factorNumeratorChanged()));
            gl->addWidget(m_checkFactorNumerator, 1, 0);
            gl->addWidget(m_spinFactorNumerator, 1, 1);

            m_spinFactorDenominator = new QSpinBox;
            m_spinFactorDenominator->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
            m_checkFactorDenominator = new QCheckBox(tr("Factor denominator"));
            QObject::connect(m_spinFactorDenominator, SIGNAL(valueChanged(int)),
                             this, SLOT(factorDenominatorChanged()));
            gl->addWidget(m_checkFactorDenominator, 2, 0);
            gl->addWidget(m_spinFactorDenominator, 2, 1);

            m_spinUnitNumberValue = new QSpinBox;
            m_spinUnitNumberValue->setRange(qEbuLimits::getMinInt(), qEbuLimits::getMaxInt());
            m_checkUnitNumberValue = new QCheckBox(tr("Unit value"));
            QObject::connect(m_spinUnitNumberValue, SIGNAL(valueChanged(int)),
                             this, SLOT(unitNumberValueChanged()));
            gl->addWidget(m_checkUnitNumberValue, 3, 0);
            gl->addWidget(m_spinUnitNumberValue, 3, 1);

            l->addLayout(gl);
        }
    }
    {
        m_labelTime = new QLabel(tr("Time"));
        m_radioTime = new QRadioButton(m_labelTime);
        m_radioTime->setCheckable(true);
        l->addWidget(m_radioTime);
        m_editFormatGroup = new FormatGroupEditBox(m_time->time());
        l->addWidget(m_editFormatGroup);
    }

    QButtonGroup *radio = new QButtonGroup;
    radio->addButton(m_radioTimecode);
    radio->addButton(m_radioNormalPlaytime);
    radio->addButton(m_radioEditUnitNumber);
    radio->addButton(m_radioTime);

    QObject::connect(m_radioTimecode, SIGNAL(toggled(bool)),
                     this, SLOT(timecodeChecked(bool)));
    QObject::connect(m_radioTime, SIGNAL(toggled(bool)),
                     this, SLOT(timeChecked(bool)));
    QObject::connect(m_radioNormalPlaytime, SIGNAL(toggled(bool)),
                     this, SLOT(normalPlaytimeChecked(bool)));
    QObject::connect(m_radioEditUnitNumber, SIGNAL(toggled(bool)),
                     this, SLOT(editUnitNumberChecked(bool)));

    this->setLayout(l);

    // Set data fields...
    m_editTimecode->setText(m_time->timecode());
    m_editNormalPlaytime->setTime(m_time->normalPlayTime().time());

    if (m_time->editUnitNumberValue()) {
        m_spinUnitNumberValue->setValue(*(m_time->editUnitNumberValue()));
        m_checkUnitNumberValue->setChecked(true);
    }
    if (m_time->editRate()) {
        m_spinRate->setValue(*(m_time->editRate()));
        m_checkRate->setChecked(true);
    }
    if (m_time->factorNumerator()) {
        m_spinFactorNumerator->setValue(m_time->factorNumerator());
        m_checkFactorNumerator->setChecked(true);
    }
    if (m_time->factorDenominator()) {
        m_spinFactorDenominator->setValue(m_time->factorDenominator());
        m_checkFactorDenominator->setChecked(true);
    }

    if (time) {
        switch (time->timeTypeRepresentation()) {
        case TimeType::enumTimecode:
        {
            m_radioTimecode->setChecked(true);
        }
            break;
        case TimeType::enumTime:
        {
            m_radioTime->setChecked(true);
        }
            break;
        case TimeType::enumNormalPlayTime:
        {
            m_radioNormalPlaytime->setChecked(true);
        }
            break;
        case TimeType::enumEditUnitNumber:
        {
            m_radioEditUnitNumber->setChecked(true);
        }
            break;
        }
    }
    else
        m_radioTimecode->setChecked(true);
}

QString TimeTypeForm::toString()
{
    return QString("Time Type");
}

void TimeTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_time;
        m_time = 0;
    }
    emit closed(m_op, QVarPtr<TimeType>::asQVariant(m_time));
}

void TimeTypeForm::applyClicked()
{
    if (m_radioTimecode->isChecked()) {
        m_time->setTimecode(m_editTimecode->text());

    } else if (m_radioNormalPlaytime->isChecked()) {
        m_time->setNormalPlayTime(TypeConverter::timeToDateTime(m_editNormalPlaytime->time()));

    } else if (m_radioTime->isChecked()) {
        FormatGroup *fg = m_editFormatGroup->formatGroup();
        m_time->setTime(fg);

    } else if (m_radioEditUnitNumber->isChecked()) {
        if (m_checkRate->isChecked())
            m_time->setEditRate(m_spinRate->value());
        else
            m_time->clearEditRate();
        if (m_checkUnitNumberValue->isChecked())
            m_time->setEditUnitNumberValue(m_spinUnitNumberValue->value());
        else
            m_time->clearEditUnitNumberValue();
        if (m_checkFactorNumerator->isChecked())
            m_time->setFactorNumerator(m_spinFactorNumerator->value());
        else
            m_time->clearFactorNumerator();
        if (m_checkFactorDenominator->isChecked())
            m_time->setFactorDenominator(m_spinFactorDenominator->value());
        else
            m_time->clearFactorDenominator();
    }

    emit closed(m_op, QVarPtr<TimeType>::asQVariant(m_time));
}

void TimeTypeForm::timeChecked(bool checked)
{
    if (!checked)
        return;

    m_labelTime->setEnabled(true);
    m_editFormatGroup->setEnabled(true);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_checkUnitNumberValue->setEnabled(false);
    m_checkRate->setEnabled(false);
    m_checkFactorNumerator->setEnabled(false);
    m_checkFactorDenominator->setEnabled(false);
    m_labelTimecode->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_labelNormalPlaytime->setEnabled(false);
    m_editNormalPlaytime->setEnabled(false);
}

void TimeTypeForm::timecodeChecked(bool checked)
{
    if (!checked)
        return;

    m_labelTime->setEnabled(false);
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_checkUnitNumberValue->setEnabled(false);
    m_checkRate->setEnabled(false);
    m_checkFactorNumerator->setEnabled(false);
    m_checkFactorDenominator->setEnabled(false);
    m_labelTimecode->setEnabled(true);
    m_editTimecode->setEnabled(true);
    m_labelNormalPlaytime->setEnabled(false);
    m_editNormalPlaytime->setEnabled(false);
}

void TimeTypeForm::normalPlaytimeChecked(bool checked)
{
    if (!checked)
        return;

    m_labelTime->setEnabled(false);
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(false);
    m_spinRate->setEnabled(false);
    m_spinFactorNumerator->setEnabled(false);
    m_spinFactorDenominator->setEnabled(false);
    m_checkUnitNumberValue->setEnabled(false);
    m_checkRate->setEnabled(false);
    m_checkFactorNumerator->setEnabled(false);
    m_checkFactorDenominator->setEnabled(false);
    m_labelTimecode->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_labelNormalPlaytime->setEnabled(true);
    m_editNormalPlaytime->setEnabled(true);
}

void TimeTypeForm::editUnitNumberChecked(bool checked)
{
    if (!checked)
        return;

    m_labelTime->setEnabled(false);
    m_editFormatGroup->setEnabled(false);
    m_spinUnitNumberValue->setEnabled(true);
    m_spinRate->setEnabled(true);
    m_spinFactorNumerator->setEnabled(true);
    m_spinFactorDenominator->setEnabled(true);
    m_checkUnitNumberValue->setEnabled(true);
    m_checkRate->setEnabled(true);
    m_checkFactorNumerator->setEnabled(true);
    m_checkFactorDenominator->setEnabled(true);
    m_labelTimecode->setEnabled(false);
    m_editTimecode->setEnabled(false);
    m_labelNormalPlaytime->setEnabled(false);
    m_editNormalPlaytime->setEnabled(false);
}

void TimeTypeForm::rateChanged()
{
    m_checkRate->setChecked(true);
}

void TimeTypeForm::factorNumeratorChanged()
{
    m_checkFactorNumerator->setChecked(true);
}

void TimeTypeForm::factorDenominatorChanged()
{
    m_checkFactorDenominator->setChecked(true);
}

void TimeTypeForm::unitNumberValueChanged()
{
    m_checkUnitNumberValue->setChecked(true);
}
